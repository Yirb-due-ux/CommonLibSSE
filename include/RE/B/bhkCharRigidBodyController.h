#pragma once

#include "RE/B/bhkCharacterController.h"
#include "RE/B/bhkCharacterRigidBody.h"
#include "RE/H/hkpCharacterRigidBodyListener.h"

namespace RE
{
	class bhkCharRigidBodyController :
		public bhkCharacterController,        // 00
		public hkpCharacterRigidBodyListener  // 330
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharRigidBodyController;
		inline static constexpr auto VTABLE = VTABLE_bhkCharRigidBodyController;

#ifndef SKYRIM_SUPPORT_AE
		// SE 1.5.97
		inline static constexpr REL::ID GetPositionImplID{ 77314 };
		inline static constexpr REL::ID SetLinearVelocityImplID{ 77318 };
		inline static constexpr REL::ID CharacterCallbackID{ 77305 };
		inline static constexpr REL::ID Unk0BID{ 77321 };
		inline static constexpr REL::ID UpdateContactsID{ 77327 };

		void UpdateContacts()
		{
			using func_t = decltype(&bhkCharRigidBodyController::UpdateContacts);
			static REL::Relocation<func_t> func{ UpdateContactsID };
			func(this);
		}
#endif

		~bhkCharRigidBodyController() override;  // 00

		// override (bhkCharacterController)
		void GetPositionImpl(hkVector4& a_pos, bool a_applyCenterOffset) const override;  // 02
		void SetLinearVelocityImpl(const hkVector4& a_velocity) override;                 // 07

		// override (hkpCharacterRigidBodyListener)
		virtual void CharacterCallback(hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB) override;                                                                                                                                                                 // 03
		virtual void ProcessActualPoints(const hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB, const hkpLinkedCollidable::CollisionEntry& a_entry, hkpSimpleConstraintContactMgr* a_mgr, hkArray<std::uint16_t>& a_contactPointIds) override;                    // 04
		virtual void UnweldContactPoints(hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds) override;                                               // 05
		virtual void ConsiderCollisionEntryForSlope(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, hkArray<std::uint16_t>& contactPointIds) override;                   // 06
		virtual void ConsiderCollisionEntryForMassModification(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds) override;  // 07

		bhkCharacterRigidBody charRigidBody;  // 340
	};
	static_assert(offsetof(bhkCharRigidBodyController, charRigidBody) == 0x340);
}
