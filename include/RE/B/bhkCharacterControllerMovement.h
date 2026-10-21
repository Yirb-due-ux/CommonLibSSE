#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// Borrowed input prefix; only the engine allocates the complete movement input.
	struct bhkCharacterControllerMovement
	{
		bhkCharacterControllerMovement() = delete;
		bhkCharacterControllerMovement(const bhkCharacterControllerMovement&) = delete;
		bhkCharacterControllerMovement& operator=(const bhkCharacterControllerMovement&) = delete;

		float    deltaTime;    // 00
		float    unk04;        // 04
		float    unk08;        // 08
		float    unk0C;        // 0C
		NiPoint3 translation;  // 10
	};
	static_assert(offsetof(bhkCharacterControllerMovement, translation) == 0x10);
}
