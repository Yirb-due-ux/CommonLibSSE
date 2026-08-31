#pragma once

namespace RE
{
	template <class T>
	class hkQueue
	{
	public:
		using size_type = std::int32_t;

		[[nodiscard]] bool empty() const noexcept
		{
			return elementsInUse == 0;
		}

		[[nodiscard]] size_type size() const noexcept
		{
			return elementsInUse;
		}

		// members
		T*        data{ nullptr };  // 00
		size_type capacity{};       // 08
		size_type head{};           // 0C
		size_type tail{};           // 10
		size_type elementsInUse{};  // 14
	};
	static_assert(sizeof(hkQueue<void*>) == 0x18);
}
