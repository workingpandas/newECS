#pragma once
#include "SystemFinal.h"
#include "SystemBase.h"
#include "ECS.h"

namespace ecs
{
	template <typename T_SYSTEM>
	SystemFinal<T_SYSTEM>::SystemFinal(ECS* ecs, ArchetypeMgr* archetype_mgr)
	{
		T_SYSTEM::m_ArchetypeMgr	= archetype_mgr;
		T_SYSTEM::m_ecs				= ecs;
		
		// Create SystemInfo for T_SYSTEM; Update query
		SystemInfo_v<T_SYSTEM>.m_Query.AddQueryFromTuple<T_SYSTEM::query>();
	}

	template <typename T_SYSTEM>
	void SystemFinal<T_SYSTEM>::Run(bool pause)
	{
		// Check if user define OnPreUpdate
		if constexpr (&T_SYSTEM::OnPreUpdate != &SystemBase::OnPreUpdate)
		{
			T_SYSTEM::OnPreUpdate();
		}

		// Not pause
		if(!pause)
		{
			// OnUpdate define; use OnUpdate
			if constexpr (&T_SYSTEM::OnUpdate != &SystemBase::OnUpdate)
			{
				T_SYSTEM::OnUpdate();
			}
			// Use () operator 
			else
			{
				// Get archetype list; search by query
				auto list = SystemBase::m_ArchetypeMgr->Search(SystemInfo_v<T_SYSTEM>.m_Query);
				T_SYSTEM::m_ArchetypeMgr->ForEach(list, std::forward<T_SYSTEM&&>(*this));
			}
		}
		
		// Pause
		else
		{
			// OnPause defined; use OnPause
			if constexpr (&T_SYSTEM::OnPause != &SystemBase::OnPause)
			{
				// OnPause defined; Use OnPause
				T_SYSTEM::OnPause();
			}
		}
		
		// OnPostUpdate defined; use OnPostUpdate
		if constexpr (&T_SYSTEM::OnPostUpdate != &SystemBase::OnPostUpdate)
		{
			T_SYSTEM::OnPostUpdate();
		}
	}

	template <typename T_SYSTEM>
	SystemFinal<T_SYSTEM>::~SystemFinal()
	{
		if constexpr (&T_SYSTEM::OnDestroy != &SystemBase::OnDestroy)
		{
			// OnDestroy defined; Use OnDestroy
			T_SYSTEM::OnDestroy();
		}
	}
}
