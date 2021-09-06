#pragma once
#include "ECS_Settings.h"
#include "ECS_Utilities.h"
namespace ecs
{
	struct velocity
	{
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "velocity"
		};

		float x = 1, y = 2, z = 3;
	};

	struct velocity1
	{
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "velocity1"
		};
	};

	//struct velocity2
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity2>;
	//};

	//struct velocity3
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity3>;
	//};

	//struct velocity4
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity4>;
	//};

	//struct velocity5
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity5>;
	//};

	//struct velocity6
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity6>;
	//};

	//struct velocity7
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity7>;
	//};

	//struct velocity8
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity8>;
	//};

	//struct velocity9
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity9>;
	//};

	//struct velocity10
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity10>;
	//};

	//struct velocity11
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity11>;
	//};

	//struct velocity12
	//{
	//	constexpr static auto info_v = ecs::GenerateInfo<velocity12>;
	//};
	//
	struct position
	{
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "position"
		};
		float x = 0.0f, y = 100.0f;
	};

	struct color
	{
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "color"
		};
		float r = 1.0f, g = 0.0f, b = 1.0f;

	};

	struct rendering
	{
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "rendering"
		};
		bool render = true;
	};
}
