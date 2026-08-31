#pragma once

#include "RE/H/hkbBlendCurveUtils.h"
#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbBlenderGenerator;
	class hkbBlendingTransitionEffect;

	class BSCyclicBlendTransitionGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSCyclicBlendTransitionGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSCyclicBlendTransitionGenerator;

		enum class CurrentBlendMode : std::int8_t
		{
			kInactive = -1,
			kDefault = 0,
			kFrozen = 1,
			kBlending = 2,
			kWaitingForBlending = 3
		};

		~BSCyclicBlendTransitionGenerator() override;  // 00

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override;                                                                     // 01
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02

		// override (hkbNode)
		void                              Activate(const hkbContext& a_context) override;                                    // 04
		void                              Update(const hkbContext& a_context, float a_timestep) override;                    // 05
		void                              HandleEvent(const hkbContext& a_context, hkbEvent& a_event) override;              // 06
		void                              Deactivate(const hkbContext& a_context) override;                                  // 07
		std::int32_t                      GetMaxNumChildren(GetChildrenFlags a_flags) override;                              // 08
		void                              GetChildren(GetChildrenFlags a_flags, ChildrenInfo& a_childrenInfo) override;      // 09
		bool                              IsValid(hkStringPtr& a_errorString) const override;                                // 0A
		BSCyclicBlendTransitionGenerator* CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;  // 0C

		// override (hkbGenerator)
		void Generate(
			const hkbContext&          a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput&        a_output,
			float                      a_timeOffset = 0.0f) const override;              // 17
		bool CanRecycleOutput() const override;                                      // 18
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;    // 19

		// Skyrim SE 1.5.97 layout. The reflected member names are preserved.
		// members
		std::uint8_t                                             pad48[8];                     // 48
		hkbBlenderGenerator*                                    pBlenderGenerator;            // 50
		hkbEventBase                                            EventToFreezeBlendValue;      // 58
		hkbEventBase                                            EventToCrossBlend;            // 68
		float                                                   fBlendParameter;              // 78
		float                                                   fTransitionDuration;          // 7C
		REX::EnumSet<hkbBlendCurveUtils::BlendCurve, std::int8_t> eBlendCurve;                  // 80
		std::uint8_t                                             pad81[15];                    // 81
		hkbBlenderGenerator*                                    pTransitionBlenderGenerator;  // 90 - Runtime clone of pBlenderGenerator.
		std::uint8_t                                             pad98[8];                     // 98
		hkbBlendingTransitionEffect*                            pTransitionEffect;            // A0 - Runtime transition effect.
		REX::EnumSet<CurrentBlendMode, std::int8_t>              currentMode;                  // A8
		std::uint8_t                                             padA9[7];                     // A9
	};
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, pBlenderGenerator) == 0x50);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, EventToFreezeBlendValue) == 0x58);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, EventToCrossBlend) == 0x68);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, fBlendParameter) == 0x78);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, fTransitionDuration) == 0x7C);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, eBlendCurve) == 0x80);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, pTransitionBlenderGenerator) == 0x90);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, pTransitionEffect) == 0xA0);
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, currentMode) == 0xA8);
	static_assert(std::is_base_of_v<hkbGenerator, BSCyclicBlendTransitionGenerator>);
	static_assert(!std::is_abstract_v<BSCyclicBlendTransitionGenerator>);
	static_assert(sizeof(BSCyclicBlendTransitionGenerator) == 0xB0);
}
