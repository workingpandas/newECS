#pragma once
#include "pch.h"

#include "ECS_Settings.h"

namespace ecs
{
	// Forward declare
	class Archetype;
	class EntityMgr;
	class ComponentMgr;
	struct Query;
	
	class ArchetypeMgr
	{
	public:
		using ArchetypeP = std::shared_ptr<Archetype>;

		void							Init(EntityMgr* entityMgr, ComponentMgr* componentMgr);
		
		template<typename ...T_ARGS>
		ArchetypeP						GetOrCreateArchetype();

		ArchetypeP						FindArchetype(GUID id);

		std::vector<ArchetypeP>			Search(Query& query);

		std::vector<EntityP>			GetEntities(Query& query);
		
		template<typename T_FUNC>
		void							ForEach(std::vector<ArchetypeP>& archetypes, T_FUNC&& Func);

//	private:
		std::unordered_map<GUID, ArchetypeP>	m_ArchetypePool;
		std::unordered_map<Bits, GUID>			m_BitsGetID;
		EntityMgr*								m_pEntityMgr		= nullptr;
		ComponentMgr*							m_pComponentMgr		= nullptr;
	};
}
#include "ArchetypeMgr.hpp"