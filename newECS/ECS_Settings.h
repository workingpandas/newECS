#pragma once
#include "pch.h"

namespace ecs
{
	/* Type */
	using uint = int64_t;
	
	/* Settings */
	constexpr uint MAX_ENTITIES						= 8;
	constexpr uint MAX_ENTITIES_PER_ARCHETYPE		= 128;
	constexpr uint MAX_COMPONENTS_PER_ARCHETYPE		= 128;
	constexpr uint MAX_COMPONENT					= 128;

	/* Alias */
	using EntityID	= uint;
	using CID		= uint;
	using GUID		= uint;
	
	using ComponentIndex	= uint;
	
	using Bits		= std::bitset<MAX_COMPONENTS_PER_ARCHETYPE>;
	using CID_List	= std::set<CID>;

	// Forward declare; alias for entity
	struct Entity;
	using  EntityP = std::shared_ptr<Entity>;
	
	/* Error checking variable */
	constexpr uint ERROR_ENTITY_ID		= MAX_ENTITIES;
	constexpr uint ERROR_COMPONENT_ID	= MAX_ENTITIES_PER_ARCHETYPE;
	constexpr uint ARRAY_LAST_INDEX		= MAX_ENTITIES;
	constexpr CID  INVALID_CID			= MAX_COMPONENTS_PER_ARCHETYPE;
}
