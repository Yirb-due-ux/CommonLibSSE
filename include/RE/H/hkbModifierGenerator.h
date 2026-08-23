#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbModifier;

	class hkbModifierGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifierGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbModifierGenerator;

		~hkbModifierGenerator() override;  // 00

		// Skyrim SE 1.5.97 reflection and destructor expose two referenced objects at 0x48 and 0x50.
		hkRefPtr<hkbModifier>  modifier;   // 48
		hkRefPtr<hkbGenerator> generator;  // 50
	};
	static_assert(offsetof(hkbModifierGenerator, modifier) == 0x48);
	static_assert(offsetof(hkbModifierGenerator, generator) == 0x50);
	static_assert(sizeof(hkbModifierGenerator) == 0x58);
}
