#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"

namespace ecs
{
	struct SystemBase;
	class ArchetypeMgr;
	class ECS;
	
	class SystemMgr
	{
	public:
		/* Alias */
		using SystemP = std::shared_ptr<SystemBase>;
		using SystemList = std::pair<GUID, SystemP>;

		/* Functions */
		void							Init(ECS* ecs, ArchetypeMgr* mgr);

		template<typename... T_ARGS>
		void							RegisterSystem();
		
		template<typename T_SYSTEM>
		SystemP							GetSystem();

		void							Run();

		void							SetPause(bool state);

		bool							GetState() const;
	
//	private:
		template<typename T_SYSTEM>
		void Register();
		
		bool						m_Pause				= false;
		ArchetypeMgr*				m_pArchetypeMgr		= nullptr;
		ECS*						m_pECS				= nullptr;
		std::vector<SystemList>		m_Systems			{};
	};


}
#include "SystemMgr.hpp"