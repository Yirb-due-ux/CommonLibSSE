#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbGenerator.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	class hkbCondition;
	class hkbStateChooser;

	class hkbStateMachine : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachine;
		inline static constexpr auto VTABLE = VTABLE_hkbStateMachine;

		enum class StartStateMode
		{
			kDefault = 0,
			kSync = 1,
			kRandom = 2,
			kChooser = 3
		};

		enum class StateMachineSelfTransitionMode
		{
			kNoTransition = 0,
			kTransitionToStartState = 1,
			kForceTransitionToStartState = 2
		};

		class TransitionInfoArray;

		// Verified against Skyrim SE 1.5.97 reflection metadata and the native
		// 0x48/0x28/0x18 transition, active-transition, and delayed-transition strides.
		struct TimeInterval
		{
			std::int32_t enterEventID;  // 00
			std::int32_t exitEventID;   // 04
			float        enterTime;     // 08
			float        exitTime;      // 0C
		};
		static_assert(sizeof(TimeInterval) == 0x10);

		struct TransitionInfo
		{
			enum class FlagBits
			{
				kNone = 0,
				kUseTriggerInterval = 1 << 0,
				kUseInitiateInterval = 1 << 1,
				kUninterruptibleWhilePlaying = 1 << 2,
				kUninterruptibleWhileDelayed = 1 << 3,
				kDelayStateChange = 1 << 4,
				kDisabled = 1 << 5,
				kDisallowReturnToPreviousState = 1 << 6,
				kDisallowRandomTransition = 1 << 7,
				kDisableCondition = 1 << 8,
				kAllowSelfTransitionByTransitionFromAnyState = 1 << 9,
				kIsGlobalWildcard = 1 << 10,
				kIsLocalWildcard = 1 << 11,
				kFromNestedStateIDIsValid = 1 << 12,
				kToNestedStateIDIsValid = 1 << 13,
				kAbutAtEndOfFromGenerator = 1 << 14
			};
			using Flags = REX::EnumSet<FlagBits, std::uint16_t>;

			TimeInterval                  triggerInterval;    // 00
			TimeInterval                  initiateInterval;   // 10
			hkRefPtr<hkbTransitionEffect> transition;         // 20
			hkRefPtr<hkbCondition>        condition;          // 28
			std::int32_t                  eventID;            // 30
			std::int32_t                  toStateID;          // 34
			std::int32_t                  fromNestedStateID;  // 38
			std::int32_t                  toNestedStateID;    // 3C
			std::int16_t                  priority;           // 40 - Compared as a signed value; higher values win.
			Flags                         flags;              // 42
			std::uint32_t                 pad44;              // 44
		};
		static_assert(offsetof(TransitionInfo, transition) == 0x20);
		static_assert(offsetof(TransitionInfo, priority) == 0x40);
		static_assert(offsetof(TransitionInfo, flags) == 0x42);
		static_assert(sizeof(TransitionInfo) == 0x48);

		struct TransitionInfoReference
		{
			inline static constexpr std::int16_t kWildcardStateIndex = -1;
			inline static constexpr std::int16_t kSameStateMachineID = -1;

			std::int16_t fromStateIndex;   // 00 - -1 selects wildcard transitions.
			std::int16_t transitionIndex;  // 02
			std::int16_t stateMachineID;   // 04 - -1 selects this state machine.
		};
		static_assert(sizeof(TransitionInfoReference) == 0x6);

		struct ProspectiveTransitionInfo
		{
			TransitionInfoReference transitionInfoReference;       // 00
			TransitionInfoReference transitionInfoReferenceForTE;  // 06
			std::int32_t            toStateID;                     // 0C
		};
		static_assert(offsetof(ProspectiveTransitionInfo, transitionInfoReferenceForTE) == 0x6);
		static_assert(offsetof(ProspectiveTransitionInfo, toStateID) == 0xC);
		static_assert(sizeof(ProspectiveTransitionInfo) == 0x10);

		struct ActiveTransitionInfo
		{
			hkbTransitionEffect*    transitionEffect;                   // 00
			hkRefVariant            transitionEffectInternalStateInfo;  // 08
			TransitionInfoReference transitionInfoReference;            // 10
			TransitionInfoReference transitionInfoReferenceForTE;       // 16
			std::int32_t            fromStateID;                        // 1C
			std::int32_t            toStateID;                          // 20
			bool                    isReturnToPreviousState;            // 24
			std::uint8_t            pad25[3];                           // 25
		};
		static_assert(offsetof(ActiveTransitionInfo, transitionEffectInternalStateInfo) == 0x8);
		static_assert(offsetof(ActiveTransitionInfo, transitionInfoReference) == 0x10);
		static_assert(offsetof(ActiveTransitionInfo, fromStateID) == 0x1C);
		static_assert(offsetof(ActiveTransitionInfo, toStateID) == 0x20);
		static_assert(sizeof(ActiveTransitionInfo) == 0x28);

		struct DelayedTransitionInfo
		{
			ProspectiveTransitionInfo delayedTransition;                         // 00
			float                     timeDelayed;                               // 10
			bool                      isDelayedTransitionReturnToPreviousState;  // 14
			bool                      wasInAbutRangeLastFrame;                   // 15
			std::uint8_t              pad16[2];                                  // 16
		};
		static_assert(offsetof(DelayedTransitionInfo, timeDelayed) == 0x10);
		static_assert(offsetof(DelayedTransitionInfo, wasInAbutRangeLastFrame) == 0x15);
		static_assert(sizeof(DelayedTransitionInfo) == 0x18);

		class StateInfo : public hkbBindable
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__StateInfo;
			inline static constexpr auto VTABLE = VTABLE_hkbStateMachine__StateInfo;

			~StateInfo() override;  // 00

			// members
			hkArray<hkRefVariant>         listeners;          // 30
			hkRefVariant                  enterNotifyEvents;  // 40
			hkRefVariant                  exitNotifyEvents;   // 48
			hkRefPtr<TransitionInfoArray> transitions;        // 50
			hkRefPtr<hkbGenerator>        generator;          // 58
			hkStringPtr                   name;               // 60
			std::int32_t                  stateID;            // 68
			float                         probability;        // 6C
			bool                          enable;             // 70
			std::uint8_t                  pad71[7];           // 71
		};
		static_assert(offsetof(StateInfo, generator) == 0x58);
		static_assert(offsetof(StateInfo, stateID) == 0x68);
		static_assert(sizeof(StateInfo) == 0x78);

		class TransitionInfoArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__TransitionInfoArray;
			inline static constexpr auto VTABLE = VTABLE_hkbStateMachine__TransitionInfoArray;

			~TransitionInfoArray() override;  // 00

			// members
			hkArray<TransitionInfo> transitions;  // 10
		};
		static_assert(offsetof(TransitionInfoArray, transitions) == 0x10);
		static_assert(sizeof(TransitionInfoArray) == 0x20);

		~hkbStateMachine() override;  // 00

		// override (hkbGenerator)
		hkClass*            GetClassType() const override;                                                                                     // 01
		void                CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;                  // 02
		void                Unk_03(void) override;                                                                                             // 03
		void                Activate(const hkbContext& a_context) override;                                                                    // 04
		void                Update(const hkbContext& a_context, float a_timestep) override;                                                    // 05
		void                HandleEvent(const hkbContext& a_context, hkbEvent& a_event) override;                                              // 06
		void                Deactivate(const hkbContext& a_context) override;                                                                  // 07
		std::int32_t        GetMaxNumChildren(GetChildrenFlags a_flags) override;                                                              // 08
		void                GetChildren(GetChildrenFlags a_flags, ChildrenInfo& a_childrenInfo) override;                                      // 09
		bool                IsValid(hkStringPtr& a_errorString) const override;                                                                // 0A
		hkbNode*            CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;                                                        // 0C
		hkReferencedObject* CreateInternalState() override;                                                                                    // 0D
		void                GetInternalState(hkReferencedObject& a_internalState) const override;                                              // 0E
		void                GetInternalStateUser(const hkbBehaviorGraph& a_rootBehavior, hkReferencedObject& a_internalState) const override;  // 0F
		void                SetInternalState(const hkReferencedObject& a_internalState) override;                                              // 10
		void                SetInternalStateUser(
						   const hkbContext&                                            a_context,
						   const hkReferencedObject&                                    a_internalState,
						   hkPointerMap<std::int16_t, const hkbNodeInternalStateInfo*>& a_nodeIdToInternalStateMap) override;  // 11
		void GetActiveEvents(hkPointerMap<std::int32_t, bool>& a_activeEvents) const override;                                 // 12
		void GetActiveVariablesSpecial(hkPointerMap<std::int32_t, bool>& a_activeVariables) const override;                    // 14
		void Generate(
			const hkbContext&          a_context,
			const hkbGeneratorOutput** a_activeChildrenOutput,
			hkbGeneratorOutput&        a_output,
			float                      a_timeOffset = 0.0f) const override;                               // 17
		bool CanRecycleOutput(void) const override;                                  // 18 - { return true; }
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& a_info) override;  // 19
		void StartEcho(void) override;                                               // 1B

		// members
		hkbEvent                                                   eventToSendWhenStateOrTransitionChanges;  // 048
		hkRefPtr<hkbStateChooser>                                  startStateChooser;                        // 060
		std::int32_t                                               startStateID;                             // 068
		std::int32_t                                               returnToPreviousStateEventID;             // 06C
		std::int32_t                                               randomTransitionEventID;                  // 070
		std::int32_t                                               transitionToNextHigherStateEventID;       // 074
		std::int32_t                                               transitionToNextLowerStateEventID;        // 078
		std::int32_t                                               syncVariableIndex;                        // 07C
		std::int32_t                                               currentStateID;                           // 080
		bool                                                       wrapAroundStateID;                        // 084
		std::int8_t                                                maxSimultaneousTransitions;               // 085
		REX::EnumSet<StartStateMode, std::uint8_t>                 startStateMode;                           // 086
		REX::EnumSet<StateMachineSelfTransitionMode, std::uint8_t> selfTransitionMode;                       // 087
		bool                                                       isActive;                                 // 088
		std::uint8_t                                               pad41;                                    // 089
		std::uint16_t                                              pad42;                                    // 08A
		std::uint32_t                                              pad44;                                    // 08C
		hkArray<StateInfo*>                                        states;                                   // 090
		hkRefPtr<TransitionInfoArray>                              wildcardTransitions;                      // 0A0
		hkRefVariant                                               stateIDToIndexMap;                        // 0A8
		hkArray<ActiveTransitionInfo>                              activeTransitions;                        // 0B0
		hkArray<std::uint8_t>                                      transitionFlags;                          // 0C0
		hkArray<std::uint8_t>                                      wildcardTransitionFlags;                  // 0D0
		hkArray<DelayedTransitionInfo>                             delayedTransitions;                       // 0E0
		float                                                      timeInState;                              // 0F0
		float                                                      lastLocalTime;                            // 0F4
		std::int32_t                                               previousStateID;                          // 0F8
		std::int32_t                                               nextStartStateIndexOverride;              // 0FC
		bool                                                       stateOrTransitionChanged;                 // 100
		bool                                                       echoNextUpdate;                           // 101
		std::uint16_t                                              currentStateIndexAndEntered;              // 102
		std::uint32_t                                              pad0BC;                                   // 104
	};
	static_assert(offsetof(hkbStateMachine, activeTransitions) == 0xB0);
	static_assert(offsetof(hkbStateMachine, transitionFlags) == 0xC0);
	static_assert(offsetof(hkbStateMachine, wildcardTransitionFlags) == 0xD0);
	static_assert(offsetof(hkbStateMachine, delayedTransitions) == 0xE0);
	static_assert(sizeof(hkbStateMachine) == 0x108);
}
