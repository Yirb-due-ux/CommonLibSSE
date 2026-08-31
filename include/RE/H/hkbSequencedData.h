#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbContext;
	class hkbEventQueue;
	class hkbSequence;
	class hkbSymbolIdMap;

	class hkbSequencedData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSequencedData;
		inline static constexpr auto VTABLE = VTABLE_hkbSequencedData;

		~hkbSequencedData() override;  // 00

		virtual void Update(
			hkbSequence*      a_sequence,
			const hkbContext& a_context,
			float             a_time,
			hkbEventQueue&    a_eventQueue,
			hkbSymbolIdMap*   a_variableIDMap,
			std::int32_t&     a_nextSample) = 0;  // 03
	};
	static_assert(sizeof(hkbSequencedData) == 0x10);
}
