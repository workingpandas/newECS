#pragma once
#include "pch.h"
#include "ECS_Settings.h"

namespace ecs
{
	class EntityMgr;
	class ComponentMgr;
	class SystemMgr;
	class ArchetypeMgr;
	class Archetype;
	
	struct SystemBase;
	struct Query;

	class ECS
	{
	public:
		void											Init();

		void											DestroyEntity(EntityID entity);
		
// EntityMgr
		EntityP&										GetEntity(EntityID id);

// ComponentMgr
		template<typename... T_ARGS>
		void											RegisterComponent();

// SystemMgr
		template<typename... T_ARGS>
		void											RegisterSystem();

		template<typename T_SYSTEM>
		std::shared_ptr<SystemBase>						GetSystem();

		void											Run();

		void											SetPause(bool state);

		bool											GetState() const;

// ArchetypeMgr
		template<typename ...T_ARGS>
		std::shared_ptr<Archetype>						GetOrCreateArchetype();
		
		std::shared_ptr<Archetype>						FindArchetype(GUID id);

		std::vector<std::shared_ptr<Archetype>>			Search(Query& query);

		template<typename T_FUNC>
		void											ForEach(std::vector<std::shared_ptr<Archetype>>& archetypes, T_FUNC&& Func);

//	private:
		void HandleDestroyEntity();

		std::shared_ptr<EntityMgr>						m_pEntityMgr;
		std::shared_ptr<ComponentMgr>					m_pComponentMgr;
		std::shared_ptr<SystemMgr>						m_pSystemMgr;
		std::shared_ptr<ArchetypeMgr>					m_pArchetypeMgr;
		std::vector<EntityID>							m_DestroyEntities;
	};
}
#include "ECS.hpp"