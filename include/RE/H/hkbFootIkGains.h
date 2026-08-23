#pragma once

namespace RE
{
	struct hkbFootIkGains
	{
		// members
		float onOffGain;                   // 00 - Smooths foot placement on and off.
		float groundAscendingGain;         // 04 - Smooths rising ground height.
		float groundDescendingGain;        // 08 - Smooths falling ground height.
		float footPlantedGain;             // 0C - Gain used while the foot is planted.
		float footRaisedGain;              // 10 - Gain used while the foot is raised.
		float footUnlockGain;              // 14 - Smooths horizontal release from a locked position.
		float worldFromModelFeedbackGain;  // 18 - Feeds vertical error back to world-from-model.
		float errorUpDownBias;             // 1C - Biases the aggregate vertical error.
		float alignWorldFromModelGain;     // 20 - Aligns world-from-model to the ground.
		float hipOrientationGain;          // 24 - Applies the hip-orientation prepass.
		float maxKneeAngleDifference;      // 28 - Limits the per-step knee-angle change.
		float ankleOrientationGain;        // 2C - Blends the ankle toward the ground orientation.
	};
	static_assert(offsetof(hkbFootIkGains, onOffGain) == 0x00);
	static_assert(offsetof(hkbFootIkGains, groundAscendingGain) == 0x04);
	static_assert(offsetof(hkbFootIkGains, groundDescendingGain) == 0x08);
	static_assert(offsetof(hkbFootIkGains, footPlantedGain) == 0x0C);
	static_assert(offsetof(hkbFootIkGains, footRaisedGain) == 0x10);
	static_assert(offsetof(hkbFootIkGains, footUnlockGain) == 0x14);
	static_assert(offsetof(hkbFootIkGains, worldFromModelFeedbackGain) == 0x18);
	static_assert(offsetof(hkbFootIkGains, errorUpDownBias) == 0x1C);
	static_assert(offsetof(hkbFootIkGains, alignWorldFromModelGain) == 0x20);
	static_assert(offsetof(hkbFootIkGains, hipOrientationGain) == 0x24);
	static_assert(offsetof(hkbFootIkGains, maxKneeAngleDifference) == 0x28);
	static_assert(offsetof(hkbFootIkGains, ankleOrientationGain) == 0x2C);
	static_assert(sizeof(hkbFootIkGains) == 0x30);
}
