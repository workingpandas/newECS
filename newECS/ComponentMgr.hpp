#pragma once
#include "pch.h"
#include "ComponentMgr.h"
#include "ComponentArray.h"
#include "xCoreFunctions.h"
#include "EntityC.h"

namespace ecs
{
	template <typename T_COMPONENT>
	void ComponentMgr::Register()
	{
		assert(m_Creators.find(ComponentInfo_v<T_COMPONENT>.m_Guid) == m_Creators.end());
		//	   "ComponentMgr::Register() / COMPONENT ALREADY REGISTERED!"

		
		// Add to creators
		m_Creators[ComponentInfo_v<T_COMPONENT>.m_Guid] = std::make_shared<ComponentCreator<T_COMPONENT>>();

		// Add Component ID
		ComponentInfo_v<T_COMPONENT>.m_CID = m_NextID++;
	}

	template <typename ... T_ARGS>
	void ComponentMgr::RegisterComponent()
	{
		// Ensure no duplicates in arguments
		assert(!xCore::tuple_has_duplicates_v<std::tuple<T_ARGS...>>); //"ComponentMgr::RegisterComponent / CONTAIN DUPLICATED ARGUMENTS!"

		// RegisterComponent
		((Register<T_ARGS>()), ...);
	}

	template <typename T_COMPONENT>
	info ComponentMgr::CreateComponents()
	{
		assert(m_Creators.find(ComponentInfo_v<T_COMPONENT>.m_Guid) != m_Creators.end());
		//	   "ComponentMgr::CreateComponents() / COMPONENT NOT REGISTERED!"

		return m_Creators[ComponentInfo_v<T_COMPONENT>.m_Guid]->Create();
	}

	template <typename ... T_ARGS>
	std::shared_ptr<ComponentArray> ComponentMgr::CreateArray()
	{
		auto result = std::make_shared<ComponentArray>();
		result->Init<T_ARGS...>(this);
		return result;
	}

	inline void ComponentMgr::Init()
	{
		Register<EntityC>();
	}
}
