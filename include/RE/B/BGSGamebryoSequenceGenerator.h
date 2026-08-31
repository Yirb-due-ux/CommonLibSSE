#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class NiControllerSequence;

	class BGSGamebryoSequenceTrigger
	{
	public:
		// members
		float         keyTime;  // 00 - Sequence text-key time.
		std::uint32_t pad04;    // 04
		hkbEventBase  event;    // 08
	};
	static_assert(offsetof(BGSGamebryoSequenceTrigger, keyTime) == 0x0);
	static_assert(offsetof(BGSGamebryoSequenceTrigger, pad04) == 0x4);
	static_assert(offsetof(BGSGamebryoSequenceTrigger, event) == 0x8);
	static_assert(sizeof(BGSGamebryoSequenceTrigger) == 0x18);

	class BGSGamebryoSequenceGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSGamebryoSequenceGenerator;
		inline static constexpr auto VTABLE = VTABLE_BGSGamebryoSequenceGenerator;

		enum class BlendModeFunction : std::uint8_t
		{
			kNone = 0,
			kPercent = 1,
			kOneMinusPercent = 2
		};

		~BGSGamebryoSequenceGenerator() override;  // 00

		// override (hkbNode)
		// Resets time and defers sequence activation until Update.
		void Activate(const hkbContext& a_context) override;  // 04
		// Advances the sequence and queues text-key events.
		void                          Update(const hkbContext& a_context, float a_timestep) override;  // 05
		void                          Deactivate(const hkbContext& a_context) override;                // 07
		bool                          IsValid(hkStringPtr& a_errorString) const override;              // 0A - requires pSequence
		BGSGamebryoSequenceGenerator* CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;      // 0C

		// override (hkbGenerator)
		void Generate(
			const hkbContext&          a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput&        a_output,
			float                      a_timeOffset = 0.0f) const override;                               // 17
		bool CanRecycleOutput() const override;                                      // 18 - { return true; }
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;  // 19
		void SetLocalTime(float a_time) override;                                    // 1A

		// Runtime bridge to the Gamebryo controller sequence. This is a non-owning
		// pointer stored in hkbNode::userData after delayed activation. Deactivation
		// does not clear it, so a non-null result does not by itself mean active.
		[[nodiscard]] NiControllerSequence* GetControllerSequence() const noexcept
		{
			return reinterpret_cast<NiControllerSequence*>(userData);
		}

		// Skyrim SE 1.5.97 layout. Only pSequence, eBlendModeFunction, and fPercent are serialized;
		// the remaining members are runtime state.
		// members
		char*                                         pSequence;           // 48 - NiControllerSequence name, not a file path.
		REX::EnumSet<BlendModeFunction, std::uint8_t> eBlendModeFunction;  // 50
		std::uint8_t                                  pad51[3];            // 51
		float                                         fPercent;            // 54 - Input for the sequence-level blend weight.
		hkArray<BGSGamebryoSequenceTrigger>           events;              // 58 - Runtime triggers built from sequence text keys.
		float                                         fTime;               // 68 - Runtime local sequence time.
		bool                                          bDelayedActivate;    // 6C - Runtime state.
		bool                                          bLooping;            // 6D - Runtime state.
		std::uint8_t                                  pad6E[2];            // 6E
	};
	static_assert(offsetof(BGSGamebryoSequenceGenerator, pSequence) == 0x48);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, eBlendModeFunction) == 0x50);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, fPercent) == 0x54);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, events) == 0x58);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, fTime) == 0x68);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, bDelayedActivate) == 0x6C);
	static_assert(offsetof(BGSGamebryoSequenceGenerator, bLooping) == 0x6D);
	static_assert(sizeof(BGSGamebryoSequenceGenerator) == 0x70);
}
