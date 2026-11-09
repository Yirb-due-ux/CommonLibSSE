#pragma once

namespace RE
{
	struct hkTypeInfo
	{
		using Finish = void (*)(void*, int);
		using Cleanup = void (*)(void*);

		const char* typeName;    // 00
		const char* scopedName;  // 08
		Finish      finish;      // 10
		Cleanup     cleanup;     // 18
		const void* vtable;      // 20
		std::size_t size;        // 28
	};
	static_assert(sizeof(hkTypeInfo) == 0x30);
	static_assert(offsetof(hkTypeInfo, vtable) == 0x20);
}
