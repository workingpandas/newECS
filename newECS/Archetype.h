#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"

namespace ecs
{
	// Forward declare
	class EntityMgr;
	class ComponentMgr;
	class ComponentArray;
	
	class Archetype
	{
	public:
		using ComponentArrayP = std::shared_ptr<ComponentArray>;
		
		Archetype(EntityMgr* entity_mgr);

		template<typename ...T_ARGS>
		void							Init(ComponentMgr* component_mgr);

		template<typename T_FUNC>
		void							CreateEntity(const uint& amount, T_FUNC&& Func);

		void							DestroyEntity(EntityP& entity);

		[[nodiscard]]const Bits&		GetBits() const;
	
		template<typename T_FUNC>
		void							ForEachComponent(T_FUNC&& Func);
		
		template<typename T_COMPONENT>
		T_COMPONENT&					GetComponent(EntityP& entity);

		decltype(auto)					GetAllEntity();

	//private:
		GUID							m_Guid;
		uint							m_Count;
		Bits							m_Bits;
		EntityMgr*						m_pEntityMgr;
		ComponentArrayP					m_pComponents;
		std::vector<EntityID>			m_Entities;
	};
}
#include "Archetype.hpp"
