#include "RE/H/hkbBehaviorGraph.h"

namespace RE
{
	hkbNode* hkbBehaviorGraph::GetNodeClone(hkbNode* a_nodeTemplate) const
	{
		using func_t = decltype(&hkbBehaviorGraph::GetNodeClone);
		static REL::Relocation<func_t> func{ REL::ID(57786) };
		return func(this, a_nodeTemplate);
	}

	hkbNode* hkbBehaviorGraph::GetNodeTemplate(hkbNode* a_nodeClone) const
	{
		using func_t = decltype(&hkbBehaviorGraph::GetNodeTemplate);
		static REL::Relocation<func_t> func{ REL::ID(57791) };
		return func(this, a_nodeClone);
	}

	hkbNodeInfo* hkbBehaviorGraph::FindNodeInfoByTemplate(hkbNode* a_nodeTemplate)
	{
		return const_cast<hkbNodeInfo*>(static_cast<const hkbBehaviorGraph*>(this)->FindNodeInfoByTemplate(a_nodeTemplate));
	}

	const hkbNodeInfo* hkbBehaviorGraph::FindNodeInfoByTemplate(hkbNode* a_nodeTemplate) const
	{
		if (!a_nodeTemplate || !activeNodes || !activeNodeTemplateToIndexMap) {
			return nullptr;
		}

		const auto index = activeNodeTemplateToIndexMap->GetWithDefault(a_nodeTemplate, -1);
		return index >= 0 && index < activeNodes->size() ? activeNodes->data() + index : nullptr;
	}

	hkbNodeInfo* hkbBehaviorGraph::FindNodeInfoByClone(hkbNode* a_nodeClone)
	{
		return const_cast<hkbNodeInfo*>(static_cast<const hkbBehaviorGraph*>(this)->FindNodeInfoByClone(a_nodeClone));
	}

	const hkbNodeInfo* hkbBehaviorGraph::FindNodeInfoByClone(hkbNode* a_nodeClone) const
	{
		if (!a_nodeClone) {
			return nullptr;
		}

		auto* nodeTemplate = GetNodeTemplate(a_nodeClone);
		return nodeTemplate ? FindNodeInfoByTemplate(nodeTemplate) : nullptr;
	}
}
