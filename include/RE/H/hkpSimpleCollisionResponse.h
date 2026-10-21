#pragma once

namespace RE
{
	class hkContactPoint;
	class hkpDynamicsContactMgr;
	class hkpMotion;
	struct hkpSimpleConstraintUtilCollideParams;

	class hkpSimpleCollisionResponse
	{
	public:
		struct SolveSingleOutput
		{
			float impulse;             // 0
			float velocityKeyframedA;  // 4
			float velocityKeyframedB;  // 8
		};
		static_assert(sizeof(SolveSingleOutput) == 0xC);

#ifndef SKYRIM_SUPPORT_AE
		// SE 1.5.97
		inline static constexpr REL::ID SolveSingleContactID{ 61432 };

		static void SolveSingleContact(const hkContactPoint& a_contactPoint, float a_time, hkpSimpleConstraintUtilCollideParams& a_params, hkpMotion* a_bodyA, hkpMotion* a_bodyB, hkpDynamicsContactMgr* a_contactMgr, SolveSingleOutput& a_output)
		{
			using func_t = decltype(&hkpSimpleCollisionResponse::SolveSingleContact);
			static REL::Relocation<func_t> func{ SolveSingleContactID };
			func(a_contactPoint, a_time, a_params, a_bodyA, a_bodyB, a_contactMgr, a_output);
		}
#endif
	};
}
