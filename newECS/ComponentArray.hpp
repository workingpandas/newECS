#pragma once
#include "ComponentArray.h"
#include "xCoreFunctions.h"
#include "EntityC.h"

namespace ecs
{
	template <typename ... T_ARGS>
	void ComponentArray::Init(ComponentMgr* mgr)
	{
		// Ensure no duplicates in arguments
		assert(!xCore::tuple_has_duplicates_v<std::tuple<T_ARGS...>>);
		// "ComponentArray::Init / CONTAIN DUPLICATED T_ARGS!"

		// Insert Entity Component
		m_Components.insert(std::pair(ComponentInfo_v<EntityC>.m_Guid, mgr->CreateComponents<EntityC>()));
		// Insert remaining entities
		((m_Components.insert(std::pair(ComponentInfo_v<T_ARGS>.m_Guid, mgr->CreateComponents<T_ARGS>()))), ...);
	}

	template <typename T_COMPONENT>
	T_COMPONENT& ComponentArray::GetByIndex(ComponentIndex index)
	{
		// Ensure this array have the component
		assert(m_Components.find(ComponentInfo_v<T_COMPONENT>.m_Guid) != m_Components.end());

		// Return component array
		return reinterpret_cast<T_COMPONENT&>(m_Components[ComponentInfo_v<T_COMPONENT>.m_Guid].m_ComponentData.get()[index * sizeof(T_COMPONENT)]);
	}

	template <typename T_COMPONENT>
	T_COMPONENT& ComponentArray::GetByEntity(EntityP& entity)
	{
		// Ensure this array have the component
		assert(m_Components.find(ComponentInfo_v<T_COMPONENT>.m_Guid) != m_Components.end());
		//"ComponentArray::InsertComponent / COMPONENT NOT FOUND!"

		// Ensure entity has component
		assert(m_EntityGetIndex.find(entity->m_EntityID) != m_EntityGetIndex.end());
		//	"ComponentArray::InsertComponent /  ENTITY NOT FOUND!"

		return GetByIndex<T_COMPONENT>(entity->m_ComponentIndex);
	}

	inline void ComponentArray::InsertEmpty(EntityP& entity)
	{
		// Ensure not inserting same entity
		assert(m_EntityGetIndex.find(entity->m_EntityID) == m_EntityGetIndex.end());
		// "ComponentArray::InsertComponent /  INSERTING COMPONENT TO SAME ENTITY!"

		// UpdateComponent maps
		m_EntityGetIndex[entity->m_EntityID] = m_LastIndex;
		m_IndexGetEntity[m_LastIndex] = entity->m_EntityID;

		// UpdateComponent entity's component index
		entity->m_ComponentIndex = m_LastIndex++;

		// Update EntityComponent
		GetByIndex<EntityC>(entity->m_ComponentIndex).m_EntityID = entity->m_EntityID;
	}
	
	template <typename T_COMPONENT>
	void ComponentArray::InsertComponent(EntityP& entity, T_COMPONENT& component)
	{		
		// Ensure this array have the component
		assert(m_Components.find(ComponentInfo_v<T_COMPONENT>.m_Guid) != m_Components.end());
		//	   "ComponentArray::InsertComponent / COMPONENT NOT FOUND!"

		// Ensure not inserting same entity
		assert( m_EntityGetIndex.find(entity->m_EntityID) == m_EntityGetIndex.end());
		//	   "ComponentArray::InsertComponent /  INSERTING COMPONENT TO SAME ENTITY!"

		// InsertComponent component
		GetByIndex<T_COMPONENT>(m_LastIndex) = component;
	}

	template <typename ... T_ARGS>
	void ComponentArray::InsertComponent(EntityP& entity, T_ARGS... component)
	{
		// Ensure no duplicates in arguments
		assert(!xCore::tuple_has_duplicates_v<std::tuple<T_ARGS...>>);
		//	"ComponentArray::InsertComponent / CONTAIN DUPLICATED ARGUMENTS!"
		
		//Ensure amount of arguments is the correct amount
		assert(sizeof...(T_ARGS) == m_Components.size());
		//	   "ComponentArray::InsertComponentSafely / MISSING COMPONENTS NEEDED!"

		// Check if input components are in the array
		(assert(m_Components.find(ComponentInfo_v<T_ARGS>.m_Guid) != m_Components.end()), ...);
		// "ComponentArray::InsertComponent / COMPONENT NOT FOUND!"

		// Check if array has enough space
		assert(m_LastIndex + 1 <= MAX_COMPONENTS_PER_ARCHETYPE);
		//	   "ComponentArray::InsertComponent / REACHED MAX CAPACITY!"
		
		// InsertComponent components
		(InsertComponent<T_ARGS>(entity, component), ...);
				
		// UpdateComponent maps
		m_EntityGetIndex[entity->m_EntityID] = m_LastIndex;
		m_IndexGetEntity[m_LastIndex] = entity->m_EntityID;

		// UpdateComponent entity's component index
		entity->m_ComponentIndex = m_LastIndex++;
	}

	inline void ComponentArray::RemoveEntity(EntityMgr* mgr, EntityP& entity)
	{
		// Ensure entity has component
		assert(m_EntityGetIndex.find(entity->m_EntityID) != m_EntityGetIndex.end());
		// "ComponentArray::InsertComponent /  ENTITY NOT FOUND!"

		const uint lastUsedIndex = m_LastIndex - 1;
		const auto deletingEntityIndex = entity->m_ComponentIndex;
		const auto lastValidEntry = m_IndexGetEntity[lastUsedIndex];
		
		// Remove Entity component; copy last valid to removing entity
		Copy(deletingEntityIndex, lastUsedIndex);

		// UpdateComponent the maps
		// Get Entity to be replaced
		auto replacingEntity = mgr->GetEntity(lastValidEntry);

		// UpdateComponent entities
		entity->m_ComponentIndex = ERROR_COMPONENT_ID;
		replacingEntity->m_ComponentIndex = deletingEntityIndex;

		// UpdateComponent maps
		m_EntityGetIndex[lastValidEntry] = deletingEntityIndex;
		m_IndexGetEntity[deletingEntityIndex] = lastValidEntry;

		m_EntityGetIndex.erase(entity->m_EntityID);
		m_IndexGetEntity.erase(lastValidEntry);
		
		// UpdateComponent count
		--m_LastIndex;
	}

	inline void ComponentArray::Clone(EntityP& owner, EntityP& clone)
	{
		// Ensure owner is in this array
		assert(m_EntityGetIndex.find(owner->m_EntityID) != m_EntityGetIndex.end());
		
		// Ensure clone is NOT in this array
		assert(m_EntityGetIndex.find(clone->m_EntityID) == m_EntityGetIndex.end() ||
			   clone->m_Archetype == nullptr);
		//"ComponentArray::Clone /  CLONE HAS COMPONENTS!"

		// Insert components for clone
		// Add last available slot for clone
		m_EntityGetIndex[clone->m_EntityID] = m_LastIndex;
		m_IndexGetEntity[m_LastIndex] = clone->m_EntityID;


		// Copy values from owner to clone
		Copy(m_LastIndex, owner->m_ComponentIndex);

		// UpdateComponent entity's component index
		clone->m_ComponentIndex = m_LastIndex++;
	}

	inline void ComponentArray::Copy(uint DstIndex, uint SrcIndex)
	{
		for (auto component = m_Components.begin(); component != m_Components.end(); ++component)
		{
			// Replace the target with the last index
			auto& size = component->second.m_Size;
			auto arr = component->second.m_ComponentData.get();

			// Can be trivially copied
			if ((*component).second.m_pCopyFn == nullptr)
			{
				// Default memcpy
				std::memcpy(arr + DstIndex * size, arr + SrcIndex * size, size);
			}
			// Use copy function
			else
			{
				(*component).second.m_pCopyFn(arr + DstIndex * size, arr + SrcIndex * size);
			}
		}
	}
}
