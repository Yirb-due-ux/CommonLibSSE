#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbSequencedData.h"

namespace RE
{
	class hkbEventSequencedData : public hkbSequencedData
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventSequencedData;
		inline static constexpr auto VTABLE = VTABLE_hkbEventSequencedData;

		struct SequencedEvent
		{
			hkbEvent     event;     // 00
			float        time;      // 18
			std::uint8_t pad1C[4];  // 1C
		};
		static_assert(offsetof(SequencedEvent, event) == 0x00);
		static_assert(offsetof(SequencedEvent, time) == 0x18);
		static_assert(sizeof(SequencedEvent) == 0x20);

		~hkbEventSequencedData() override;  // 00

		// Enqueues every event at or before a_time and advances a_nextSample.
		void Update(
			hkbSequence*      a_sequence,
			const hkbContext& a_context,
			float             a_time,
			hkbEventQueue&    a_eventQueue,
			hkbSymbolIdMap*   a_variableIDMap,
			std::int32_t&     a_nextSample) override;  // 03

		// members
		hkArray<SequencedEvent> events;  // 10
	};
	static_assert(offsetof(hkbEventSequencedData, events) == 0x10);
	static_assert(sizeof(hkbEventSequencedData) == 0x20);
}
