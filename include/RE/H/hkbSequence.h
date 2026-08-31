#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbModifier.h"
#include "RE/H/hkbSequenceInternalState.h"

namespace RE
{
	class hkbBehaviorGraph;
	class hkbBoolVariableSequencedData;
	class hkbEvent;
	class hkbEventSequencedData;
	class hkbIntVariableSequencedData;
	class hkbRealVariableSequencedData;
	class hkbSequenceStringData;
	class hkbSymbolIdMap;

	class hkbSequence : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSequence;
		inline static constexpr auto VTABLE = VTABLE_hkbSequence;

		~hkbSequence() override;  // 00

		// Resets time and all four sampling cursors. The sequence starts enabled
		// when no enable event is configured.
		void Activate(const hkbContext& a_context) override;  // 04

		// While enabled, advances time and updates every event and variable track.
		void Update(const hkbContext& a_context, float a_timestep) override;  // 05

		// Maps the incoming event when an event ID map exists, then applies the
		// configured enable or disable event. Enabling also resets time to zero.
		void HandleEvent(const hkbContext& a_context, hkbEvent& a_event) override;  // 06

		// Shares referenced sequence data and ID maps, then resets the runtime sampling state.
		// Native allocation; the caller receives one reference.
		[[nodiscard]] hkbSequence* CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;  // 0C

		// Native allocation; the caller receives one reference.
		// This function does not initialize the scalar state fields; GetInternalState does.
		[[nodiscard]] hkbSequenceInternalState* CreateInternalState() override;  // 0D

		// Copies all playback state: four sampling cursors, time, and enable state.
		void GetInternalState(hkReferencedObject& a_internalState) const override;  // 0E

		// Restores all playback state captured by GetInternalState.
		void SetInternalState(const hkReferencedObject& a_internalState) override;  // 10

		// members
		hkArray<hkbEventSequencedData*>        eventSequencedData;         // 050
		hkArray<hkbRealVariableSequencedData*> realVariableSequencedData;  // 060
		hkArray<hkbBoolVariableSequencedData*> boolVariableSequencedData;  // 070
		hkArray<hkbIntVariableSequencedData*>  intVariableSequencedData;   // 080
		std::int32_t                           enableEventId;              // 090
		std::int32_t                           disableEventId;             // 094
		hkRefPtr<hkbSequenceStringData>        stringData;                 // 098
		hkRefPtr<hkbSymbolIdMap>               variableIdMap;              // 0A0 - runtime only
		hkRefPtr<hkbSymbolIdMap>               eventIdMap;                 // 0A8 - runtime only
		hkArray<std::int32_t>                  nextSampleEvents;           // 0B0 - runtime only
		hkArray<std::int32_t>                  nextSampleReals;            // 0C0 - runtime only
		hkArray<std::int32_t>                  nextSampleBools;            // 0D0 - runtime only
		hkArray<std::int32_t>                  nextSampleInts;             // 0E0 - runtime only
		float                                  time;                       // 0F0 - runtime only
		bool                                   isEnabled;                  // 0F4 - runtime only
		std::uint8_t                           padF5[3];                   // 0F5
	};
	static_assert(offsetof(hkbSequence, eventSequencedData) == 0x50);
	static_assert(offsetof(hkbSequence, realVariableSequencedData) == 0x60);
	static_assert(offsetof(hkbSequence, boolVariableSequencedData) == 0x70);
	static_assert(offsetof(hkbSequence, intVariableSequencedData) == 0x80);
	static_assert(offsetof(hkbSequence, enableEventId) == 0x90);
	static_assert(offsetof(hkbSequence, disableEventId) == 0x94);
	static_assert(offsetof(hkbSequence, stringData) == 0x98);
	static_assert(offsetof(hkbSequence, variableIdMap) == 0xA0);
	static_assert(offsetof(hkbSequence, eventIdMap) == 0xA8);
	static_assert(offsetof(hkbSequence, nextSampleEvents) == 0xB0);
	static_assert(offsetof(hkbSequence, nextSampleReals) == 0xC0);
	static_assert(offsetof(hkbSequence, nextSampleBools) == 0xD0);
	static_assert(offsetof(hkbSequence, nextSampleInts) == 0xE0);
	static_assert(offsetof(hkbSequence, time) == 0xF0);
	static_assert(offsetof(hkbSequence, isEnabled) == 0xF4);
	static_assert(sizeof(hkbSequence) == 0xF8);
}
