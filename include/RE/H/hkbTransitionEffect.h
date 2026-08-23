#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbTransitionEffect : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbTransitionEffect;

		enum class SelfTransitionMode
		{
			kContinueIfCyclicBlendIfAcyclic = 0,
			kContinue = 1,
			kReset = 2,
			kBlend = 3
		};

		enum class EventMode
		{
			kDefault = 0,
			kProcessAll = 1,
			kIgnoreFromGenerator = 2,
			kIgnoreToGenerator = 3
		};

		~hkbTransitionEffect() override;  // 00

		// override (hkbNode)
		bool IsTransitionEffect(void) const override;  // 13 - { return true; }

		// add
		virtual bool  IsDone(void) = 0;                                     // 1C
		virtual void  SetFromGenerator(hkbGenerator* a_fromGenerator) = 0;  // 1D
		virtual void  SetToGenerator(hkbGenerator* a_toGenerator) = 0;      // 1E
		virtual float GetFromGeneratorBlendOutTime(void) = 0;               // 1F
		virtual float GetToGeneratorBlendInTime(void) = 0;                  // 20

		// members
		REX::EnumSet<SelfTransitionMode, std::int8_t> selfTransitionMode;  // 48 - Behavior when the to-generator is already active.
		REX::EnumSet<EventMode, std::int8_t>          eventMode;           // 49 - Event handling for the from- and to-generators.
		REX::EnumSet<EventMode, std::int8_t>          defaultEventMode;    // 4A - Used when eventMode is kDefault.
		std::uint8_t                                  pad4B[5];            // 4B
	};
	static_assert(offsetof(hkbTransitionEffect, selfTransitionMode) == 0x48);
	static_assert(offsetof(hkbTransitionEffect, defaultEventMode) == 0x4A);
	static_assert(sizeof(hkbTransitionEffect) == 0x50);
}
