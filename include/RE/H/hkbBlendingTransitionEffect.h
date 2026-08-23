#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkbBlendCurveUtils.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	class hkbBehaviorGraph;
	class hkbGeneratorSyncInfo;

	class hkbBlendingTransitionEffectInternalState : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlendingTransitionEffectInternalState;
		inline static constexpr auto VTABLE = VTABLE_hkbBlendingTransitionEffectInternalState;

		~hkbBlendingTransitionEffectInternalState() override;  // 00

		// members
		hkArray<hkQsTransform> characterPoseAtBeginningOfTransition;  // 10
		float                  timeRemaining;                         // 20
		float                  timeInTransition;                      // 24
		bool                   applySelfTransition;                   // 28
		bool                   initializeCharacterPose;               // 29
		std::uint8_t           pad2A[6];                              // 2A
	};
	static_assert(offsetof(hkbBlendingTransitionEffectInternalState, timeRemaining) == 0x20);
	static_assert(sizeof(hkbBlendingTransitionEffectInternalState) == 0x30);

	class hkbBlendingTransitionEffect : public hkbTransitionEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlendingTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbBlendingTransitionEffect;

		enum class FlagBits
		{
			kNone = 0,
			kIgnoreFromWorldFromModel = 1 << 0,  // Use only the to-generator world-from-model.
			kSync = 1 << 1,                      // Synchronize the child generator cycles.
			kIgnoreToWorldFromModel = 1 << 2     // Use only the from-generator world-from-model.
		};
		using Flags = REX::EnumSet<FlagBits, std::uint16_t>;

		enum class EndMode
		{
			kNone = 0,
			kTransitionUntilEndOfFromGenerator = 1,
			kCapDurationAtEndOfFromGenerator = 2
		};

		~hkbBlendingTransitionEffect() override;  // 00

		// override (hkbNode)
		void Activate(const hkbContext& a_context) override;                  // 04
		void Update(const hkbContext& a_context, float a_timestep) override;  // 05
		void Deactivate(const hkbContext& a_context) override;                // 07

		// override (hkbGenerator)
		void Generate(
			const hkbContext&          a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput&        a_output,
			float                      a_timeOffset = 0.0f) const override;                               // 17
		bool CanRecycleOutput(void) const override;                                  // 18
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;  // 19

		// override (hkbTransitionEffect)
		bool  IsDone(void) override;                                     // 1C
		void  SetFromGenerator(hkbGenerator* a_fromGenerator) override;  // 1D
		void  SetToGenerator(hkbGenerator* a_toGenerator) override;      // 1E
		float GetFromGeneratorBlendOutTime(void) override;               // 1F
		float GetToGeneratorBlendInTime(void) override;                  // 20

		// add
		virtual bool                        IsSyncable(hkbBehaviorGraph& a_behaviorGraph);                // 21
		virtual bool                        HasToGeneratorBeenActivatedInThisFrame(void) const;           // 22
		virtual bool                        UseFromGeneratorToSyncOnly(void) const;                       // 23
		virtual const hkbGeneratorSyncInfo& GetFromGeneratorSyncInfo(hkbBehaviorGraph& a_behaviorGraph);  // 24
		virtual float                       GetTransitionDuration(void) const;                            // 25
		virtual bool                        IsFirstFrame(void) const;                                     // 26

		// members
		float                                                     duration;                              // 50 - Duration of the transition.
		float                                                     toGeneratorStartTimeFraction;          // 54 - Initial local-time fraction of the to-generator.
		Flags                                                     flags;                                 // 58
		REX::EnumSet<EndMode, std::int8_t>                        endMode;                               // 5A
		REX::EnumSet<hkbBlendCurveUtils::BlendCurve, std::int8_t> blendCurve;                            // 5B
		std::uint32_t                                             pad5C;                                 // 5C
		hkbGenerator*                                             fromGenerator;                         // 60
		hkbGenerator*                                             toGenerator;                           // 68
		hkArray<hkQsTransform>                                    characterPoseAtBeginningOfTransition;  // 70
		float                                                     timeRemaining;                         // 80
		float                                                     timeInTransition;                      // 84
		bool                                                      applySelfTransition;                   // 88
		bool                                                      initializeCharacterPose;               // 89
		std::uint8_t                                              pad8A[6];                              // 8A
	};
	static_assert(offsetof(hkbBlendingTransitionEffect, duration) == 0x50);
	static_assert(offsetof(hkbBlendingTransitionEffect, flags) == 0x58);
	static_assert(offsetof(hkbBlendingTransitionEffect, blendCurve) == 0x5B);
	static_assert(offsetof(hkbBlendingTransitionEffect, fromGenerator) == 0x60);
	static_assert(offsetof(hkbBlendingTransitionEffect, timeRemaining) == 0x80);
	static_assert(offsetof(hkbBlendingTransitionEffect, timeInTransition) == 0x84);
	static_assert(sizeof(hkbBlendingTransitionEffect) == 0x90);
}
