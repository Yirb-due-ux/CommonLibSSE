#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkClass;
	class hkRefVariant;

	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;
		inline static constexpr auto VTABLE = VTABLE_hkbVariableBindingSet;

		struct Binding
		{
			enum class BindingType : std::int8_t
			{
				kVariable = 0,
				kCharacterProperty = 1
			};

			enum class InternalBindingFlagBits : std::int8_t
			{
				kNone = 0,
				kOutput = 1 << 0
			};
			using InternalBindingFlags = REX::EnumSet<InternalBindingFlagBits, std::int8_t>;

			// Skyrim SE 1.5.97 reflection exposes an 11-member, 0x28-byte binding record.
			hkStringPtr                            memberPath;             // 00
			hkClass*                               memberClass;            // 08
			std::int32_t                           offsetInObjectPlusOne;  // 10
			std::int32_t                           offsetInArrayPlusOne;   // 14
			std::int32_t                           rootVariableIndex;      // 18
			std::int32_t                           variableIndex;          // 1C
			std::int8_t                            bitIndex;               // 20
			REX::EnumSet<BindingType, std::int8_t> bindingType;            // 21
			std::uint8_t                           memberType;             // 22
			std::int8_t                            variableType;           // 23
			InternalBindingFlags                   flags;                  // 24
			std::uint8_t                           pad25[3];               // 25
		};
		static_assert(offsetof(Binding, memberClass) == 0x08);
		static_assert(offsetof(Binding, offsetInObjectPlusOne) == 0x10);
		static_assert(offsetof(Binding, variableIndex) == 0x1C);
		static_assert(offsetof(Binding, bitIndex) == 0x20);
		static_assert(offsetof(Binding, bindingType) == 0x21);
		static_assert(offsetof(Binding, flags) == 0x24);
		static_assert(sizeof(Binding) == 0x28);

		~hkbVariableBindingSet() override;  // 00

		// Skyrim SE 1.5.97 reflection exposes three members at 0x10, 0x20, and 0x24.
		hkArray<Binding> bindings;                // 10
		std::int32_t     indexOfBindingToEnable;  // 20
		bool             hasOutputBinding;        // 24
		std::uint8_t     pad25[3];                // 25
	};
	static_assert(offsetof(hkbVariableBindingSet, bindings) == 0x10);
	static_assert(offsetof(hkbVariableBindingSet, indexOfBindingToEnable) == 0x20);
	static_assert(offsetof(hkbVariableBindingSet, hasOutputBinding) == 0x24);
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);

	class hkbBindable : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBindable;
		inline static constexpr auto VTABLE = VTABLE_hkbBindable;

		~hkbBindable() override;  // 00

		// add
		virtual void Unk_03(void);  // 03

		// members
		hkRefPtr<hkbVariableBindingSet> variableBindingSet;  // 10
		hkArray<hkRefVariant>           cachedBindables;     // 18
		bool                            areBindablesCached;  // 28
		std::uint8_t                    pad29;               // 29
		std::uint16_t                   pad2A;               // 2A
		std::uint32_t                   pad2C;               // 2C
	};
	static_assert(sizeof(hkbBindable) == 0x30);
}
