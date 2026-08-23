#include "RE/H/hkbBlendCurveUtils.h"

#ifndef SKYRIM_SUPPORT_AE
namespace RE
{
	float hkbBlendCurveUtils::EvaluateBlendCurve(BlendCurve a_blendCurve, float a_time)
	{
		using func_t = decltype(&hkbBlendCurveUtils::EvaluateBlendCurve);
		static REL::Relocation<func_t> func{ REL::ID(57875) };
		return func(a_blendCurve, a_time);
	}
}
#endif
