#include "RE/B/BGSFootIkRaycastInterfaceDB.h"

namespace RE
{
#ifndef SKYRIM_SUPPORT_AE
	BGSFootIkRaycastInterfaceDB* BGSFootIkRaycastInterfaceDB::GetSingleton()
	{
		static REL::Relocation<BGSFootIkRaycastInterfaceDB**> singleton{ SingletonID };
		return *singleton;
	}

	bool BGSFootIkRaycastInterfaceDB::GetSkipZ(TESObjectREFR* a_ref, std::uint8_t* a_skipZ) const
	{
		using func_t = decltype(&BGSFootIkRaycastInterfaceDB::GetSkipZ);
		static REL::Relocation<func_t> func{ GetSkipZID };
		return func(this, a_ref, a_skipZ);
	}
#endif
}
