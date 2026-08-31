#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkPointerMap.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkbGenerator.h"
#include "RE/H/hkbNodeInfo.h"

namespace RE
{
	class hkbBehaviorGraphData;

	class hkbBehaviorGraph : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraph;
		inline static constexpr auto VTABLE = VTABLE_hkbBehaviorGraph;

		enum class VariableMode
		{
			kDiscardWhenActive = 0,
			kMaintainValuesWhenInactive = 1,
		};

		~hkbBehaviorGraph() override;  // 00

		// override (hkbGenerator)
		hkClass* GetClassType() const override;                                                                     // 01
		void     CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02
		void     Activate(const hkbContext& a_context) override;                                                    // 04
		void     Update(const hkbContext& a_context, float a_timestep) override;                                    // 05
		void     HandleEvent(const hkbContext& a_context, hkbEvent& a_event) override;                              // 06
		void     Deactivate(const hkbContext& a_context) override;                                                  // 07
		void     GetChildren(GetChildrenFlags a_flags, ChildrenInfo& a_childrenInfo) override;                      // 09
		hkbNode* CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;                                        // 0C
		bool     IsGraph(void) const override;                                                                      // 16 - { return true; }
		void     Generate(
			const hkbContext& a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput& a_output,
			float a_timeOffset = 0.0f) const override;                                                               // 17
		bool     CanRecycleOutput(void) const override;                                                             // 18 - { return true; }
		void     UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;                              // 19

		// Returns an existing runtime clone, or the input node when no clone is required or mapped.
		[[nodiscard]] hkbNode* GetNodeClone(hkbNode* a_nodeTemplate) const;
		// Returns the mapped template for a runtime clone. Non-clone nodes are returned
		// unchanged; a clone missing from nodeCloneToTemplateMap returns nullptr.
		[[nodiscard]] hkbNode* GetNodeTemplate(hkbNode* a_nodeClone) const;

		// These map-backed lookups cover the current active-node set. A missing or invalid
		// entry returns nullptr instead of falling back to activeNodes[0].
		[[nodiscard]] hkbNodeInfo*       FindNodeInfoByTemplate(hkbNode* a_nodeTemplate);
		[[nodiscard]] const hkbNodeInfo* FindNodeInfoByTemplate(hkbNode* a_nodeTemplate) const;
		[[nodiscard]] hkbNodeInfo*       FindNodeInfoByClone(hkbNode* a_nodeClone);
		[[nodiscard]] const hkbNodeInfo* FindNodeInfoByClone(hkbNode* a_nodeClone) const;

		// members
		REX::EnumSet<VariableMode, std::uint8_t> variableMode;                     // 048
		std::uint8_t                             pad49;                            // 049
		std::uint16_t                            pad4A;                            // 04A
		std::uint32_t                            pad4C;                            // 04C
		hkArray<hkRefVariant>                    uniqueIDPool;                     // 050
		hkRefVariant                             idToStateMachineTemplateMap;      // 060
		hkArray<hkRefVariant>                    mirroredExternalIDMap;            // 068
		hkRefVariant                             pseudoRandomGenerator;            // 078
		hkRefPtr<hkbGenerator>                   rootGenerator;                    // 080
		hkRefPtr<hkbBehaviorGraphData>           data;                             // 088
		hkRefVariant                             rootGeneratorClone;               // 090
		NodeList*                                activeNodes;                      // 098
		hkPointerMap<hkbNode*, std::int32_t>*    activeNodeTemplateToIndexMap;     // 0A0 - Template to activeNodes index.
		hkArray<std::int32_t>*                   activeNodesChildrenIndices;       // 0A8 - Flattened child indices into activeNodes.
		hkRefVariant                             globalTransitionData;             // 0B0
		hkRefVariant                             eventIDMap;                       // 0B8
		hkRefVariant                             attributeIDMap;                   // 0C0
		hkRefVariant                             variableIDMap;                    // 0C8
		hkRefVariant                             characterPropertyIDMap;           // 0D0
		hkRefVariant                             variableValueSet;                 // 0D8
		hkPointerMap<hkbNode*, hkbNode*>*        nodeTemplateToCloneMap;           // 0E0
		hkPointerMap<hkbNode*, hkbNode*>*        nodeCloneToTemplateMap;           // 0E8
		hkRefVariant                             stateListenerTemplateToCloneMap;  // 0F0
		hkRefVariant                             nodePartitionInfo;                // 0F8
		std::int32_t                             numIntermediateOutputs;           // 100
		std::uint32_t                            pad104;                           // 104
		hkArray<hkRefVariant>                    jobs;                             // 108
		hkArray<hkRefVariant>                    allPartitionMemory;               // 118
		std::int16_t                             numStaticNodes;                   // 128
		std::int16_t                             nextUniqueID;                     // 12A
		bool                                     isActive;                         // 12C
		bool                                     isLinked;                         // 12D
		bool                                     updateActiveNodes;                // 12E
		bool                                     stateOrTransitionChanged;         // 12F
	};
	static_assert(offsetof(hkbBehaviorGraph, activeNodes) == 0x98);
	static_assert(offsetof(hkbBehaviorGraph, activeNodeTemplateToIndexMap) == 0xA0);
	static_assert(offsetof(hkbBehaviorGraph, activeNodesChildrenIndices) == 0xA8);
	static_assert(offsetof(hkbBehaviorGraph, nodeTemplateToCloneMap) == 0xE0);
	static_assert(offsetof(hkbBehaviorGraph, nodeCloneToTemplateMap) == 0xE8);
	static_assert(sizeof(hkbBehaviorGraph) == 0x130);
}
