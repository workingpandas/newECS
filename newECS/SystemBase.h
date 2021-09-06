#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"
#include "EntityC.h"

namespace ecs
{
	// Forward declare
	class Archetype;
	class ArchetypeMgr;
	class SystemMgr;
	class ECS;
		
	struct SystemBase
	{
		/* System for user to overwrite */
		//When system is created
		void						OnCreate()			{}

		// Before update
		void						OnPreUpdate()		{}

		// Update
		void						OnUpdate()			{}

		// Post update
		void						OnPostUpdate()		{}

		// Pause
		void						OnPause()			{}

		// Pause
		void						OnDestroy()			{}
		
		// Run all function; Don't need to override this function
		virtual void				Run(bool pause)		{}

		/* UTILITIES FUNCTIONS */
		template<typename T_FUNC>
		void						ForEach(std::vector<std::shared_ptr<Archetype>>& archetypes, T_FUNC&& Func);

		template<typename... T_ARGS>
		decltype(auto)				GetOrCreateArchetype();

		void						DestroyEntity(EntityID entity);

		void						DestroyEntity(EntityC& entity);

		decltype(auto)				Search(Query& query);

		bool						GetPauseState() const;

		void			SetPause(bool state);

		template<typename T_SYSTEM>
		decltype(auto)	GetSystem();
		
		// Managers
		ArchetypeMgr*	m_ArchetypeMgr		= nullptr;
		ECS*			m_ecs				= nullptr;
	};
}
#include "SystemBase.hpp"
