#pragma once

#include <type_traits>

namespace RE
{
	template <class Key, class Value>
	class hkPointerMap
	{
	public:
		using size_type = std::int32_t;

		struct Pair
		{
			std::uint64_t key;    // 00
			std::uint64_t value;  // 08
		};
		static_assert(sizeof(Pair) == 0x10);

		[[nodiscard]] Value GetWithDefault(Key a_key, Value a_default) const noexcept
		{
			static_assert(std::is_integral_v<Key> || std::is_pointer_v<Key>);
			static_assert(std::is_integral_v<Value> || std::is_pointer_v<Value>);

			if (hashMod > 0) {
				const auto key = ToStorage(a_key);
				auto       index = static_cast<std::uint32_t>(key >> 4) * 0x9E3779B1u;
				index &= static_cast<std::uint32_t>(hashMod);

				while (data[index].key != static_cast<std::uint64_t>(-1)) {
					if (data[index].key == key) {
						return FromStorage<Value>(data[index].value);
					}

					index = (index + 1) & static_cast<std::uint32_t>(hashMod);
				}
			}

			return a_default;
		}

		[[nodiscard]] size_type size() const noexcept
		{
			return sizeAndFlags & 0x7FFFFFFF;
		}

		// members
		Pair*     data{ nullptr };  // 00
		size_type sizeAndFlags{};   // 08
		size_type hashMod{ -1 };    // 0C

	private:
		template <class T>
		[[nodiscard]] static std::uint64_t ToStorage(T a_value) noexcept
		{
			if constexpr (std::is_pointer_v<T>) {
				return reinterpret_cast<std::uintptr_t>(a_value);
			} else if constexpr (std::is_signed_v<T>) {
				return static_cast<std::uint64_t>(static_cast<std::int64_t>(a_value));
			} else {
				return static_cast<std::uint64_t>(a_value);
			}
		}

		template <class T>
		[[nodiscard]] static T FromStorage(std::uint64_t a_value) noexcept
		{
			if constexpr (std::is_pointer_v<T>) {
				return reinterpret_cast<T>(static_cast<std::uintptr_t>(a_value));
			} else if constexpr (std::is_signed_v<T>) {
				return static_cast<T>(static_cast<std::int64_t>(a_value));
			} else {
				return static_cast<T>(a_value);
			}
		}
	};
	static_assert(sizeof(hkPointerMap<std::int32_t, std::int32_t>) == 0x10);
}
