#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkVector4;
	union hkbVariableValue;

	class hkbVariableValueSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableValueSet;
		inline static constexpr auto VTABLE = VTABLE_hkbVariableValueSet;

		~hkbVariableValueSet() override;  // 00

		// members
		hkArray<hkbVariableValue> wordVariableValues;     // 10
		hkArray<hkVector4>        quadVariableValues;     // 20
		hkArray<hkRefVariant>     variantVariableValues;  // 30
	};
	static_assert(offsetof(hkbVariableValueSet, wordVariableValues) == 0x10);
	static_assert(offsetof(hkbVariableValueSet, quadVariableValues) == 0x20);
	static_assert(offsetof(hkbVariableValueSet, variantVariableValues) == 0x30);
	static_assert(sizeof(hkbVariableValueSet) == 0x40);
}
