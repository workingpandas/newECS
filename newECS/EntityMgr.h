#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "pch.h"
#include "ECS_Settings.h"
#include "Entity.h"

namespace ecs
{
	// Manage all entities
	class EntityMgr
	{
	public:
		EntityMgr();

		// Create an entity
		[[nodiscard]]EntityP& CreateEntity();

		// Push entity back to pool & reset the values
		void DestroyEntity(EntityP entity);

		// Get an entity using EntityID
		[[nodiscard]]EntityP& GetEntity(EntityID id);

	//private:
		// Pool of entities
		std::queue<EntityID>					m_AvailableID{};

		// Table of each entity and their archetype
		std::unordered_map<EntityID, EntityP>	m_EntityPool{};

		// Amount of entities
		size_t									m_ActiveCount{};
	};
}

#endif
