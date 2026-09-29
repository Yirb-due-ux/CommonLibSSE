#pragma once

#include "RE/H/hkbBlendingTransitionEffect.h"

namespace RE
{
	class hkbBlendingTransitionEffectUtils
	{
	public:
#ifndef SKYRIM_SUPPORT_AE
		static void GenerateInternal(
			const hkbBlendingTransitionEffect& a_effect,
			float                              a_timeOffset,
			hkQsTransform*                     a_pose,
			const hkbGeneratorOutput**         a_activeChildrenOutput,
			hkbGeneratorOutput&                a_output);
#endif
	};
}
