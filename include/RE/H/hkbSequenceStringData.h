#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbSequenceStringData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSequenceStringData;
		inline static constexpr auto VTABLE = VTABLE_hkbSequenceStringData;

		~hkbSequenceStringData() override;  // 00

		// members
		hkArray<hkStringPtr> eventNames;     // 10
		hkArray<hkStringPtr> variableNames;  // 20
	};
	static_assert(offsetof(hkbSequenceStringData, eventNames) == 0x10);
	static_assert(offsetof(hkbSequenceStringData, variableNames) == 0x20);
	static_assert(sizeof(hkbSequenceStringData) == 0x30);
}
