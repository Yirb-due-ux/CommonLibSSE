#pragma once

namespace RE
{
	class TESObjectREFR;

#ifndef SKYRIM_SUPPORT_AE
	// Borrowed native view; storage and virtual interfaces are not modeled.
	class BGSFootIkRaycastInterfaceDB
	{
	public:
		inline static constexpr auto    RTTI = RTTI_BGSFootIkRaycastInterfaceDB;
		inline static constexpr auto    VTABLE = VTABLE_BGSFootIkRaycastInterfaceDB;
		inline static constexpr REL::ID GetSkipZID{ 31987 };
		inline static constexpr REL::ID SingletonID{ 514961 };

		static BGSFootIkRaycastInterfaceDB* GetSingleton();

		// Returns whether a live entry matched; on failure a_skipZ is unchanged.
		bool GetSkipZ(TESObjectREFR* a_ref, std::uint8_t* a_skipZ) const;

	private:
		BGSFootIkRaycastInterfaceDB() = delete;
		BGSFootIkRaycastInterfaceDB(const BGSFootIkRaycastInterfaceDB&) = delete;
		BGSFootIkRaycastInterfaceDB& operator=(const BGSFootIkRaycastInterfaceDB&) = delete;
		~BGSFootIkRaycastInterfaceDB() = delete;
	};
#endif
}
