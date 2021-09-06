#pragma once
#include "ECS_Settings.h"
#include "Query.h"

namespace ecs
{
/******************************** FUNCTIONS ***********************************/
	// Compile time string to int (using ascii value)
	constexpr int ecs_stoi_impl(const char* str, int value = 0)
	{
		return *str ? ecs_stoi_impl(str + 1, *str + value) : value;
	}

	constexpr int StringToID(const char* str)
	{
		return ecs_stoi_impl(str);
	}
/*********************************** COMPONENT **************************************/
	struct ComponentInfo
	{
		GUID			m_Guid		= 0;
		mutable CID		m_CID		= INVALID_CID;
		const char*		m_pName		= "Unnamed Component";
	};
	
	namespace component::details
	{
		template <typename T_COMPONENT>
		consteval ComponentInfo CreateInfo() noexcept
		{
			return ComponentInfo{
				.m_Guid		=	T_COMPONENT::info_v.m_Guid ? T_COMPONENT::info_v.m_Guid : StringToID(__FUNCSIG__),
				.m_CID		=	T_COMPONENT::info_v.m_CID,
				.m_pName	=	T_COMPONENT::info_v.m_pName
			};
		}

		// Create ComponentInfo
		template<typename T>
		constexpr static auto info_v = CreateInfo<T>();
	}

	// Reference to the ComponentInfo<T_COMPONENT>
	template<typename T_COMPONENT>
	constexpr static auto& ComponentInfo_v = component::details::info_v<T_COMPONENT>;

/************************************ SYSTEM ****************************************/
	struct SystemInfo
	{
		GUID			m_Guid		= 0;
		const char*		m_pName		= "Unnamed System";
		mutable Query	m_Query		{};
	};
	
	namespace system::details
	{
		template< typename T_SYSTEM >
		consteval SystemInfo CreateInfo() noexcept
		{
			return SystemInfo
			{
				.m_Guid = T_SYSTEM::info_v.m_Guid ? T_SYSTEM::info_v.m_Guid : StringToID(__FUNCSIG__),
				.m_pName = T_SYSTEM::info_v.m_pName,
			};
		}

		// Create SystemInfo
		template< typename T >
		static constexpr auto info_v = CreateInfo<T>();
	}
	// Reference to the SystemInfo_v<SYSTEM>
	template< typename T_SYSTEM >
	constexpr static auto& SystemInfo_v = system::details::info_v<T_SYSTEM>;

/******************************** COMPONENT ARRAY ***********************************/
	// Component array
	struct info
	{
		using move_fn = void(std::byte* Dst, std::byte* Src) noexcept;
		using copy_fn = void(std::byte* Dst, const std::byte* Src) noexcept;
		using fn_kill = void(std::unique_ptr<std::byte[]>&&) ;

		info() = default;
		info(const info&) = default;
		info( info&&) = default;

		// Component Array
		std::unique_ptr<std::byte[]>	m_ComponentData;

		// Size of component
		std::size_t						m_Size = 0;

		~info()
		{
			if (m_ComponentData.get())	m_pKill(std::move(m_ComponentData));
		}

		// Pointer to Component info
		const ComponentInfo*			m_pInfo			= nullptr;

		// Cast back to T before releasing memory
		fn_kill*						m_pKill			= nullptr;

		// Move function
		move_fn*						m_pMoveFn		= nullptr;
		
		// Copy function
		copy_fn*						m_pCopyFn		= nullptr;
	};

/******************************** QUERY INFO STRUCT ***********************************/
	// Query
	template<typename... T>
	struct must{};

	template<typename... T>
	struct none_of{};

	template<typename... T>
	struct one_of{};
}
