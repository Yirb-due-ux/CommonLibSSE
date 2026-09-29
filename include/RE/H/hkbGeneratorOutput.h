#pragma once

#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <optional>
#include <span>
#include <type_traits>

#include "REX/REX/EnumSet.h"

namespace RE
{
	struct hkbGeneratorOutput
	{
		enum class TrackType : std::int8_t
		{
			kReal = 0,
			kQsTransform = 1,
			kBinary = 2
		};

		enum class TrackFlagBits : std::int8_t
		{
			kNone = 0,
			kAdditivePose = 1 << 0,
			kPalette = 1 << 1,
			kSparse = 1 << 2
		};
		using TrackFlags = REX::EnumSet<TrackFlagBits, std::int8_t>;

		struct TrackMasterHeader
		{
			std::int32_t numBytes;   // 00 - Total size of the packed track buffer.
			std::int32_t numTracks;  // 04
			std::uint8_t unused[8];  // 08
		};
		static_assert(sizeof(TrackMasterHeader) == 0x10);

		struct TrackHeader
		{
			std::int16_t                         capacity;          // 00 - Element capacity, not byte capacity.
			std::int16_t                         numData;           // 02 - Number of populated elements.
			std::int16_t                         dataOffset;        // 04 - Offset from the packed buffer base.
			std::int16_t                         elementSizeBytes;  // 06
			float                                onFraction;        // 08 - Zero means the track data is invalid.
			TrackFlags                           flags;             // 0C
			REX::EnumSet<TrackType, std::int8_t> type;              // 0D
			std::uint16_t                        pad0E;             // 0E
		};
		static_assert(offsetof(TrackHeader, onFraction) == 0x08);
		static_assert(offsetof(TrackHeader, flags) == 0x0C);
		static_assert(offsetof(TrackHeader, type) == 0x0D);
		static_assert(sizeof(TrackHeader) == 0x10);

		struct Tracks
		{
			TrackMasterHeader masterHeader;     // 00
			TrackHeader       trackHeaders[1];  // 10 - Variable-length tail with masterHeader.numTracks entries.
		};
		static_assert(offsetof(Tracks, trackHeaders) == 0x10);
		static_assert(sizeof(Tracks) == 0x20);

		// Accessors for the packed format verified for Skyrim SE 1.5.97.
		class DenseRealTrack
		{
		public:
			const TrackHeader& GetHeader() const noexcept { return _header; }

			// Reads one value from the buffer; no pointer is retained.
			bool Read(
				std::span<const std::byte> a_buffer,
				std::size_t                a_slotIndex,
				std::optional<float>&      a_out) const noexcept
			{
				if (a_buffer.size() < _numBytes) {
					return false;
				}
				if (a_slotIndex >= static_cast<std::size_t>(_header.numData)) {
					a_out.reset();
					return true;
				}
				float      value;
				const auto offset = static_cast<std::size_t>(_header.dataOffset) + a_slotIndex * sizeof(float);
				std::memcpy(std::addressof(value), a_buffer.data() + offset, sizeof(value));
				a_out = value;
				return true;
			}

		private:
			friend struct hkbGeneratorOutput;

			DenseRealTrack(const TrackHeader& a_header, std::size_t a_numBytes) noexcept :
				_header(a_header), _numBytes(a_numBytes)
			{}

			TrackHeader _header;
			std::size_t _numBytes;
		};

		// Copies track metadata from the buffer.
		static bool TryReadTrackHeader(
			std::span<const std::byte> a_buffer,
			std::size_t                a_trackIndex,
			TrackHeader&               a_out) noexcept
		{
			if (a_buffer.size() < sizeof(TrackMasterHeader)) {
				return false;
			}
			TrackMasterHeader master;
			std::memcpy(std::addressof(master), a_buffer.data(), sizeof(master));
			if (master.numBytes < static_cast<std::int32_t>(sizeof(master)) ||
				static_cast<std::size_t>(master.numBytes) > a_buffer.size() ||
				master.numTracks < 0 || a_trackIndex >= static_cast<std::size_t>(master.numTracks)) {
				return false;
			}
			const auto totalBytes = static_cast<std::size_t>(master.numBytes);
			const auto numTracks = static_cast<std::size_t>(master.numTracks);
			if (numTracks > (totalBytes - sizeof(master)) / sizeof(TrackHeader)) {
				return false;
			}
			const auto  headersEnd = sizeof(master) + numTracks * sizeof(TrackHeader);
			TrackHeader header;
			std::memcpy(std::addressof(header), a_buffer.data() + sizeof(master) + a_trackIndex * sizeof(header), sizeof(header));
			if (header.capacity < 0 || header.numData < 0 || header.numData > header.capacity ||
				header.elementSizeBytes <= 0 || !std::isfinite(header.onFraction) ||
				header.dataOffset < 0 || static_cast<std::size_t>(header.dataOffset) < headersEnd ||
				static_cast<std::size_t>(header.dataOffset) >= totalBytes ||
				static_cast<std::size_t>(header.capacity) >
					(totalBytes - static_cast<std::size_t>(header.dataOffset)) / static_cast<std::size_t>(header.elementSizeBytes)) {
				return false;
			}
			a_out = header;
			return true;
		}

		static std::optional<DenseRealTrack> TryReadDenseRealTrack(
			std::span<const std::byte> a_buffer,
			std::size_t                a_trackIndex) noexcept
		{
			TrackHeader header;
			if (!TryReadTrackHeader(a_buffer, a_trackIndex, header) ||
				header.type != TrackType::kReal || header.onFraction <= 0.0f ||
				header.flags.any(TrackFlagBits::kPalette, TrackFlagBits::kSparse) ||
				header.elementSizeBytes != static_cast<std::int16_t>(sizeof(float))) {
				return std::nullopt;
			}
			std::int32_t totalBytes;
			std::memcpy(std::addressof(totalBytes), a_buffer.data(), sizeof(totalBytes));
			return DenseRealTrack(header, static_cast<std::size_t>(totalBytes));
		}

		// Skyrim SE 1.5.97 passes this 0x10 holder between generator and graph output paths.
		Tracks*      tracks;        // 00
		bool         deleteTracks;  // 08 - The holder frees tracks through Havok's allocator when set.
		std::uint8_t pad09[7];      // 09
	};
	static_assert(offsetof(hkbGeneratorOutput, deleteTracks) == 0x08);
	static_assert(sizeof(hkbGeneratorOutput) == 0x10);
}
