#pragma once
#include "pch.h"
#include "ECS.h"

#include "EntityMgr.h"
#include "ComponentMgr.h"
#include "SystemMgr.h"
#include "ArchetypeMgr.h"

#include "SystemBase.h"
#include "Archetype.h"
#include "Query.h"

namespace ecs
{
	inline void ECS::Init()
	{
		// Create
		m_pEntityMgr		= std::make_shared<EntityMgr>();
		m_pComponentMgr		= std::make_shared<ComponentMgr>();
		m_pSystemMgr		= std::make_shared<SystemMgr>();
		m_pArchetypeMgr		= std::make_shared<ArchetypeMgr>();
		
		// Init
		m_pComponentMgr->Init();
		m_pSystemMgr->Init(this, m_pArchetypeMgr.get());
		m_pArchetypeMgr->Init(m_pEntityMgr.get(), m_pComponentMgr.get());
	}

	inline void ECS::DestroyEntity(EntityID entity)
	{	
		m_DestroyEntities.push_back(entity);
	}

	inline EntityP ECS::GetEntity(EntityID id)
	{
		return m_pEntityMgr->GetEntity(id);
	}

	inline void ECS::Run()
	{
		// Run all system
		m_pSystemMgr->Run();
		// Handle deleting entities
		HandleDestroyEntity();
	}

	inline void ECS::SetPause(bool state)
	{
		m_pSystemMgr->SetPause(state);
	}

	inline bool ECS::GetState() const
	{
		return m_pSystemMgr->GetState();
	}

	inline std::shared_ptr<Archetype> ECS::FindArchetype(GUID id)
	{
		return m_pArchetypeMgr->FindArchetype(id);
	}

	inline std::vector<std::shared_ptr<Archetype>> ECS::Search(Query& query)
	{
		return m_pArchetypeMgr->Search(query);
	}

	inline void ECS::HandleDestroyEntity()
	{
		// Delete duplicating EntityID
		std::ranges::sort(m_DestroyEntities.begin(), m_DestroyEntities.end());
		m_DestroyEntities.erase
		(
			std::unique(m_DestroyEntities.begin(), m_DestroyEntities.end()),
			m_DestroyEntities.end()
		);
		
		for(auto& i : m_DestroyEntities)
		{
			auto entity = m_pEntityMgr->GetEntity(i);
			// Delete from archetype
			entity->m_Archetype->DestroyEntity(entity);
			// Delete from EntityMgr
			m_pEntityMgr->DestroyEntity(entity);
		}
		m_DestroyEntities.clear();
	}

	template <typename ... T_ARGS>
	void ECS::RegisterComponent()
	{
		m_pComponentMgr->RegisterComponent<T_ARGS...>();
	}

	template <typename ... T_ARGS>
	void ECS::RegisterSystem()
	{
		m_pSystemMgr->RegisterSystem<T_ARGS...>();
	}

	template <typename T_SYSTEM>
	std::shared_ptr<SystemBase> ECS::GetSystem()
	{
		return m_pSystemMgr->GetSystem<T_SYSTEM>();
	}

	template <typename ... T_ARGS>
	std::shared_ptr<Archetype> ECS::GetOrCreateArchetype()
	{
		return m_pArchetypeMgr->GetOrCreateArchetype<T_ARGS...>();
	}

	template <typename T_FUNC>
	void ECS::ForEach(std::vector<std::shared_ptr<Archetype>>& archetypes, T_FUNC&& Func)
	{
		m_pArchetypeMgr->ForEach(archetypes, std::forward<T_FUNC&&>(Func));
	}
}
