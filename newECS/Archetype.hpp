#pragma once
#include "Archetype.h"
#include "ComponentMgr.h"
#include "ComponentArray.h"
#include "xCoreFunctions.h"

namespace ecs
{
	inline Archetype::Archetype(EntityMgr* entity_mgr)
		: m_Count{ 0 }, m_pEntityMgr{ entity_mgr }, m_Guid{ 0 }
	{

	}

	inline void Archetype::DestroyEntity(EntityP& entity)
	{
		// Ensure deleting entity is in this archetype
		if (m_Entities.empty()) return;
		
		const auto it = std::ranges::find(m_Entities.begin(), m_Entities.end(), entity->m_EntityID);
		assert(it != m_Entities.end()); // "Archetype::DestroyEntity / ENTITY IS NOT IN ARCHETYPE"

		// Remove from components array
		m_pComponents->RemoveEntity(m_pEntityMgr, entity);
		// Remove from vector
		m_Entities.erase(it);
		
		--m_Count;
	}

	inline const Bits& Archetype::GetBits() const
	{
		return m_Bits;
	}

	template <typename ... T_ARGS>
	void Archetype::Init(ComponentMgr* component_mgr)
	{
		// Ensure no duplicating T_ARGS
		assert(!xCore::tuple_has_duplicates_v<std::tuple<T_ARGS...>>); // "Archetype::Init / CONTAIN DUPLICATED T_ARGS"
		
		// Create bits
		(m_Bits.set(ComponentInfo_v<T_ARGS>.m_CID), ...);

		// Create Component arrays
		m_pComponents = component_mgr->CreateArray<T_ARGS...>();

		// Generate an unique ID
		m_Guid = StringToID(__FUNCSIG__);
	}

	template< typename T_FUNC >
	void Archetype::CreateEntity(const uint& amount, T_FUNC&& Func )
	{
		using my_tuple = typename xCore::details::params_to_tuple<decltype(&T_FUNC::operator())>::type;

		// Check if creating too much entity
		assert(m_Count + 1 < MAX_ENTITIES_PER_ARCHETYPE); // "Archetype::CreateEntity / MAX CAPACITY REACHED"

		// Create n-amount of entities
		for(uint i = 0; i < amount; ++i)
		{
			my_tuple Tuple;

			// Create entity
			auto entity = m_pEntityMgr->CreateEntity();
			entity->m_Archetype = this;
			m_Entities.push_back(entity->m_EntityID);

			// Insert components
			m_pComponents->InsertEmpty(entity);
			[&] <typename...X >(std::tuple<X...>& t)
			{
				((std::get<X>(Tuple) = &m_pComponents->GetByEntity<std::remove_pointer_t<X>>(entity)), ...);

				Func(*std::get<X>(Tuple) ...);
			}(Tuple);
			
			// UpdateComponent count
			++m_Count;
		}
	}

	template <typename T_FUNC>
	void Archetype::ForEachComponent(T_FUNC&& Func)
	{
		using my_tuple = typename xCore::details::params_to_tuple<decltype(&T_FUNC::operator())>::type;

		for(auto i : m_Entities)
		{
			my_tuple Tuple;
			[&] <typename...X >(std::tuple<X...>&t)
			{
				((std::get<X>(Tuple) = &m_pComponents->GetByEntity<std::remove_pointer_t<X>>(m_pEntityMgr->GetEntity(i))), ...);

				Func(*std::get<X>(Tuple) ...);
			}(Tuple);
		}
	}

	template <typename T_COMPONENT>
	T_COMPONENT& Archetype::GetComponent(EntityP& entity)
	{
		return m_pComponents->GetByEntity<T_COMPONENT>(entity);
	}

	inline decltype(auto) Archetype::GetAllEntity()
	{
		std::vector<EntityP> result;
		for (auto id : m_Entities) result.push_back(m_pEntityMgr->GetEntity(id));

		return result;
	}
}
