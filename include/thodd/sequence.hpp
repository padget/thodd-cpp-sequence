#ifndef __THODD_SEQUENCE_HPP__
#  define  __THODD_SEQUENCE_HPP__ 

#  include <type_traits>
#  include <algorithm>

namespace
thodd
{
    template<
        typename type_t,
        type_t ... idxs_c>
    struct sequence {};   
}


namespace 
thodd::sequence_detail
{
    constexpr auto
    at_c(    
        auto __index, 
        auto __item)
    {
        return __item;
    }


    constexpr auto
    at_c(
        auto __index, 
        auto __item,
        auto __next, 
        auto ... __items)
    {
        return 
        __index == 0 ? 
        __item : 
        at_c(
            __index - 1, 
            __next, 
            __items...); 
    }


    template<
        typename type_t,
        type_t min_c, 
        type_t max_c, 
        type_t ... nexts_c>
    constexpr sequence<type_t, max_c, nexts_c...> 
    make_sequence(
        std::integral_constant<type_t, min_c>,
        std::integral_constant<type_t, max_c>,
        sequence<type_t, max_c, nexts_c...>,
        auto __step)
    {
        return {};
    }


    template<
        typename type_t,
        type_t min_c, 
        type_t max_c, 
        type_t index_c,
        type_t ... nexts_c>
    constexpr auto 
    make_sequence(
        std::integral_constant<type_t, min_c>, 
        std::integral_constant<type_t, max_c>, 
        sequence<type_t, index_c, nexts_c...>, 
        auto __step)
    {
        return 
        make_sequence(
            std::integral_constant<type_t, min_c>{}, 
            std::integral_constant<type_t, max_c>{}, 
            sequence<type_t, __step(index_c), index_c, nexts_c...>{}, 
            __step);
    }


    template<
        typename type_t,
        type_t ... indexes_c>
    constexpr sequence<type_t, (sizeof(indexes_c) - 1 - indexes_c)...>
    simple_reverse_sequence(
        sequence<type_t, indexes_c...>)
    {
        return {} ;
    }
}


namespace 
thodd
{
    template<
        typename type_t,
        type_t min_c, 
        type_t max_c>
    constexpr auto 
    make_sequence(
        std::integral_constant<type_t, min_c>, 
        std::integral_constant<type_t, max_c>,
        auto __step)
    {
        static_assert(
            min_c <= max_c,
            "(min_c <= max_c) not" 
            "respected for make_sequence");

        return 
        sequence_detail::
        make_sequence(
            std::integral_constant<type_t, min_c>{}, 
            std::integral_constant<type_t, max_c>{},
            sequence<type_t, min_c>{}, 
            __step) ;
    }


    template<
        typename type_t,
        type_t min_c, 
        type_t max_c>
    constexpr auto 
    make_sequence(
        std::integral_constant<type_t, min_c>, 
        std::integral_constant<type_t, max_c>)
    {
        return 
        sequence_detail::
        make_sequence(
            std::integral_constant<type_t, min_c>{}, 
            std::integral_constant<type_t, max_c>{},
            sequence<type_t, min_c>{}, 
            [] (auto __item) 
            { return __item + 1 ; }) ;
    }


    template<
        typename type_t, 
        type_t max_c>
    constexpr auto 
    make_sequence(
        std::integral_constant<type_t, max_c>,
        auto __step)
    {
        return 
        make_sequence(
            std::integral_constant<type_t, 0>{}, 
            std::integral_constant<type_t, max_c>{}, 
            __step) ;
    }


    template<
        typename type_t,
        type_t max_c>
    constexpr auto 
    make_sequence(
        std::integral_constant<type_t, max_c>)
    {
        return 
        make_sequence(
            std::integral_constant<type_t, 0>{}, 
            std::integral_constant<type_t, max_c>{}, 
            [] (auto __item) 
            { return __item + 1; }) ;
    }

    
    template<
        typename type_t, 
        type_t min_c,
        type_t max_c>
    using make_sequence_t = 
        decltype(
            make_sequence(
                std::integral_constant<type_t, min_c>{}, 
                std::integral_constant<type_t, max_c>{})) ;

    template<
        typename type_t,
        type_t ... indexes_c, 
        type_t ... items_c>
    constexpr sequence<type_t, sequence_detail::at_c(sizeof(indexes_c) - 1 - indexes_c, items_c...)...>
    reverse_sequence(
        sequence<type_t, items_c...>, 
        sequence<type_t, indexes_c...>)
    {
        return {} ;
    }


    template<
        typename type_t,
        type_t ... indexes_c>
    constexpr auto 
    reverse_sequence(
        sequence<type_t, indexes_c...>)
    {
        return 
        reverse_sequence(
            sequence<type_t, indexes_c...>{}, 
            sequence_detail::simple_reverse_sequence(
                make_sequence(
                    std::integral_constant<type_t, sizeof...(indexes_c) - 1>{}))) ;
    }


    template<
        typename type_t, 
        type_t min_c,
        type_t max_c>
    using make_rsequence_t = 
        decltype(
            reverse_sequence(
                make_sequence(
                    std::integral_constant<type_t, min_c>{}, 
                    std::integral_constant<type_t, max_c>{}))) ;
}

#endif