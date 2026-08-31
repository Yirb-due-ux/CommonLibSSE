#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbSequenceInternalState : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSequenceInternalState;
		inline static constexpr auto VTABLE = VTABLE_hkbSequenceInternalState;

		~hkbSequenceInternalState() override;  // 00

		// members
		hkArray<std::int32_t> nextSampleEvents;  // 10
		hkArray<std::int32_t> nextSampleReals;   // 20
		hkArray<std::int32_t> nextSampleBools;   // 30
		hkArray<std::int32_t> nextSampleInts;    // 40
		float                 time;              // 50
		bool                  isEnabled;         // 54
		std::uint8_t          pad55[3];          // 55
	};
	static_assert(offsetof(hkbSequenceInternalState, nextSampleEvents) == 0x10);
	static_assert(offsetof(hkbSequenceInternalState, nextSampleReals) == 0x20);
	static_assert(offsetof(hkbSequenceInternalState, nextSampleBools) == 0x30);
	static_assert(offsetof(hkbSequenceInternalState, nextSampleInts) == 0x40);
	static_assert(offsetof(hkbSequenceInternalState, time) == 0x50);
	static_assert(offsetof(hkbSequenceInternalState, isEnabled) == 0x54);
	static_assert(sizeof(hkbSequenceInternalState) == 0x58);
}
