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
		void							OnCreate()			{}

		// Before update
		void							OnPreUpdate()		{}

		// Update
		void							OnUpdate()			{}

		// Post update
		void							OnPostUpdate()		{}

		// Pause
		void							OnPause()			{}

		// When system is destroyed
		void							OnDestroy()			{}
		
		// Run all function; Don't need to override this function
		virtual void					Run(bool pause)		{}

		/* UTILITIES FUNCTIONS */
		template<typename T_FUNC>
		// For each archetype, run the lambda function that will affect their components
		void							ForEach(std::vector<std::shared_ptr<Archetype>>& archetypes, T_FUNC&& Func);

		// Get or create an archetype
		template<typename... T_ARGS>
		decltype(auto)					GetOrCreateArchetype();

		// Destroy an entity by EntityID
		void							DestroyEntity(EntityID entity);

		// Destroy an entity by component
		void							DestroyEntity(EntityC& entity);

		// Search for archetype that satisfied the query
		decltype(auto)					Search(Query& query);

		// Get pause state
		bool							GetPauseState() const;

		// Set pause state
		void							SetPause(bool state);

		// Get system ptr
		template<typename T_SYSTEM>
		decltype(auto)					GetSystem();
		
		// Managers
		ArchetypeMgr*					m_ArchetypeMgr		= nullptr;
		ECS*							m_ecs				= nullptr;
	};
}
#include "SystemBase.hpp"
