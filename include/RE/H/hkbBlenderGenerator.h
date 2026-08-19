#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbBlenderGeneratorChild : public hkbBindable
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlenderGeneratorChild;

		~hkbBlenderGeneratorChild() override;  // 00

		// members
		hkRefPtr<hkbGenerator> generator;             // 30
		hkRefVariant           boneWeights;           // 38
		float                  weight;                // 40
		float                  worldFromModelWeight;  // 44
		std::uint64_t          pad48;                 // 48
	};
	static_assert(sizeof(hkbBlenderGeneratorChild) == 0x50);

	class hkbBlenderGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlenderGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbBlenderGenerator;

		enum Flags
		{
			kFlagSyncCycles = 1 << 0,
			kFlagSmoothGeneratorWeights = 1 << 2,
			kFlagDontDeactivateChildrenWithZeroWeights = 1 << 3,
			kFlagParametricBlend = 1 << 4,
			kFlagIsParametricBlendCyclic = 1 << 5,
			kFlagForceDensePose = 1 << 6
		};

		~hkbBlenderGenerator() override;  // 00

		// override (hkbGenerator)
		void Activate(const hkbContext& a_context) override;                  // 04
		void Update(const hkbContext& a_context, float a_timestep) override;  // 05
		void Deactivate(const hkbContext& a_context) override;                // 07
		void Generate(
			const hkbContext& a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput& a_output,
			float a_timeOffset = 0.0f) const override;                                // 17
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;  // 19

		// members
		float                              referencePoseWeightThreshold;  // 048
		float                              blendParameter;                // 04C
		float                              minCyclicBlendParameter;       // 050
		float                              maxCyclicBlendParameter;       // 054
		std::int16_t                       indexOfSyncMasterChild;        // 058
		std::int16_t                       flags;                         // 05A
		bool                               subtractLastChild;             // 05C
		std::uint8_t                       pad05D;                        // 05D
		std::uint16_t                      pad05E;                        // 05E
		hkArray<hkbBlenderGeneratorChild*> children;                     // 060
		hkRefVariant                       childrenInternalStates;       // 070
		hkRefVariant                       sortedChildren;               // 078
		float                              endIntervalWeight;             // 080
		std::int32_t                       numActiveChildren;            // 084
		std::int16_t                       beginIntervalIndex;           // 088
		std::int16_t                       endIntervalIndex;             // 08A
		bool                               initSync;                     // 08C
		bool                               doSubtractiveBlend;           // 08D
		std::uint16_t                      pad08E;                        // 08E
	};
	static_assert(offsetof(hkbBlenderGenerator, blendParameter) == 0x04C);
	static_assert(offsetof(hkbBlenderGenerator, flags) == 0x05A);
	static_assert(offsetof(hkbBlenderGenerator, children) == 0x060);
	static_assert(offsetof(hkbBlenderGenerator, numActiveChildren) == 0x084);
	static_assert(sizeof(hkbBlenderGenerator) == 0x90);
}
