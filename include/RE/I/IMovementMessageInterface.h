#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class NiPoint3;
	struct BSPathingLocation;

	class IMovementMessageInterface : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMessageInterface;
		inline static constexpr auto VTABLE = VTABLE_IMovementMessageInterface;

		~IMovementMessageInterface() override;  // 00

		// add
		virtual void Unk_01(const BSPathingLocation& a_location, const NiPoint3& a_position) = 0;  // 01 - Queues a warp record ordered against queued movement messages.
		virtual void Unk_02(const MovementMessagePtr& a_message) = 0;                              // 02 - Retains and queues the message for controller processing.
		virtual void Unk_03(const MovementMessage& a_message) = 0;                                 // 03 - Synchronously dispatches the message without retaining it.
	};
	static_assert(sizeof(IMovementMessageInterface) == 0x8);
}
