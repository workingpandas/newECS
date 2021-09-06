#pragma once
#include "SystemBase.h"
#include "Archetype.h"
#include "ArchetypeMgr.h"
#include "ECS.h"

namespace ecs
{
	template <typename T_FUNC>
	void SystemBase::ForEach(std::vector<std::shared_ptr<Archetype>>& archetypes, T_FUNC&& Func)
	{
		m_ArchetypeMgr->ForEach(archetypes, std::forward<T_FUNC&&>(Func));
	}

	template<typename... T_ARGS>
	decltype(auto) SystemBase::GetOrCreateArchetype()
	{
		return m_ecs->GetOrCreateArchetype<T_ARGS...>();
	}

	template <typename T_SYSTEM>
	decltype(auto) SystemBase::GetSystem()
	{
		return m_ecs->GetSystem<T_SYSTEM>();
	}

	inline void SystemBase::DestroyEntity(EntityID entity)
	{
		m_ecs->DestroyEntity(entity);
	}

	inline void SystemBase::DestroyEntity(EntityC& entity)
	{
		m_ecs->DestroyEntity(entity.m_EntityID);
	}

	inline decltype(auto) SystemBase::Search(Query& query)
	{
		return m_ecs->Search(query);
	}

	inline bool SystemBase::GetPauseState() const
	{
		return m_ecs->GetState();
	}

	inline void SystemBase::SetPause(bool state)
	{
		m_ecs->SetPause(state);
	}
}
