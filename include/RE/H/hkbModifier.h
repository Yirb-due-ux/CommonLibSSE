#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	class hkbGeneratorSyncInfo;
	struct hkbGeneratorOutput;

	class hkbModifier : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbModifier;

		~hkbModifier() override;  // 00

		// Skyrim SE 1.5.97 adds exactly these two slots after hkbNode.
		virtual void Modify(const hkbContext& a_context, hkbGeneratorOutput& a_output);          // 17
		virtual void ModifySyncInfo(const hkbContext& a_context, hkbGeneratorSyncInfo& a_info);  // 18

		// members
		bool         enable;    // 48
		std::uint8_t pad49[7];  // 49
	};
	static_assert(offsetof(hkbModifier, enable) == 0x48);
	static_assert(sizeof(hkbModifier) == 0x50);
}
