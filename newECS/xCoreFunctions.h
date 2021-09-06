#pragma once

// Functions taken from xCore
namespace xCore
{
    namespace details
    {
        template <typename...>
        struct count_of;

        template< typename F >
        struct count_of<F>
        {
            static constexpr auto value = 0ull;
        };

        template <typename F, typename S, typename... T>
        struct count_of<F, S, T...>
        {
            static constexpr auto value = std::is_same<F, S>::value + count_of<F, T...>::value;
        };
    }

    template< typename T_TYPE, typename...T_ARGS >
    static constexpr auto count_of_v = details::count_of< T_TYPE, T_ARGS...>::value;

    //--------------------------------------------------------------------------------------------
    // Does tuple have duplicates
	//--------------------------------------------------------------------------------------------
    namespace details
    {
        template< typename T_TUPLE >
        struct tuple_has_duplicates;

        template< typename...T_ARGS >
        struct tuple_has_duplicates< std::tuple<T_ARGS...> >
        {
            constexpr static bool value = ((count_of_v<T_ARGS, T_ARGS...> > 1) || ...);
        };
    }

    template< typename T_TUPLE >
    static constexpr bool tuple_has_duplicates_v = details::tuple_has_duplicates<T_TUPLE >::value;

    //--------------------------------------------------------------------------------------------
    // Extract parameters from function
    //--------------------------------------------------------------------------------------------
	
    namespace details
    {
        template<typename T>
        struct params_to_tuple;

    	// J::*: Pointer to J's function
    	// T...: The parameters in the functions
        template<typename J, typename...T>
        struct params_to_tuple<void(J::*)(T...) const>
        {
            using type = std::tuple<std::decay_t<T>*...>;
        };
    }
	
    //------------------------------------------------------------------------------------------
    // Creates a nullptr value given a tuple
    //------------------------------------------------------------------------------------------
    template< typename T_TUPLE>
    constexpr auto null_tuple_v = static_cast<T_TUPLE*>(0);
}
