#pragma once

#include "RE/H/hkStepInfo.h"
#include "RE/H/hkpMotion.h"
#include "RE/H/hkpSolverInfo.h"
#include "RE/H/hkpVelocityAccumulator.h"

namespace RE
{
#ifndef SKYRIM_SUPPORT_AE
	// SE 1.5.97
	inline constexpr REL::ID hkRigidMotionUtilApplyForcesAndBuildAccumulatorsID{ 61368 };
	inline constexpr REL::ID hkRigidMotionUtilApplyForcesAndStepID{ 61366 };
	inline constexpr REL::ID hkRigidMotionUtilApplyAccumulatorsID{ 61369 };

	inline hkpVelocityAccumulator* hkRigidMotionUtilApplyForcesAndBuildAccumulators(const hkStepInfo& a_info, hkpMotion* const* a_motions, std::int32_t a_numMotions, std::int32_t a_motionOffset, hkpVelocityAccumulator* a_accumulatorsOut)
	{
		using func_t = decltype(&hkRigidMotionUtilApplyForcesAndBuildAccumulators);
		static REL::Relocation<func_t> func{ hkRigidMotionUtilApplyForcesAndBuildAccumulatorsID };
		return func(a_info, a_motions, a_numMotions, a_motionOffset, a_accumulatorsOut);
	}

	inline std::int32_t hkRigidMotionUtilApplyForcesAndStep(const hkpSolverInfo& a_solverInfo, const hkStepInfo& a_info, const hkVector4& a_deltaVelocity, hkpMotion* const* a_motions, std::int32_t a_numMotions, std::int32_t a_motionOffset)
	{
		using func_t = decltype(&hkRigidMotionUtilApplyForcesAndStep);
		static REL::Relocation<func_t> func{ hkRigidMotionUtilApplyForcesAndStepID };
		return func(a_solverInfo, a_info, a_deltaVelocity, a_motions, a_numMotions, a_motionOffset);
	}

	inline std::int32_t hkRigidMotionUtilApplyAccumulators(const hkpSolverInfo& a_solverInfo, const hkStepInfo& a_info, const hkpVelocityAccumulator* a_accumulators, hkpMotion* const* a_motions, std::int32_t a_numMotions, std::int32_t a_motionOffset)
	{
		using func_t = decltype(&hkRigidMotionUtilApplyAccumulators);
		static REL::Relocation<func_t> func{ hkRigidMotionUtilApplyAccumulatorsID };
		return func(a_solverInfo, a_info, a_accumulators, a_motions, a_numMotions, a_motionOffset);
	}
#endif
}
