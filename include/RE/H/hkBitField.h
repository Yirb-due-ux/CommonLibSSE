#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	struct hkBitField
	{
		static hkBitField Borrow(std::uint32_t* a_words, std::int32_t a_count, std::int32_t a_bits)
		{
			hkBitField field{};
			field.words._data = a_words;
			field.words._size = a_count;
			field.words._capacityAndFlags = static_cast<std::int32_t>(a_count | hkArrayBase<std::uint32_t>::kDontDeallocFlag);
			field.numBits = a_bits;
			return field;
		}

		[[nodiscard]] bool Test(std::size_t a_bit) const
		{
			return (words.data()[a_bit / 32] & (1u << (a_bit % 32))) != 0;
		}

		hkArrayBase<std::uint32_t> words;   // 00
		std::int32_t              numBits;  // 10
	};
	static_assert(sizeof(hkBitField) == 0x18);
	static_assert(offsetof(hkBitField, numBits) == 0x10);
}
