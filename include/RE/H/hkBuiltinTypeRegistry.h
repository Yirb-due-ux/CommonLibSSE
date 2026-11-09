#pragma once

#include "RE/H/hkClass.h"
#include "RE/H/hkTypeInfo.h"

namespace RE
{
#ifndef SKYRIM_SUPPORT_AE
	// SE 1.5.97 registry methods. The remaining virtual interface is intentionally opaque.
	class hkClassNameRegistry
	{
	public:
		const hkClass* Find(const char* a_name) const
		{
			using func_t = const hkClass* (*)(const hkClassNameRegistry*, const char*);
			const std::uintptr_t* table;
			std::memcpy(&table, this, sizeof(table));
			// Slot 4 selects the concrete class-name registry implementation.
			return reinterpret_cast<func_t>(table[4])(this, a_name);
		}
	};

	class hkTypeInfoRegistry
	{
	public:
		const hkTypeInfo* Find(const char* a_name) const
		{
			static REL::Relocation<decltype(&hkTypeInfoRegistry::Find)> func{ REL::ID(59467) };
			return func(this, a_name);
		}
	};

	class hkVtableClassRegistry
	{
	public:
		void RegisterVtable(const void* a_vtable, const hkClass* a_class)
		{
			static REL::Relocation<decltype(&hkVtableClassRegistry::RegisterVtable)> func{ REL::ID(59471) };
			func(this, a_vtable, a_class);
		}
	};

	class hkBuiltinTypeRegistry
	{
	public:
		static hkBuiltinTypeRegistry* GetSingleton()
		{
			static REL::Relocation<hkBuiltinTypeRegistry**> singleton{ REL::ID(521918) };
			return *singleton;
		}

		hkTypeInfoRegistry* GetTypeInfoRegistry()
		{
			static REL::Relocation<decltype(&hkBuiltinTypeRegistry::GetTypeInfoRegistry)> func{ REL::ID(59455) };
			return func(this);
		}

		hkClassNameRegistry* GetClassNameRegistry()
		{
			static REL::Relocation<decltype(&hkBuiltinTypeRegistry::GetClassNameRegistry)> func{ REL::ID(59456) };
			return func(this);
		}

		hkVtableClassRegistry* GetVtableClassRegistry()
		{
			static REL::Relocation<decltype(&hkBuiltinTypeRegistry::GetVtableClassRegistry)> func{ REL::ID(59457) };
			return func(this);
		}

		void RegisterType(const hkTypeInfo* a_type, const hkClass* a_class)
		{
			static REL::Relocation<decltype(&hkBuiltinTypeRegistry::RegisterType)> func{ REL::ID(59462) };
			func(this, a_type, a_class);
		}
	};
#endif
}
