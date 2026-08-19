#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	struct hkbGeneratorOutput;
	struct hkbNodeInfo;

	class hkbGenerator : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbGenerator;

		~hkbGenerator() override;  // 00

		// override (hkbNode)
		bool IsGenerator(void) const override;  // 15 - { return true; }

		// add
		virtual void Generate(
			const hkbContext& a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput& a_output,
			float a_timeOffset = 0.0f) const = 0;                       // 17
		virtual bool CanRecycleOutput(void) const;                     // 18 - { return false; }
		virtual void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info);  // 19
		virtual void SetLocalTime(float a_time);                        // 1A
		virtual void StartEcho(void);                                   // 1B
	};
	static_assert(sizeof(hkbGenerator) == 0x48);
}
