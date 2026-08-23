#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkbBindable.h"

namespace RE
{
	class hkbBoneWeightArray : public hkbBindable
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBoneWeightArray;
		inline static constexpr auto VTABLE = VTABLE_hkbBoneWeightArray;

		~hkbBoneWeightArray() override;  // 00

		// Skyrim SE 1.5.97 reflection exposes one hkArray<hkReal> member at 0x30.
		hkArray<float> boneWeights;  // 30
	};
	static_assert(offsetof(hkbBoneWeightArray, boneWeights) == 0x30);
	static_assert(sizeof(hkbBoneWeightArray) == 0x40);
}
