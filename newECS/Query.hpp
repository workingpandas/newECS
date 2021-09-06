#pragma once
#include "Query.h"
#include "ECS_Settings.h"
#include "xCoreFunctions.h"
namespace ecs
{
	constexpr bool failed = false;
	template <typename T_TUPLE_QUERY>
	void Query::AddQueryFromTuple()
	{
		AddQueryFromTuple(xCore::null_tuple_v<T_TUPLE_QUERY>);
	}

	template <typename ... T_QUERIES>
	void Query::AddQueryFromTuple(std::tuple<T_QUERIES...>* tuple)
	{
		(([&]<template <typename...> class T_QUERY, typename... T_COMPONENT>(T_QUERY<T_COMPONENT...>*) constexpr noexcept
		{
			// [t] is either :must<T_COMPONENT...> / none_of<T_COMPONENT...> / one_of<T_COMPONENT...>
			using t = T_QUERY<T_COMPONENT...>;

			if(std::is_same_v<t, must<T_COMPONENT...>>)
			{
				AddFromComponent<T_COMPONENT...>(m_Must);
			}
			else if (std::is_same_v<t, none_of<T_COMPONENT...>>)
			{
				AddFromComponent<T_COMPONENT...>(m_NoneOf);
			}
			else if (std::is_same_v<t, one_of<T_COMPONENT...>>)
			{
				AddFromComponent<T_COMPONENT...>(m_OneOf);
			}
			else
			{
				// TODO: ADD FAIL SWITCH
				// "Query::AddQueryFromTuple / UNKNOWN QUERY!"
			}
		}(xCore::null_tuple_v<T_QUERIES>))
		,...
		);
		
	}

	template <typename ... T_ARGS>
	void Query::AddFromComponent(Bits& bit)
	{
		// Ensure all components input has been registered
		((assert(ComponentInfo_v<T_ARGS>.m_CID != INVALID_CID)), ...);
		
		// Set bits
		((bit.set(ComponentInfo_v<T_ARGS>.m_CID)), ...);
	}

	inline bool Query::Compare(const Bits& archetypeBits)
	{
		std::uint64_t componentBool = 0;
		std::uint64_t oneOfBool = 0;
		
		for(size_t i = 0; i < MAX_COMPONENT; ++i)
		{
			// Contain none of; return false
			if(m_NoneOf[i] & archetypeBits[i])	
				return false;
			// Does not contain must; return false
			if ((m_Must[i] & archetypeBits[i]) != m_Must[i])
				return false;

			componentBool |= m_OneOf[i] & archetypeBits[i];
			oneOfBool |= m_OneOf[i];
		}
		// componentBool | oneOfBool
		// 0			 | 1		= return false; component don't have OneOf
		// 1			 | 1		= return true; component have OneOf
		// 0			 | 0		= return true; query does not have OneOf
		// 1			 | 0		= ERROR; does not make sense
		assert(!(!oneOfBool && componentBool));

		return !oneOfBool || componentBool;
	}
}
