#pragma once

namespace RE
{
	class hkbBehaviorGraph;
	class hkbNode;

	class hkbGeneratorSyncInfo
	{
	public:
		struct SyncPoint
		{
			enum : std::int32_t
			{
				kInvalidID = -1,
				kStartOfGeneratorID = -2
			};

			std::int32_t id;    // 00
			float        time;  // 04
		};
		static_assert(sizeof(SyncPoint) == 0x8);

		SyncPoint   syncPoints[8];  // 00
		float       duration;       // 40
		float       localTime;      // 44
		float       playbackSpeed;  // 48
		std::int8_t numSyncPoints;  // 4C
		bool        isCyclic;       // 4D
		bool        isMirrored;     // 4E
		bool        isAdditive;     // 4F
	};
	static_assert(offsetof(hkbGeneratorSyncInfo, duration) == 0x40);
	static_assert(offsetof(hkbGeneratorSyncInfo, localTime) == 0x44);
	static_assert(offsetof(hkbGeneratorSyncInfo, playbackSpeed) == 0x48);
	static_assert(offsetof(hkbGeneratorSyncInfo, numSyncPoints) == 0x4C);
	static_assert(sizeof(hkbGeneratorSyncInfo) == 0x50);

	struct hkbNodeInfo
	{
		hkbGeneratorSyncInfo syncInfo;               // 00
		hkbNode*             nodeTemplate;           // 50
		hkbNode*             nodeClone;              // 58
		hkbBehaviorGraph*    behavior;               // 60
		std::int32_t         syncInfoIndex;          // 68 - Redirect target when useSyncInfoIndex is set.
		std::int32_t         parentCount;            // 6C
		std::int32_t         childCount;             // 70
		std::int32_t         firstChildIndex;        // 74 - Offset into activeNodesChildrenIndices.
		std::int32_t         syncParentIndex;        // 78
		std::int32_t         parentIndex;            // 7C - First visited parent.
		std::int32_t         unk80;                  // 80
		bool                 ignoreEvents;           // 84
		bool                 isGenerator;            // 85
		bool                 syncToParent;           // 86
		bool                 stopped;                // 87
		bool                 hasActivateBeenCalled;  // 88
		bool                 useSyncInfoIndex;       // 89
		std::uint8_t         pad8A[6];               // 8A
	};
	static_assert(offsetof(hkbNodeInfo, syncInfo) == 0x0);
	static_assert(offsetof(hkbNodeInfo, nodeTemplate) == 0x50);
	static_assert(offsetof(hkbNodeInfo, nodeClone) == 0x58);
	static_assert(offsetof(hkbNodeInfo, behavior) == 0x60);
	static_assert(offsetof(hkbNodeInfo, syncInfoIndex) == 0x68);
	static_assert(offsetof(hkbNodeInfo, parentCount) == 0x6C);
	static_assert(offsetof(hkbNodeInfo, childCount) == 0x70);
	static_assert(offsetof(hkbNodeInfo, firstChildIndex) == 0x74);
	static_assert(offsetof(hkbNodeInfo, syncParentIndex) == 0x78);
	static_assert(offsetof(hkbNodeInfo, parentIndex) == 0x7C);
	static_assert(offsetof(hkbNodeInfo, unk80) == 0x80);
	static_assert(offsetof(hkbNodeInfo, ignoreEvents) == 0x84);
	static_assert(offsetof(hkbNodeInfo, isGenerator) == 0x85);
	static_assert(offsetof(hkbNodeInfo, syncToParent) == 0x86);
	static_assert(offsetof(hkbNodeInfo, stopped) == 0x87);
	static_assert(offsetof(hkbNodeInfo, hasActivateBeenCalled) == 0x88);
	static_assert(offsetof(hkbNodeInfo, useSyncInfoIndex) == 0x89);
	static_assert(sizeof(hkbNodeInfo) == 0x90);

	using NodeList = hkArray<hkbNodeInfo>;
}
