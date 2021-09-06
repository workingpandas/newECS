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

struct Delete : ecs::SystemBase
{
	constexpr static auto info_v = ecs::SystemInfo{
		.m_pName = "Delete"
	};

	using query = std::tuple<
		ecs::must<ecs::velocity, ecs::position>
	>;
	
	void OnUpdate()
	{
		using namespace ecs;
		Query q1;
		q1.AddFromComponent<velocity>(q1.m_Must);

		auto list = Search(q1);
		QuickPrint("Delete");

		ForEach(list, [&](EntityC& e, velocity& v)
		{
				if (v.x > 50.f) DestroyEntity(e);
		});
		
		//auto list2 = m_ArchetypeMgr->Search(q1);
		//
		//for(auto& i : list)
		//{
		//	auto& v = i->m_Archetype->GetComponent<velocity>(i);
		//	if (v.x > 50.f) m_ecs->DestroyEntity(i->m_EntityID);
		//}
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
	ecs.Init();
	ecs.RegisterComponent<velocity, position, color, rendering>();

	ecs.GetOrCreateArchetype<velocity, position>()
	->CreateEntity(4, [&](velocity& v, position& p)
	{
			v.x = Math::random(0.f, 100.f);
			p.x = Math::random(0.f, 100.f);
	});

	ecs.RegisterSystem<Print, RandomVal, Delete>();

	for (int i = 0; i < 6; ++i) ecs.Run();
	
	return 0;
}