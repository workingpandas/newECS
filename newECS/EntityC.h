#pragma once
#include "pch.h"
#include "ECS_Settings.h"
#include "ECS_Utilities.h"

struct EntityC
{
	constexpr static auto info_v = ecs::ComponentInfo{
		.m_pName = "entity"
	};

	ecs::EntityID m_EntityID = ecs::ERROR_ENTITY_ID;
};
