#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkPointerMap.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbContext.h"

namespace RE
{
	class hkbBehaviorGraph;
	class hkbEvent;
	class hkbNode;
	class hkbNodeInternalStateInfo;

	struct hkbNodeChildInfo
	{
		hkbNode*      node{ nullptr };        // 00 - child node
		bool          ignoreEvents{ false };  // 08
		bool          reset{ false };         // 09
		bool          syncToParent{ false };  // 0A
		bool          stopped{ false };       // 0B
		std::uint32_t pad0C;                  // 0C
	};
	static_assert(offsetof(hkbNodeChildInfo, node) == 0x0);
	static_assert(offsetof(hkbNodeChildInfo, stopped) == 0xB);
	static_assert(sizeof(hkbNodeChildInfo) == 0x10);

	class hkbNode : public hkbBindable
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNode;
		inline static constexpr auto VTABLE = VTABLE_hkbNode;

		struct ChildrenInfo
		{
			ChildrenInfo(hkArray<hkbNodeChildInfo>& a_childInfos) :
				childInfos(a_childInfos)
			{}

			hkArray<hkbNodeChildInfo>& childInfos;    // 00
			bool                       ignoreEvents;  // 08
			bool                       reset;         // 09
			bool                       syncToParent;  // 0A
			std::uint8_t               unk0B;         // 0B
			std::uint32_t              pad0C;         // 0C
		};
		static_assert(offsetof(ChildrenInfo, childInfos) == 0x0);
		static_assert(offsetof(ChildrenInfo, syncToParent) == 0xA);
		static_assert(sizeof(ChildrenInfo) == 0x10);

		enum class GetChildrenFlagBits : std::int32_t
		{
			kActiveOnly = 1 << 0,
			kGeneratorsOnly = 1 << 1,
			kIgnoreReferencedBehaviour = 1 << 2
		};
		using GetChildrenFlags = REX::EnumSet<GetChildrenFlagBits, std::int32_t>;
		static_assert(sizeof(GetChildrenFlags) == 0x4);

		~hkbNode() override;  // 00

		// add
		virtual void                Activate(const hkbContext& a_context);                                                                    // 04 - { return; }
		virtual void                Update(const hkbContext& a_context, float a_timestep);                                                    // 05 - { userData |= 1; }
		virtual void                HandleEvent(const hkbContext& a_context, hkbEvent& a_event);                                              // 06 - { return; }
		virtual void                Deactivate(const hkbContext& a_context);                                                                  // 07 - { return; }
		virtual std::int32_t        GetMaxNumChildren(GetChildrenFlags a_flags);                                                              // 08 - { return 2; }
		virtual void                GetChildren(GetChildrenFlags a_flags, ChildrenInfo& a_childrenInfo);                                      // 09 - { return; }
		virtual bool                IsValid(hkStringPtr& a_errorString) const;                                                                // 0A - { return true; }
		virtual void                Precompute(const hkbContext& a_context);                                                                  // 0B - { return; }
		virtual hkbNode*            CloneNode(hkbBehaviorGraph& a_rootBehavior) const;                                                        // 0C
		virtual hkReferencedObject* CreateInternalState();                                                                                    // 0D - { return nullptr; }
		virtual void                GetInternalState(hkReferencedObject& a_internalState) const;                                              // 0E - { return; }
		virtual void                GetInternalStateUser(const hkbBehaviorGraph& a_rootBehavior, hkReferencedObject& a_internalState) const;  // 0F - { return; }
		virtual void                SetInternalState(const hkReferencedObject& a_internalState);                                              // 10 - { return; }
		virtual void                SetInternalStateUser(
			const hkbContext&                                            a_context,
			const hkReferencedObject&                                    a_internalState,
			hkPointerMap<std::int16_t, const hkbNodeInternalStateInfo*>& a_nodeIdToInternalStateMap);       // 11 - { return; }
		virtual void GetActiveEvents(hkPointerMap<std::int32_t, bool>& a_activeEvents) const;               // 12 - { return; }
		virtual bool IsTransitionEffect(void) const;                                                        // 13 - { return false; }
		virtual void GetActiveVariablesSpecial(hkPointerMap<std::int32_t, bool>& a_activeVariables) const;  // 14 - { return; }
		virtual bool IsGenerator(void) const;                                                               // 15 - { return false; }
		virtual bool IsGraph(void) const;                                                                   // 16 - { return false; }

		enum class CloneState
		{
			kDefault = 0,
			kTemplate = 1,
			kClone = 2,
			kShareable = 3
		};

		// members
		std::uint64_t                          userData;    // 30
		hkStringPtr                            name;        // 38
		std::uint16_t                          id;          // 40
		REX::EnumSet<CloneState, std::uint8_t> cloneState;  // 42
		std::uint8_t                           pad43;       // 43
		std::uint32_t                          pad44;       // 44
	};
	static_assert(sizeof(hkbNode) == 0x48);
}
