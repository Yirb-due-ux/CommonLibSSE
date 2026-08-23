#pragma once

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

		// Skyrim SE 1.5.97 passes this 0x10 holder between generator and graph output paths.
		Tracks*      tracks;        // 00
		bool         deleteTracks;  // 08 - The holder frees tracks through Havok's allocator when set.
		std::uint8_t pad09[7];      // 09
	};
	static_assert(offsetof(hkbGeneratorOutput, deleteTracks) == 0x08);
	static_assert(sizeof(hkbGeneratorOutput) == 0x10);
}
