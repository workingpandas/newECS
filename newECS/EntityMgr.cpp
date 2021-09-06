#include "pch.h"
#include "EntityMgr.h"

namespace ecs
{
	EntityMgr::EntityMgr()
	{
		// Fill up the pool
		for(EntityID i = 0; i < MAX_ENTITIES; ++i)
		{
			m_AvailableID.push(i);
			m_EntityPool.insert(std::pair(i, std::make_shared<Entity>(Entity{ .m_EntityID = i })));
		}
	}

	[[nodiscard]]EntityP& EntityMgr::CreateEntity()
	{
		assert(m_ActiveCount < MAX_ENTITIES);
		// "EntityMgr::CreateEntity / TOO MANY ENTITIES"
		
		auto& e  = m_AvailableID.front();
		m_AvailableID.pop();
		
		++m_ActiveCount;
		
		return m_EntityPool[e];
	}

	void EntityMgr::DestroyEntity(EntityP entity)
	{
		assert(entity->m_EntityID < MAX_ENTITIES);
		// "EntityMgr::DestroyEntity / INVALID ENTITY!"

		// Reset settings
		entity->m_ComponentIndex = ERROR_COMPONENT_ID;
		entity->m_Archetype = nullptr;
		
		// Back to pool
		m_AvailableID.push(entity->m_EntityID);
		
		--m_ActiveCount;
	}

	[[nodiscard]]EntityP& EntityMgr::GetEntity(EntityID id)
	{
		assert(m_EntityPool.find(id) != m_EntityPool.end());
		//	   "EntityMgr::GetEntity / INVALID ID!"
		return m_EntityPool[id];
	}
}
