#include "pch.h"
#include "ECS_Settings.h"
#include "velocity.h"
#include "ECS.h"
#include "SystemBase.h"
#include "Query.h"
#include "EntityC.h"
#include "TRandom.hpp"

// Memory leak test
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// System example
// All system inherit from SystemBase
struct Delete : ecs::SystemBase
{
	// All system needs a SystemInfo
	// You can overwrite the name & ID if you wan
	constexpr static auto info_v = ecs::SystemInfo{
		.m_pName = "Delete"
	};

	// All system needs a query (std::tuple)
	// Must: Components that an archetypes MUST have
	// NoneOf: Components that an archetypes MUST NOT have
	// OneOf: As long as archetype have 1 of the input components
	using query = std::tuple<
		ecs::must<ecs::velocity, ecs::position>
	>;

	// You can define these functions:
	// OnCreate: Will run when the system is created
	// OnDestroy: Will run when system is destroyed
	// OnPreUpdate: Will run before update is run
	// OnUpdate: Update function
	// OnPostUpdate: Will run after OnUpdate finished
	// OnPause: Will run when SystemMgr's state is set to pause
	// 
	// () operator: Function similarly to OnUpdate. The purpose of this
	// is if the update function is not complex (i.e only to overwrite values or
	// trivial task), you can use this instead of OnUpdate.
	// OnUpdate is for more complex functions (i.e you are affecting entities from
	// 2 or more different archetype

	// Don't need overwrite
	void OnUpdate()
	{
		using namespace ecs;

		// Creating a query
		Query q1;
		// This query is asking for archetype with velocity component
		q1.AddFromComponent<velocity>(q1.m_Must);

		// Get all archetype
		auto list = Search(q1);
		//QuickPrint("Delete");

		// For each archetype, run the lambda function
		// COMPONENTS MUST BE A REFERENCE (&, or else you are not affecting the components)
		ForEach(list, [&](EntityC& e, velocity& v)
		{
				if (v.x > 50.f)
				{
					QuickPrint("Deleting " + std::to_string(e.m_EntityID) + " with value " + std::to_string(v.x));
					// Destroy this entity
					DestroyEntity(e);
				}
		});
		QuickPrint("");
	}
};

struct RandomVal : ecs::SystemBase
{
	constexpr static auto info_v = ecs::SystemInfo{
		.m_pName = "RandomVal"
	};

	using query = std::tuple<
		ecs::must<ecs::velocity, ecs::position>
	>;

	// Using () instead of OnUpdate
	// Trivial function
	void operator()(ecs::velocity& v) const
	{
		const auto newval = Math::random(0.f, 100.f);
		QuickPrint("Random new value: " + std::to_string(newval));
		v.x = newval;
	}
};

struct Print : ecs::SystemBase
{
	constexpr static auto info_v = ecs::SystemInfo{
		.m_pName = "Print"
	};

	using query = std::tuple<
		ecs::must<ecs::velocity, ecs::position>
	>;
	
	void operator()(EntityC& e, ecs::velocity& v) const
	{
		QuickPrint(e.m_EntityID);
		QuickPrint(v.x);
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	using namespace ecs;
	ECS ecs;

	// Init ecs
	ecs.Init();

	// Register components
	ecs.RegisterComponent<velocity, position, color, rendering>();

	// Get or create an archetype
	// After getting the archetype ptr, run CreateEntity
	// Creating 4 entities and initialize them to the values in the lambda function
	ecs.GetOrCreateArchetype<velocity, position>()
	->CreateEntity(4, [&](velocity& v, position& p)
	{
			v.x = Math::random(0.f, 100.f);
			p.x = Math::random(0.f, 100.f);
	});

	// Register systems
	// Order MATTERS
	// Print run first, then RandomVal, then Delete	
	ecs.RegisterSystem<Print, RandomVal, Delete>();

	// Run the system for 6 times
	for (int i = 0; i < 6; ++i) ecs.Run();
	
	return 0;
}	