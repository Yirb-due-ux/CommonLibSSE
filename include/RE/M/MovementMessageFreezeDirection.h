#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageFreezeDirection : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageFreezeDirection;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageFreezeDirection;

		enum class FreezeMessageType : std::uint32_t
		{
			kType0 = 0,  // Actor handler emits CyclicFreeze and sets its process flag.
			kType1 = 1,  // Actor handler emits CyclicCrossBlend and clears its process flag.
			kType2 = 2,  // Actor handler dispatches kActionMoveStop and clears its process flag.
			kType3 = 3,  // Actor handler emits CyclicFreeze without updating its process flag.
			kType4 = 4,  // Actor handler dispatches kActionMoveStart.
			kInvalid = static_cast<std::underlying_type_t<FreezeMessageType>>(-1)  // Actor handler ignores the message.
		};

		~MovementMessageFreezeDirection() override;  // 00

		// override (MovementMessage)
		[[nodiscard]] std::uint32_t GetType() const override;                            // 01
		void                        Write(BSPathingStreamWrite& a_stream) const override;  // 02
		void                        Read(BSPathingStreamRead& a_stream) override;          // 03

		// members
		FreezeMessageType type;   // 10
		std::uint32_t     pad14;  // 14
	};
	static_assert(sizeof(MovementMessageFreezeDirection::FreezeMessageType) == 0x4);
	static_assert(offsetof(MovementMessageFreezeDirection, type) == 0x10);
	static_assert(std::is_base_of_v<MovementMessage, MovementMessageFreezeDirection>);
	static_assert(!std::is_abstract_v<MovementMessageFreezeDirection>);
	static_assert(sizeof(MovementMessageFreezeDirection) == 0x18);
}
