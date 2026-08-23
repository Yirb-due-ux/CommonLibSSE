#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkbFootIkDriverInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkDriverInfo;
		inline static constexpr auto VTABLE = VTABLE_hkbFootIkDriverInfo;

		struct alignas(0x10) Leg
		{
			// members
			hkQuaternion prevAnkleRotLS;            // 00 - Runtime cache; ignored by serialization.
			hkVector4    kneeAxisLS;                // 10 - Knee hinge axis in knee-local space.
			hkVector4    footEndLS;                 // 20 - Toe/end point in ankle-local space.
			float        footPlantedAnkleHeightMS;  // 30
			float        footRaisedAnkleHeightMS;   // 34
			float        maxAnkleHeightMS;          // 38
			float        minAnkleHeightMS;          // 3C
			float        maxKneeAngleDegrees;       // 40
			float        minKneeAngleDegrees;       // 44
			float        maxAnkleAngleDegrees;      // 48
			std::int16_t hipIndex;                  // 4C
			std::int16_t kneeIndex;                 // 4E
			std::int16_t ankleIndex;                // 50
			std::uint8_t pad52[0x0E];               // 52
		};
		static_assert(offsetof(Leg, prevAnkleRotLS) == 0x00);
		static_assert(offsetof(Leg, kneeAxisLS) == 0x10);
		static_assert(offsetof(Leg, footEndLS) == 0x20);
		static_assert(offsetof(Leg, footPlantedAnkleHeightMS) == 0x30);
		static_assert(offsetof(Leg, footRaisedAnkleHeightMS) == 0x34);
		static_assert(offsetof(Leg, maxAnkleHeightMS) == 0x38);
		static_assert(offsetof(Leg, minAnkleHeightMS) == 0x3C);
		static_assert(offsetof(Leg, maxKneeAngleDegrees) == 0x40);
		static_assert(offsetof(Leg, minKneeAngleDegrees) == 0x44);
		static_assert(offsetof(Leg, maxAnkleAngleDegrees) == 0x48);
		static_assert(offsetof(Leg, hipIndex) == 0x4C);
		static_assert(offsetof(Leg, kneeIndex) == 0x4E);
		static_assert(offsetof(Leg, ankleIndex) == 0x50);
		static_assert(alignof(Leg) == 0x10);
		static_assert(sizeof(Leg) == 0x60);

		~hkbFootIkDriverInfo() override;  // 00

		// members
		hkArray<Leg>  legs;                    // 10
		float         raycastDistanceUp;       // 20
		float         raycastDistanceDown;     // 24
		float         originalGroundHeightMS;  // 28
		float         verticalOffset;          // 2C
		std::uint32_t collisionFilterInfo;     // 30
		float         forwardAlignFraction;    // 34
		float         sidewaysAlignFraction;   // 38
		float         sidewaysSampleWidth;     // 3C
		bool          lockFeetWhenPlanted;     // 40
		bool          useCharacterUpVector;    // 41
		bool          isQuadrupedNarrow;       // 42
		std::uint8_t  pad43[5];                // 43
	};
	static_assert(offsetof(hkbFootIkDriverInfo, legs) == 0x10);
	static_assert(offsetof(hkbFootIkDriverInfo, raycastDistanceUp) == 0x20);
	static_assert(offsetof(hkbFootIkDriverInfo, raycastDistanceDown) == 0x24);
	static_assert(offsetof(hkbFootIkDriverInfo, originalGroundHeightMS) == 0x28);
	static_assert(offsetof(hkbFootIkDriverInfo, verticalOffset) == 0x2C);
	static_assert(offsetof(hkbFootIkDriverInfo, collisionFilterInfo) == 0x30);
	static_assert(offsetof(hkbFootIkDriverInfo, forwardAlignFraction) == 0x34);
	static_assert(offsetof(hkbFootIkDriverInfo, sidewaysAlignFraction) == 0x38);
	static_assert(offsetof(hkbFootIkDriverInfo, sidewaysSampleWidth) == 0x3C);
	static_assert(offsetof(hkbFootIkDriverInfo, lockFeetWhenPlanted) == 0x40);
	static_assert(offsetof(hkbFootIkDriverInfo, useCharacterUpVector) == 0x41);
	static_assert(offsetof(hkbFootIkDriverInfo, isQuadrupedNarrow) == 0x42);
	static_assert(sizeof(hkbFootIkDriverInfo) == 0x48);
}
