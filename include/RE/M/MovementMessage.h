#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	struct IPathFollowerAction;

	BSSmartPointer(MovementMessage);

	class MovementMessage : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessage;
		inline static constexpr auto VTABLE = VTABLE_MovementMessage;

		virtual ~MovementMessage();  // 00

		// add
		virtual std::uint32_t        GetType() const = 0;                              // 01
		virtual void                 Write(BSPathingStreamWrite& a_stream) const = 0;  // 02
		virtual void                 Read(BSPathingStreamRead& a_stream) = 0;          // 03
		virtual void                 FixupNumericID(void* a_numericIDMap);             // 04
		virtual IPathFollowerAction* GetPathFollowerActionInterface();                 // 05
	};
	static_assert(sizeof(MovementMessage) == 0x10);
}
