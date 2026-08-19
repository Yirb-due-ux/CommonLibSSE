#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbCharacterControllerSetup.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		// members
		std::uint8_t                      characterControllerSetup[0x18];  // 10
		std::uint8_t                      pad28[0x08];                     // 28
		hkVector4                         modelUpMS;                       // 30
		hkVector4                         modelForwardMS;                  // 40
		hkVector4                         modelRightMS;                    // 50
		hkArray<hkbVariableInfo>          characterPropertyInfos;         // 60
		hkArray<std::int32_t>             numBonesPerLod;                 // 70
		hkRefPtr<hkbVariableValueSet>     characterPropertyValues;        // 80
		hkRefPtr<hkbFootIkDriverInfo>     footIkDriverInfo;               // 88
		hkRefPtr<hkbHandIkDriverInfo>     handIkDriverInfo;               // 90
		hkRefPtr<hkbCharacterStringData>  stringData;                     // 98
		hkRefPtr<hkbMirroredSkeletonInfo> mirroredSkeletonInfo;           // A0
		float                             scale;                          // A8
		std::uint16_t                     numHands;                       // AC
		std::uint16_t                     numFloatSlots;                  // AE
	};
	static_assert(offsetof(hkbCharacterData, footIkDriverInfo) == 0x88);
	static_assert(offsetof(hkbCharacterData, handIkDriverInfo) == 0x90);
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}
