#pragma once
#include "SystemMgr.h"
#include "SystemBase.h"
#include "SystemFinal.h"

namespace ecs
{
	inline void SystemMgr::Init(ECS* ecs, ArchetypeMgr* mgr)
	{
		m_pECS = ecs;
		m_pArchetypeMgr = mgr;
	}

	template <typename ... T_ARGS>
	void SystemMgr::RegisterSystem()
	{
		((Register<T_ARGS>()), ...);
	}

	template <typename T_SYSTEM>
	void SystemMgr::Register()
	{
		// Ensure no duplication
		auto info = SystemInfo_v<T_SYSTEM>;
		assert([&]()->bool
		{
			for(const auto& id : std::views::keys(m_Systems)){
				if(id == info.m_Guid) return false;
			}
			return true;
		} ());

		// Register system
		m_Systems.push_back(
			std::pair(SystemInfo_v<T_SYSTEM>.m_Guid, std::make_shared<SystemFinal<T_SYSTEM>>(m_pECS, m_pArchetypeMgr))
		);
	}

	template <typename T_SYSTEM>
	SystemMgr::SystemP SystemMgr::GetSystem()
	{
		auto id = SystemInfo_v<T_SYSTEM>.m_Guid;
		for(auto& system : m_Systems)
		{
			if (system.first == id) return system.second;
		}
		// System not found
		assert(false);
		return nullptr;
	}

	inline void SystemMgr::Run()
	{
		for(auto& pair : std::views::values(m_Systems)){
			pair->Run(m_Pause);
		}
	}

	inline void SystemMgr::SetPause(bool state)
	{
		m_Pause = state;
	}

	inline bool SystemMgr::GetState() const
	{
		return m_Pause;
	}
}
