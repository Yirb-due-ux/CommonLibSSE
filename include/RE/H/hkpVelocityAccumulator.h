#pragma once

#include "RE/H/hkVector4.h"

namespace RE
{
	class hkpVelocityAccumulator
	{
	public:
		enum class Type : std::uint8_t
		{
			kRigidBody,
			kKeyframedRigidBody,
			kNoGravityRigidBody
		};

		enum class Context : std::uint8_t
		{
			kBuildJacobians,
			kSolver
		};

		// members
		REX::EnumSet<Type, std::uint8_t>    type;               // 00
		REX::EnumSet<Context, std::uint8_t> context;            // 01
		std::uint16_t                       pad02;              // 02
		std::uint32_t                       deactivationClass;  // 04
		float                               gravityFactor;      // 08
		std::uint32_t                       pad0C;              // 0C
		hkVector4                           linearVelocity;     // 10
		hkVector4                           angularVelocity;    // 20
		hkVector4                           invMasses;          // 30
		hkVector4                           scratch[4];         // 40
	};
	static_assert(sizeof(hkpVelocityAccumulator) == 0x80);
}
