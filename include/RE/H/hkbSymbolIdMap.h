#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkPointerMap.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbSymbolIdMap : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSymbolIdMap;
		inline static constexpr auto VTABLE = VTABLE_hkbSymbolIdMap;

		~hkbSymbolIdMap() override;  // 00

		std::int32_t GetExternal(std::int32_t a_internal) const
		{
			// Native behavior requires every non-negative internal ID to be a valid array index.
			return a_internal < 0 ? a_internal : internalToExternalMap[a_internal];
		}

		std::int32_t GetInternal(std::int32_t a_external) const noexcept
		{
			if (a_external < 0) {
				return a_external;
			}

			return externalToInternalMap.GetWithDefault(a_external + 1, -1);
		}

		// members
		hkArray<std::int32_t>                    internalToExternalMap;  // 10
		hkPointerMap<std::int32_t, std::int32_t> externalToInternalMap;  // 20
	};
	static_assert(offsetof(hkbSymbolIdMap, internalToExternalMap) == 0x10);
	static_assert(offsetof(hkbSymbolIdMap, externalToInternalMap) == 0x20);
	static_assert(sizeof(hkbSymbolIdMap) == 0x30);
}
