#include "REL/Relocation.h"

#include "REX/W32/KERNEL32.h"

namespace REL
{
	namespace
	{
		using WriteStatus = VFuncWriteResult::Status;

		WriteStatus write_protected(std::uintptr_t a_dst, const void* a_src, std::size_t a_count) noexcept
		{
			auto*         dst = reinterpret_cast<void*>(a_dst);
			std::uint32_t old{ 0 };
			if (!REX::W32::VirtualProtect(dst, a_count, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(old))) {
				return WriteStatus::kProtectFailed;
			}
			std::memcpy(dst, a_src, a_count);
			if (!REX::W32::VirtualProtect(dst, a_count, old, std::addressof(old))) {
				return WriteStatus::kRestoreFailed;
			}
			return WriteStatus::kSuccess;
		}
	}

	VFuncWriteResult detail::try_write_vfunc_at(std::uintptr_t a_slot, std::uintptr_t a_newFunc) noexcept
	{
		const auto previous = *reinterpret_cast<const std::uintptr_t*>(a_slot);
		return { previous, write_protected(a_slot, std::addressof(a_newFunc), sizeof(a_newFunc)) };
	}

	void safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count)
	{
		[[maybe_unused]] const auto status = write_protected(a_dst, a_src, a_count);
		assert(status == WriteStatus::kSuccess);
	}

	void safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count)
	{
		std::uint32_t old{ 0 };
		bool          success = REX::W32::VirtualProtect(
            reinterpret_cast<void*>(a_dst), a_count, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(old));
		if (success) {
			std::fill_n(reinterpret_cast<std::uint8_t*>(a_dst), a_count, a_value);
			success = REX::W32::VirtualProtect(
				reinterpret_cast<void*>(a_dst), a_count, old, std::addressof(old));
		}

		assert(success);
	}
}
