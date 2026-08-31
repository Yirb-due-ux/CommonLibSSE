#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkbSequencedData.h"

namespace RE
{
	class hkbIntVariableSequencedData : public hkbSequencedData
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbIntVariableSequencedData;
		inline static constexpr auto VTABLE = VTABLE_hkbIntVariableSequencedData;

		struct Sample
		{
			float        time;   // 00
			std::int32_t value;  // 04
		};
		static_assert(offsetof(Sample, time) == 0x00);
		static_assert(offsetof(Sample, value) == 0x04);
		static_assert(sizeof(Sample) == 0x08);

		~hkbIntVariableSequencedData() override;  // 00

		// Samples the nearest value at a_time and writes the mapped graph variable.
		void Update(
			hkbSequence*      a_sequence,
			const hkbContext& a_context,
			float             a_time,
			hkbEventQueue&    a_eventQueue,
			hkbSymbolIdMap*   a_variableIDMap,
			std::int32_t&     a_nextSample) override;  // 03

		// members
		hkArray<Sample> samples;        // 10
		std::int32_t    variableIndex;  // 20
		std::uint8_t    pad24[4];       // 24
	};
	static_assert(offsetof(hkbIntVariableSequencedData, samples) == 0x10);
	static_assert(offsetof(hkbIntVariableSequencedData, variableIndex) == 0x20);
	static_assert(sizeof(hkbIntVariableSequencedData) == 0x28);
}
