#pragma once
#include "ECS_Settings.h"
#include "ECS_Utilities.h"
namespace ecs
{
	// Example component
	struct velocity
	{
		// All components need to have an info_v
		// Input name or GUID if you want
		// ComponentMgr will overwrite them if they are leave blank
		constexpr static auto info_v = ComponentInfo{
			.m_pName = "velocity"
		};

		// Data members
		float x = 1, y = 2, z = 3;
	};

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
