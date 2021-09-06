#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"
#include "SystemBase.h"
namespace ecs
{
	// Forward declare
	class ArchetypeMgr;
	class ECS;
	
	// SystemBase : T_SYSTEM : SystemFinal
	template<typename T_SYSTEM>
	struct SystemFinal : T_SYSTEM
	{
		constexpr static auto info_v = SystemInfo_v<T_SYSTEM>;
		
		SystemFinal(ECS* ecs, ArchetypeMgr* archetype_mgr);

		void Run(bool pause) override;

		virtual ~SystemFinal();
	};
}
#include "SystemFinal.hpp"
