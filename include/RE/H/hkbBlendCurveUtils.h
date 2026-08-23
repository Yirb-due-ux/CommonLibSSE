#pragma once

namespace RE
{
	class hkbBlendCurveUtils
	{
	public:
		enum class BlendCurve
		{
			kSmooth = 0,          // 3t^2 - 2t^3
			kLinear = 1,          // t
			kLinearToSmooth = 2,  // t + t^2 - t^3
			kSmoothToLinear = 3   // 2t^2 - t^3
		};

#ifndef SKYRIM_SUPPORT_AE
		// Evaluates a normalized transition fraction and clamps the result to [0, 1].
		// The relocation is verified against Skyrim SE 1.5.97.
		[[nodiscard]] static float EvaluateBlendCurve(BlendCurve a_blendCurve, float a_time);
#endif
	};
	static_assert(sizeof(hkbBlendCurveUtils::BlendCurve) == 0x4);
	static_assert(sizeof(hkbBlendCurveUtils) == 0x1);
}
