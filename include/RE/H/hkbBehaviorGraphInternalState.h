#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbNodeInternalStateInfo.h"

namespace RE
{
	class hkbVariableValueSet;

	class hkbBehaviorGraphInternalState : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraphInternalState;
		inline static constexpr auto VTABLE = VTABLE_hkbBehaviorGraphInternalState;

		hkbBehaviorGraphInternalState();
		~hkbBehaviorGraphInternalState() override;  // 00

		// members
		hkArray<hkRefPtr<hkbNodeInternalStateInfo>> nodeInternalStateInfos;  // 10
		hkRefPtr<hkbVariableValueSet>               variableValueSet;        // 20
	};
	static_assert(offsetof(hkbBehaviorGraphInternalState, nodeInternalStateInfos) == 0x10);
	static_assert(offsetof(hkbBehaviorGraphInternalState, variableValueSet) == 0x20);
	static_assert(sizeof(hkbBehaviorGraphInternalState) == 0x28);
}
