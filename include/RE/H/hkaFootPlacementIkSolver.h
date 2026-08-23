#pragma once

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkaRaycastInterface;
	class hkaSkeleton;

	// Skyrim SE 1.5.97 layout. Callable solver entry points are intentionally not exposed here.
	class hkaFootPlacementIkSolver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkaFootPlacementIkSolver;
		inline static constexpr auto VTABLE = VTABLE_hkaFootPlacementIkSolver;

		struct alignas(0x10) Setup
		{
			// members
			const hkaSkeleton* skeleton;                  // 00
			std::int16_t       hipIndex;                  // 08
			std::int16_t       kneeIndex;                 // 0A
			std::int16_t       ankleIndex;                // 0C
			std::uint8_t       pad0E[2];                  // 0E
			hkVector4          kneeAxisLS;                // 10
			hkVector4          footEndLS;                 // 20
			hkVector4          worldUpDirectionWS;        // 30
			hkVector4          modelUpDirectionMS;        // 40
			float              originalGroundHeightMS;    // 50
			float              footPlantedAnkleHeightMS;  // 54
			float              footRaisedAnkleHeightMS;   // 58
			float              maxAnkleHeightMS;          // 5C
			float              minAnkleHeightMS;          // 60
			float              cosineMaxKneeAngle;        // 64
			float              cosineMinKneeAngle;        // 68
			float              raycastDistanceUp;         // 6C
			float              raycastDistanceDown;       // 70
			bool               useFootLocking;            // 74
			std::uint8_t       pad75[0x0B];               // 75
		};
		static_assert(offsetof(Setup, skeleton) == 0x00);
		static_assert(offsetof(Setup, hipIndex) == 0x08);
		static_assert(offsetof(Setup, kneeIndex) == 0x0A);
		static_assert(offsetof(Setup, ankleIndex) == 0x0C);
		static_assert(offsetof(Setup, kneeAxisLS) == 0x10);
		static_assert(offsetof(Setup, footEndLS) == 0x20);
		static_assert(offsetof(Setup, worldUpDirectionWS) == 0x30);
		static_assert(offsetof(Setup, modelUpDirectionMS) == 0x40);
		static_assert(offsetof(Setup, originalGroundHeightMS) == 0x50);
		static_assert(offsetof(Setup, footPlantedAnkleHeightMS) == 0x54);
		static_assert(offsetof(Setup, footRaisedAnkleHeightMS) == 0x58);
		static_assert(offsetof(Setup, maxAnkleHeightMS) == 0x5C);
		static_assert(offsetof(Setup, minAnkleHeightMS) == 0x60);
		static_assert(offsetof(Setup, cosineMaxKneeAngle) == 0x64);
		static_assert(offsetof(Setup, cosineMinKneeAngle) == 0x68);
		static_assert(offsetof(Setup, raycastDistanceUp) == 0x6C);
		static_assert(offsetof(Setup, raycastDistanceDown) == 0x70);
		static_assert(offsetof(Setup, useFootLocking) == 0x74);
		static_assert(alignof(Setup) == 0x10);
		static_assert(sizeof(Setup) == 0x80);

		struct alignas(0x10) Input
		{
			// members
			hkQsTransform        originalAnkleTransformMS;  // 00 - Animation ankle transform before Foot IK.
			hkQsTransform        worldFromModel;            // 30
			bool                 footPlacementOn;           // 60
			std::uint8_t         pad61[7];                  // 61
			hkaRaycastInterface* raycastInterface;          // 68
			float                onOffGain;                 // 70
			float                groundAscendingGain;       // 74
			float                groundDescendingGain;      // 78
			float                footPlantedGain;           // 7C
			float                footRaisedGain;            // 80
			float                footUnlockGain;            // 84
			float                maxKneeAngleDifference;    // 88 - Skyrim extension copied from Foot IK gains.
			std::uint32_t        collisionFilterInfo;       // 8C
			bool                 useCollisionFilterInfo;    // 90
			std::uint8_t         pad91[0x0F];               // 91
		};
		static_assert(offsetof(Input, originalAnkleTransformMS) == 0x00);
		static_assert(offsetof(Input, worldFromModel) == 0x30);
		static_assert(offsetof(Input, footPlacementOn) == 0x60);
		static_assert(offsetof(Input, raycastInterface) == 0x68);
		static_assert(offsetof(Input, onOffGain) == 0x70);
		static_assert(offsetof(Input, groundAscendingGain) == 0x74);
		static_assert(offsetof(Input, groundDescendingGain) == 0x78);
		static_assert(offsetof(Input, footPlantedGain) == 0x7C);
		static_assert(offsetof(Input, footRaisedGain) == 0x80);
		static_assert(offsetof(Input, footUnlockGain) == 0x84);
		static_assert(offsetof(Input, maxKneeAngleDifference) == 0x88);
		static_assert(offsetof(Input, collisionFilterInfo) == 0x8C);
		static_assert(offsetof(Input, useCollisionFilterInfo) == 0x90);
		static_assert(alignof(Input) == 0x10);
		static_assert(sizeof(Input) == 0xA0);

		struct alignas(0x10) Output
		{
			// members
			hkVector4    groundNormal;   // 00
			float        verticalError;  // 10
			bool         hitSomething;   // 14
			std::uint8_t pad15[0x0B];    // 15
		};
		static_assert(offsetof(Output, groundNormal) == 0x00);
		static_assert(offsetof(Output, verticalError) == 0x10);
		static_assert(offsetof(Output, hitSomething) == 0x14);
		static_assert(alignof(Output) == 0x10);
		static_assert(sizeof(Output) == 0x20);

		~hkaFootPlacementIkSolver() override;  // 00

		// members
		Setup        setup;                         // 10
		float        currentWeight;                 // 90
		float        previousGroundHeightWS;        // 94
		std::uint8_t pad98[8];                      // 98
		hkVector4    previousGroundNormalWS;        // A0
		float        previousVerticalDisplacement;  // B0
		bool         isFootLocked;                  // B4
		std::uint8_t padB5[0x0B];                   // B5
		hkVector4    lockedFootPositionInWS;        // C0
		hkVector4    lockedFootEndPositionInWS;     // D0
		hkVector4    footUnlockingOffset;           // E0
	};
	static_assert(offsetof(hkaFootPlacementIkSolver, setup) == 0x10);
	static_assert(offsetof(hkaFootPlacementIkSolver, currentWeight) == 0x90);
	static_assert(offsetof(hkaFootPlacementIkSolver, previousGroundHeightWS) == 0x94);
	static_assert(offsetof(hkaFootPlacementIkSolver, previousGroundNormalWS) == 0xA0);
	static_assert(offsetof(hkaFootPlacementIkSolver, previousVerticalDisplacement) == 0xB0);
	static_assert(offsetof(hkaFootPlacementIkSolver, isFootLocked) == 0xB4);
	static_assert(offsetof(hkaFootPlacementIkSolver, lockedFootPositionInWS) == 0xC0);
	static_assert(offsetof(hkaFootPlacementIkSolver, lockedFootEndPositionInWS) == 0xD0);
	static_assert(offsetof(hkaFootPlacementIkSolver, footUnlockingOffset) == 0xE0);
	static_assert(alignof(hkaFootPlacementIkSolver) == 0x10);
	static_assert(sizeof(hkaFootPlacementIkSolver) == 0xF0);
}
