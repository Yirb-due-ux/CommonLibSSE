#pragma once

#include "RE/H/hkQueue.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbSymbolIdMap.h"

namespace RE
{
	class hkbEventQueue
	{
	public:
		std::int32_t ConvertID(std::int32_t a_id) const
		{
			if (!eventIdMap) {
				return a_id;
			}

			return mapInternalToExternal ? eventIdMap->GetExternal(a_id) : eventIdMap->GetInternal(a_id);
		}

		// members
		hkQueue<hkbEvent> queue;                           // 00
		hkbSymbolIdMap*   eventIdMap{ nullptr };           // 18
		bool              mapInternalToExternal{ false };  // 20
		std::uint8_t      pad21[7]{};                      // 21
	};
	static_assert(offsetof(hkbEventQueue, queue) == 0x00);
	static_assert(offsetof(hkbEventQueue, eventIdMap) == 0x18);
	static_assert(offsetof(hkbEventQueue, mapInternalToExternal) == 0x20);
	static_assert(sizeof(hkbEventQueue) == 0x28);
}
