#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"

namespace ecs
{
	class ComponentMgr;
	class EntityMgr;

	// Contain all the components for an archetype
	class ComponentArray
	{
	public:
		// Create component array
		template<typename ...T_ARGS>
		void							Init(ComponentMgr* mgr);

		// Get component by index
		template<typename T_COMPONENT>
		T_COMPONENT&					GetByIndex(ComponentIndex index);

		// Get component by entity
		template<typename T_COMPONENT>
		T_COMPONENT&					GetByEntity(EntityP& entity);

		// Insert empty components
		void							InsertEmpty(EntityP& entity);

		/////////////////////////////////////////////////////////////////////////////////////////
		// Insert single component
		template<typename T_COMPONENT>
		void							InsertComponent(EntityP& entity, T_COMPONENT& component);

		// Insert components; Safe; Will ensure the components passed in matches m_Component
		template<typename ...T_ARGS>
		void							InsertComponent(EntityP& entity, T_ARGS... component);
		/////////////////////////////////////////////////////////////////////////////////////////

		// RemoveEntity all components from entity
		void							RemoveEntity(EntityMgr* mgr, EntityP& entity);

		// Clone the components for an entity
		void							Clone(EntityP& owner, EntityP& clone);
	
	//private:
		// Copy all Dst's component data to Src
		void							Copy(uint DstIndex, uint SrcIndex);
		
		// List of available index
		uint												m_LastIndex = 0;

		// Component arrays
		std::unordered_map<GUID, info>						m_Components;
		
		// Given EntityID, return the component index
		std::unordered_map<EntityID, ComponentIndex>		m_EntityGetIndex;

		// Given component index, return the EntityID (owner)
		std::unordered_map<ComponentIndex, EntityID>		m_IndexGetEntity;
	};
}
#include "ComponentArray.hpp"
