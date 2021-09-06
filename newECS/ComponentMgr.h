#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"
#include "ComponentCreator.h"

namespace ecs
{
	// Forward declare
	class ComponentArray;
	
	class ComponentMgr
	{
	public:
		void Init();
		
		template<typename... T_ARGS>
		void RegisterComponent();

		template<typename T_COMPONENT>
		info CreateComponents();

		template<typename ...T_ARGS>
		std::shared_ptr<ComponentArray> CreateArray();
	
	private:
		template<typename T_COMPONENT>
		void Register();
		
		std::map<GUID, std::shared_ptr<ICreator>> m_Creators;
		CID m_NextID = 0;
	};
}
#include "ComponentMgr.hpp"