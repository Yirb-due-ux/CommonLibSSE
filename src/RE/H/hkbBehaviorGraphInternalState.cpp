#include "RE/H/hkbBehaviorGraphInternalState.h"

#include "RE/H/hkbVariableValueSet.h"

namespace RE
{
	hkbBehaviorGraphInternalState::hkbBehaviorGraphInternalState() :
		nodeInternalStateInfos{},
		variableValueSet{}
	{
		nodeInternalStateInfos._capacityAndFlags = static_cast<std::int32_t>(decltype(nodeInternalStateInfos)::kDontDeallocFlag);
		stl::emplace_vtable(this);
	}

	hkbBehaviorGraphInternalState::~hkbBehaviorGraphInternalState()
	{
		using func_t = void(hkbBehaviorGraphInternalState*);
		static REL::Relocation<func_t> func{ REL::ID(58322) };
		func(this);
	}
}
