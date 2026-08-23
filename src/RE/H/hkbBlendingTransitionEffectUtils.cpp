#include "RE/H/hkbBlendingTransitionEffectUtils.h"

#ifndef SKYRIM_SUPPORT_AE
namespace RE
{
	void hkbBlendingTransitionEffectUtils::GenerateInternal(
		const hkbBlendingTransitionEffect& a_effect,
		float                              a_timeOffset,
		hkQsTransform*                     a_pose,
		const hkbGeneratorOutput**         a_activeChildrenOutput,
		hkbGeneratorOutput&                a_output)
	{
		using func_t = decltype(&hkbBlendingTransitionEffectUtils::GenerateInternal);
		static REL::Relocation<func_t> func{ REL::ID(59402) };
		func(a_effect, a_timeOffset, a_pose, a_activeChildrenOutput, a_output);
	}
}
#endif
