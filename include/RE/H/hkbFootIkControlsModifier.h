#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbEventProperty.h"
#include "RE/H/hkbFootIkGains.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	struct alignas(0x10) hkbFootIkControlData
	{
		// members
		hkbFootIkGains gains;  // 00
	};
	static_assert(alignof(hkbFootIkControlData) == 0x10);
	static_assert(sizeof(hkbFootIkControlData) == 0x30);

	class hkbFootIkControlsModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkControlsModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbFootIkControlsModifier;

		struct Leg
		{
			// members
			hkVector4        groundPosition;   // 00 - Ground position reported by the raycast.
			hkbEventProperty ungroundedEvent;  // 10 - Event sent when a planted foot misses the ground.
			float            verticalError;    // 20 - Distance from the input foot height to the ground.
			bool             hitSomething;     // 24 - Whether the raycast hit the ground.
			bool             isPlantedMS;      // 25 - Whether the input animation considers the foot planted.
			std::uint8_t     pad26[0x0A];      // 26
		};
		static_assert(offsetof(Leg, groundPosition) == 0x00);
		static_assert(offsetof(Leg, ungroundedEvent) == 0x10);
		static_assert(offsetof(Leg, verticalError) == 0x20);
		static_assert(offsetof(Leg, hitSomething) == 0x24);
		static_assert(offsetof(Leg, isPlantedMS) == 0x25);
		static_assert(alignof(Leg) == 0x10);
		static_assert(sizeof(Leg) == 0x30);

		~hkbFootIkControlsModifier() override;  // 00

		// members
		hkbFootIkControlData controlData;              // 50 - Controls consumed by hkbFootIkModifier.
		hkArray<Leg>         legs;                     // 80 - Per-leg raycast and planting output.
		hkVector4            errorOutTranslation;      // 90 - Aggregate translation feedback.
		hkQuaternion         alignWithGroundRotation;  // A0 - Aggregate ground-alignment feedback.
	};
	static_assert(offsetof(hkbFootIkControlsModifier, controlData) == 0x50);
	static_assert(offsetof(hkbFootIkControlsModifier, legs) == 0x80);
	static_assert(offsetof(hkbFootIkControlsModifier, errorOutTranslation) == 0x90);
	static_assert(offsetof(hkbFootIkControlsModifier, alignWithGroundRotation) == 0xA0);
	static_assert(alignof(hkbFootIkControlsModifier) == 0x10);
	static_assert(sizeof(hkbFootIkControlsModifier) == 0xB0);
}
