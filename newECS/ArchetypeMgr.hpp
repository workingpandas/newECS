#pragma once
#include "ArchetypeMgr.h"

#include "Archetype.h"
#include "EntityMgr.h"
#include "ComponentMgr.h"
#include "Query.h"

namespace ecs
{
	inline void ArchetypeMgr::Init(EntityMgr* entityMgr, ComponentMgr* componentMgr)
	{
		m_pEntityMgr = entityMgr;
		m_pComponentMgr = componentMgr;
	}

	inline ArchetypeMgr::ArchetypeP ArchetypeMgr::FindArchetype(GUID id)
	{
		const auto result = m_ArchetypePool.find(id);
		return result == m_ArchetypePool.end() ? nullptr : result->second;
	}

	inline std::vector<ArchetypeMgr::ArchetypeP> ArchetypeMgr::Search(Query& query)
	{
		std::vector<ArchetypeP> result;

		for(auto it = m_ArchetypePool.begin(); it != m_ArchetypePool.end(); ++it)
		{
			if (query.Compare(it->second->GetBits()))
				result.push_back(it->second);
		}
		return result;
	}

	inline std::vector<EntityP> ArchetypeMgr::GetEntities(Query& query)
	{
		std::vector<EntityP> result;
		for (auto it = m_ArchetypePool.begin(); it != m_ArchetypePool.end(); ++it)
		{
			if (query.Compare(it->second->GetBits()))
			{
				auto entities = it->second->GetAllEntity();
				result.insert(result.end(), entities.begin(), entities.end());
			}
		}
		return result;
	}

	template <typename ... T_ARGS>
	ArchetypeMgr::ArchetypeP ArchetypeMgr::GetOrCreateArchetype()
	{
		// Get bits
		Bits bits; ((bits.set(ComponentInfo_v<T_ARGS>.m_CID)), ...);
		
		// Archetype exist
		if(const auto result = m_BitsGetID.find(bits); result != m_BitsGetID.end())
		{
			return m_ArchetypePool[result->second];
		}
		
		// Does not exist; Create archetype
		auto archetype = std::make_shared<Archetype>(m_pEntityMgr);
		archetype->Init<T_ARGS...>(m_pComponentMgr);

		// Add to maps
		m_ArchetypePool.insert(std::pair(archetype->m_Guid, archetype));
		m_BitsGetID.insert(std::pair(archetype->m_Bits, archetype->m_Guid));

		return archetype;
	}

	template <typename T_FUNC>
	void ArchetypeMgr::ForEach(std::vector<ArchetypeP>& archetypes, T_FUNC&& Func)
	{
		for(auto& a : archetypes)
		{
			a->ForEachComponent(std::forward<T_FUNC&&>(Func));
		}
	}
}
