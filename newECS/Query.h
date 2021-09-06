#pragma once
#include "pch.h"
#include "ECS_Settings.h"
namespace ecs
{
	struct Query
	{
	public:
		template<typename T_TUPLE_QUERY>
		void AddQueryFromTuple();

		bool Compare(const Bits& archetypeBits);

		template<typename... T_ARGS>
		void AddFromComponent(Bits& bit);

		Bits m_Must;
		Bits m_NoneOf;
		Bits m_OneOf;
	
	private:
		// 'Iterate' the tuple; set the correct bits with the correct CID
		template<typename... T_QUERIES>
		void AddQueryFromTuple(std::tuple<T_QUERIES...>* tuple);
	};

}
#include "Query.hpp"