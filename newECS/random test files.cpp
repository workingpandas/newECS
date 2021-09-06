#include "pch.h"
///*
//struct archetype
//{
//	template< typename T >
//	T& getComponentByIndex( int Index )
//	{
//		auto Pair = m_Components.find( component::info_v<T>.m_Guid );
//		return reinterpret_cast<T&>(Pair.second.m_ComponentData.get()[Index * sizeof(T)]);
//	}
//
//	(([&]<typename T>(T*)
//	{
//		m_Bits.set(T::info_v.m_CID);
//		m_Components[T::info_v.m_Guid] = component_mgr->CreateComponents<T>();
//	}(reinterpret_cast<T_ARGS*>(nullptr))), ... );
//
//	int m_nEntites;
//	ecs::Bits m_Bits;
//	std::set<ecs::Entity> m_entities;
//	std::map<ecs::GUID, info> m_Components;
//};
//
//
//*/
//struct complex
//{
//	constexpr static auto info_v = ecs::ComponentInfo{
//		.m_pName = "complex"
//	};
//
//	std::vector<int> v;
//	complex()
//	{
//
//	}
//	complex(const complex& rhs)
//	{
//		for (auto i : rhs.v)	v.push_back(i);
//	}
//};
//
//void test()
//{
//	using namespace ecs;
//	EntityMgr em;
//	ComponentMgr cm;
//	ComponentArray arr;
//	auto e1 = em.CreateEntity();
//	auto e2 = em.CreateEntity();
//	auto e3 = em.CreateEntity();
//	auto e4 = em.CreateEntity();
//	auto e5 = em.CreateEntity();
//	auto e6 = em.CreateEntity();
//
//	cm.RegisterComponent<velocity, position, color, rendering>();
//
//	//cm.RegisterComponent<complex>();
//
//	//auto& c1 = reinterpret_cast<complex&>(t.m_ComponentData.get()[0 * t.m_Size]);
//	//c1.v.push_back(1);
//	//c1.v.push_back(2);
//	//c1.v.push_back(3);
//
//	//complex c2;
//	//c2.v.push_back(11);
//	//c2.v.push_back(22);
//	//c2.v.push_back(33);
//
//	//complex c3;
//	//c3.v.push_back(10);
//	//c3.v.push_back(20);
//	//c3.v.push_back(30);
//
//	//auto c = cm.CreateComponents<complex>();
//
//	//arr.Init<complex>(&cm);
//
//	//complex c1;
//	//c1.v.push_back(1);
//	//c1.v.push_back(2);
//	//c1.v.push_back(3);
//
//	//complex c2;
//	//c2.v.push_back(11);
//	//c2.v.push_back(22);
//	//c2.v.push_back(33);
//
//	//complex c3;
//	//c3.v.push_back(10);
//	//c3.v.push_back(20);
//	//c3.v.push_back(30);
//
//	//arr.InsertComponent(e1, c1);
//	//arr.InsertComponent(e2, c2);
//	//arr.InsertComponent(e3, c3);
//
//	//arr.RemoveEntity(&em, e1);
//	//arr.RemoveEntity(&em, e3);
//	////QuickPrint(arr.GetByIndex<complex>(0).v[1]);
//
//	//arr.Clone(e2, e4);
//	//QuickPrint(arr.GetByEntity<complex>(e4).v[1]);
//	//QuickPrint(arr.GetByEntity<complex>(e2).v[1]);
//	//QuickPrint(e2.m_ComponentIndex);
//	//QuickPrint(e4.m_ComponentIndex);
//
//	auto narr = cm.CreateArray<velocity, position, rendering>();
//
//	narr->InsertComponent(e1,
//		velocity{ .x = 123, .y = 321, .z = 567 },
//		position{ .x = -1.f, .y = -.1f },
//		rendering{ .render = true });
//
//	narr->InsertComponent(e2,
//		velocity{ .x = 1, .y = 2, .z = 3 },
//		position{ .x = 1000.f, .y = 1000.f },
//		rendering{ .render = false });
//
//	narr->InsertComponent(e3,
//		velocity{ .x = 69, .y = 0, .z = 0 },
//		position{ .x = .0f, .y = 0.f },
//		rendering{ .render = true });
//
//	narr->InsertComponent(e4,
//		velocity{ .x = 123, .y = 321, .z = 567 },
//		position{ .x = -11111.f, .y = -.1f },
//		rendering{ .render = true });
//
//	narr->InsertComponent(e5,
//		velocity{ .x = 1444, .y = 2, .z = 3 },
//		position{ .x = 1000.f, .y = 1000.f },
//		rendering{ .render = false });
//
//	narr->InsertComponent(e6,
//		velocity{ .x = 69, .y = 0, .z = 0 },
//		position{ .x = .011f, .y = 0.f },
//		rendering{ .render = true });
//
//	narr->RemoveEntity(&em, e1);
//	QuickPrint(narr->GetByEntity<position>(e4).x);
//	QuickPrint(narr->GetByEntity<position>(e3).x);
//	QuickPrint(narr->GetByEntity<velocity>(e5).x);
//
//	narr->RemoveEntity(&em, e3);
//
//	QuickPrint(narr->GetByEntity<position>(e2).x);
//	QuickPrint(narr->GetByEntity<position>(e6).x);
//	QuickPrint(narr->GetByEntity<velocity>(e5).x);
//
//	narr->RemoveEntity(&em, e6);
//	QuickPrint(narr->GetByEntity<position>(e2).x);
//	QuickPrint(narr->GetByEntity<velocity>(e4).x);
//	/////////////////////////////////////////////////////////
//	QuickPrint("");
//	arr.Init<velocity, position, rendering>(&cm);
//
//	arr.InsertComponent(e1,
//		velocity{ .x = 123, .y = 321, .z = 567 },
//		position{ .x = -1.f, .y = -.1f },
//		rendering{ .render = true });
//
//	arr.InsertComponent(e2,
//		velocity{ .x = 1, .y = 2, .z = 3 },
//		position{ .x = 1000.f, .y = 1000.f },
//		rendering{ .render = false });
//
//	arr.InsertComponent(e3,
//		velocity{ .x = 69, .y = 0, .z = 0 },
//		position{ .x = .0f, .y = 0.f },
//		rendering{ .render = true });
//
//	arr.InsertComponent(e4,
//		velocity{ .x = 123, .y = 321, .z = 567 },
//		position{ .x = -11111.f, .y = -.1f },
//		rendering{ .render = true });
//
//	arr.InsertComponent(e5,
//		velocity{ .x = 1444, .y = 2, .z = 3 },
//		position{ .x = 1000.f, .y = 1000.f },
//		rendering{ .render = false });
//
//	arr.InsertComponent(e6,
//		velocity{ .x = 69, .y = 0, .z = 0 },
//		position{ .x = .011f, .y = 0.f },
//		rendering{ .render = true });
//
//	arr.RemoveEntity(&em, e1);
//	QuickPrint(arr.GetByEntity<position>(e4).x);
//	QuickPrint(arr.GetByEntity<position>(e3).x);
//	QuickPrint(arr.GetByEntity<velocity>(e5).x);
//
//	arr.RemoveEntity(&em, e3);
//
//	QuickPrint(arr.GetByEntity<position>(e2).x);
//	QuickPrint(arr.GetByEntity<position>(e6).x);
//	QuickPrint(arr.GetByEntity<velocity>(e5).x);
//
//	arr.RemoveEntity(&em, e6);
//	QuickPrint(arr.GetByEntity<position>(e2).x);
//	QuickPrint(arr.GetByEntity<velocity>(e4).x);
//}
//void test2()
//{
//	using namespace ecs;
//	EntityMgr em{};
//	ComponentMgr cm;
//	cm.RegisterComponent<velocity, position, color>();
//
//	/////////////////////////////////////////////////////////////////////////
//	//Archetype a(&em);
//	//a.Init<velocity, position>(&cm);
//
//	//Archetype b(&em);
//	//b.Init<color>(&cm);
//	//
//	//a.CreateEntity(2, [&](velocity& v, position& c)
//	//	{
//	//		v.x = Math::random(0.f, 100.f);
//	//		c.x = Math::random(0.f, 100.f);
//	//	});
//
//	//b.CreateEntity(3, [&](color& c)
//	//	{
//	//		c.r = Math::random(0.f, 1.f);
//	//	});
//
//	//QuickPrint(a.m_Entities.size());
//	//QuickPrint(b.m_Entities.size());
//	/////////////////////////////////////////////////////////////////////////
//
//	ArchetypeMgr am;
//
//	am.Init(&em, &cm);
//
//	am.GetOrCreateArchetype<velocity, position>()
//		->CreateEntity(2, [&](velocity& v, position& c)
//			{
//				v.x = Math::random(0.f, 100.f);
//				c.x = Math::random(0.f, 100.f);
//			});
//
//	QuickPrint(am.GetOrCreateArchetype<position, velocity>()->m_Entities.size());
//
//	/////////////////////////////////////////////////////////////////////////
//}
//void test3()
//{
//	using namespace ecs;
//	//ComponentMgr cm;
//	//cm.RegisterComponent<velocity, position, color>();
//	//
//	//Query result;
//	//result.AddFromComponent<velocity>(result.m_Must);
//	//result.AddFromComponent<color>(result.m_NoneOf);
//	//
//	//Query a;
//	//a.AddQueryFromTuple<sys::query>();
//
//
//	EntityMgr em{};
//	ComponentMgr cm;
//	cm.RegisterComponent<velocity, position, color, rendering>();
//
//	/////////////////////////////////////////////////////////////////////////
//
//	ArchetypeMgr am;
//	am.Init(&em, &cm);
//
//	// E0, E1
//	auto ta = am.GetOrCreateArchetype<velocity, position, color>();
//	ta->CreateEntity(2, [&](velocity& v, position& p, color& c)
//		{
//			v.x = Math::random(0.f, 100.f);
//		});
//
//	// E2, E3
//	auto tb = am.GetOrCreateArchetype<position, color, rendering>();
//	tb->CreateEntity(2, [&](position& p, color& c, rendering& r)
//		{
//			p.x = Math::random(0.f, 100.f);
//		});
//
//	// E4, E5
//	auto tc = am.GetOrCreateArchetype<position, velocity>();
//	tc->CreateEntity(2, [&](position& p, velocity& v)
//		{
//			v.x = Math::random(0.f, 100.f);
//		});
//
//	decltype(auto) e1 = em.m_EntityPool.find(0);
//	auto c11 = e1->second->m_Archetype->GetComponent<velocity>(e1->second);
//
//	auto c12 = ta->GetComponent<velocity>(em.GetEntity(ta->m_Entities[0]));
//
//	QuickPrint(c11.x);
//	QuickPrint(c12.x);
//
//	ta->ForEachComponent([&](velocity& v)
//		{
//			v.x = 100.f;
//		});
//	auto c111 = e1->second->m_Archetype->GetComponent<velocity>(e1->second);
//
//	auto c122 = ta->GetComponent<velocity>(em.GetEntity(ta->m_Entities[0]));
//	QuickPrint(c111.x);
//	QuickPrint(c122.x);
//	Query one, two, three;
//
//	one.AddFromComponent<velocity>(one.m_Must);
//	one.AddFromComponent<color>(one.m_NoneOf);
//
//	auto r1 = am.Search(one);
//
//	QuickPrint(r1.size());
//	QuickPrint(tc->m_Guid);
//	QuickPrint(r1[0]->m_Guid);
//	QuickPrint("");
//
//	two.AddFromComponent<velocity>(two.m_Must);
//
//	auto r2 = am.Search(two);
//	QuickPrint(r2.size());
//	QuickPrint(ta->m_Guid);
//	QuickPrint(r2[0]->m_Guid);
//	QuickPrint(tc->m_Guid);
//	QuickPrint(r2[1]->m_Guid);
//	/////////////////////////////////////////////////////////////////////////
//
//}
//void test4()
//{
//	//EntityMgr em;
////ComponentMgr cm;
////ArchetypeMgr am;
//
////cm.RegisterComponent<velocity, color, position, rendering>();
////am.Init(&em, &cm);
////	
////auto a1 = am.GetOrCreateArchetype<velocity, color, position>();
////a1->CreateEntity(4,[&](velocity& v, color& c, position& p)
////{
////		v.x = Math::random(0.f, 100.f);
//
////		c.r = Math::random(0.f, 1.f);
//
////		p.x = Math::random(0.f, 100.f);
//
////		QuickPrint(v.x);
//
////});
//
////SystemMgr sm{};
////sm.Init(&am);
////sm.RegisterSystem<DoSomething>();
////auto result = sm.GetSystem<DoSomething>();
//
////sm.Run();
//
////QuickPrint("");
////a1->ForEachComponent([&](velocity& v, color& c)
////{
////		QuickPrint(v.x);
////});
//
////QuickPrint("");
////Query qq;
////qq.AddFromComponent<velocity, color>(qq.m_Must);
////auto list = am.Search(qq);
//
////am.ForEach(list, DoSomething{});
//
////SystemFinal<DoSomething>DoSomethingFinal(&am);
////DoSomethingFinal.Run(false);
//
//
////SystemBase* DoSomethingFinal = new SystemFinal<DoSomething> (&am);
//////DoSomethingFinal.Run(false);
//////DoSomethingFinal->Run(true);
//
////std::vector<ecs::SystemBase*>ptr;
////ptr.push_back(DoSomethingFinal);
////QuickPrint("TEST");
////ptr[0]->Run(false);
//}
//
//struct renderSystem : ecs::SystemBase
//{
//	constexpr static auto typedef_v = ecs::SystemInfo{
//		.m_pName = "rendering"
//	};
//
//	using query = std::tuple<
//		ecs::must<ecs::velocity>,
//		ecs::none_of<ecs::color>
//	>;
//};
//
//struct DoSomething : public ecs::SystemBase
//{
//	constexpr static auto info_v = ecs::SystemInfo{
//		.m_pName = "DoSomething"
//	};
//
//	using query = std::tuple<
//		ecs::must<ecs::velocity, ecs::color>
//	>;
//
//	void Run(bool pause) override
//	{
//		QuickPrint("RUNNING");
//	}
//
//	//void OnUpdate()
//	//{
//	//	using namespace ecs;
//	//	QuickPrint("DoSomething OnUpdate");
//
//	//	Query q1;
//	//	q1.AddFromComponent<velocity, color>(q1.m_Must);
//
//	//	auto list = m_ArchetypeMgr->Search(q1);
//
//	//	ForEach(list, [&](velocity& v, color& c)
//	//	{
//	//			ForEach(list, [&](velocity& v2, color& c2)
//	//			{
//	//				QuickPrint("ForEach2");
//	//				v2.x = 100.f;
//	//			});
//	//			QuickPrint("ForEach1");
//	//			QuickPrint(v.x);
//	//	});
//	//}
//
//	void OnPause()
//	{
//		QuickPrint("DoSomething On Pause ");
//	}
//
//	void OnPreUpdate()
//	{
//		QuickPrint("DoSomething OnPreUpdate");
//	}
//
//	void OnPostUpdate()
//	{
//		QuickPrint("DoSomething OnPostUpdate");
//	}
//
//	void OnDestroy()
//	{
//		QuickPrint("DoSomething OnDestroy");
//	}
//
//	void operator()(ecs::velocity& v, ecs::color& c) const
//	{
//		QuickPrint(std::string{ "Original value: " } + std::to_string(v.x));
//		v.x = Math::random(0.f, 100.f);
//		QuickPrint(std::string{ "New value: " } + std::to_string(v.x));
//	}
//};