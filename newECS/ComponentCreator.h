#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"

namespace ecs
{
	struct ICreator
	{
		virtual info Create() = 0;
		virtual ~ICreator() = default;
	};

	template <typename T>
	struct ComponentCreator : public ICreator
	{
		info Create() override
		{
			auto Memory = std::make_unique<T[]>(ecs::MAX_COMPONENTS_PER_ARCHETYPE);			
			info result{};

			result.m_ComponentData = std::move(reinterpret_cast<std::unique_ptr<std::byte[]>&>(Memory));
			result.m_Size = sizeof(T);
			result.m_pInfo = &T::info_v;

			// Cast back to T & release the memory
			result.m_pKill = [](std::unique_ptr<std::byte[]>&& A)
			{
				reinterpret_cast<std::unique_ptr<T[]>&&>(A).reset();
			};

			// Get move method if needed
			result.m_pMoveFn  = std::is_trivially_move_assignable_v<T>
			? nullptr
			: [] (std::byte* p1, std::byte* p2) noexcept
			{
				*reinterpret_cast<T*>(p1) = std::move(*reinterpret_cast<T*>(p2));
			};

			// Get copy method if needed
			result.m_pCopyFn = std::is_trivially_copy_assignable_v<T>
			? nullptr
			: [] (std::byte* p1, const std::byte* p2) noexcept
			{
				*reinterpret_cast<T*>(p1) = *reinterpret_cast<const T*>(p2);
			};
			
			return result;
		}
	};
}
