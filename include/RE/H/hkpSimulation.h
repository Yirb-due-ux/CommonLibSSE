#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpWorld;

	class hkpSimulation : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSimulation;
		inline static constexpr auto VTABLE = VTABLE_hkpSimulation;

		~hkpSimulation() override;  // 00

		// members
		std::uint64_t unk10;               // 10
		hkpWorld*     world;               // 18
		std::uint32_t unk20;               // 20
		float         currentTime;         // 24
		float         currentPsiTime;      // 28
		float         physicsDeltaTime;    // 2C
		float         simulateUntilTime;   // 30
		std::uint32_t unk34;               // 34
		std::uint32_t previousStepResult;  // 38
		std::uint32_t pad3C;               // 3C
	};
	static_assert(sizeof(hkpSimulation) == 0x40);
}
