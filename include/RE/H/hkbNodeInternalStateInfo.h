#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkbNodeInfo.h"

namespace RE
{
	class hkbNodeInternalStateInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNodeInternalStateInfo;
		inline static constexpr auto VTABLE = VTABLE_hkbNodeInternalStateInfo;

		~hkbNodeInternalStateInfo() override;  // 00

		// members
		hkbGeneratorSyncInfo         syncInfo;               // 10
		hkStringPtr                  name;                   // 60
		hkRefPtr<hkReferencedObject> internalState;          // 68
		std::int16_t                 nodeID;                 // 70
		bool                         hasActivateBeenCalled;  // 72
		std::uint8_t                 pad73[5];               // 73
	};
	static_assert(offsetof(hkbNodeInternalStateInfo, syncInfo) == 0x10);
	static_assert(offsetof(hkbNodeInternalStateInfo, name) == 0x60);
	static_assert(offsetof(hkbNodeInternalStateInfo, internalState) == 0x68);
	static_assert(offsetof(hkbNodeInternalStateInfo, nodeID) == 0x70);
	static_assert(offsetof(hkbNodeInternalStateInfo, hasActivateBeenCalled) == 0x72);
	static_assert(sizeof(hkbNodeInternalStateInfo) == 0x78);
}
