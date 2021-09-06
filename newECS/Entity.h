#pragma once
#include "pch.h"
#include "ECS_Settings.h"

namespace ecs
{
	// Predeclared archetype
	class Archetype;
	
	struct Entity
	{
		/* Data members */
		EntityID		m_EntityID			=	ERROR_ENTITY_ID;	// Entity ID
		ComponentIndex	m_ComponentIndex	=	ERROR_COMPONENT_ID;	// Index in an archetype; access component
		Archetype*		m_Archetype			=	nullptr;			// Pointer to it's archetype
	};	
}
