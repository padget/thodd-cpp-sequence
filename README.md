# thodd-cpp-sequence

This header-only library provide a powerfull replacement of std::integral_sequence.
You can choose the min and max and the step between two sequential values, and finally, 
reverse the sequence.

This library expose these functions : 

```c++
template<typename type_t, type_t min_c, type_t max_c>
constexpr sequence<type_t, max_c, nexts_c..., min_c> 
make_sequence(
    std::integral_constant<type_t, min_c>, 
    std::integral_constant<type_t, max_c>,
    auto __step) ;

template<typename type_t, type_t min_c, type_t max_c>
constexpr sequence<type_t, max_c, nexts_c..., min_c> 
make_sequence(
    igral<type_t, min_c>, 
    igral<type_t, max_c>) ;

template<typename type_t, type_t max_c>
constexpr sequence<type_t, max_c, nexts_c..., min_c> 
make_sequence(
    std::integral_constant<type_t, max_c>,
    auto __step) ;

template<typename type_t, type_t max_c>
constexpr sequence<type_t, max_c, nexts_c..., min_c> 
make_sequence(
    std::integral_constant<type_t, max_c>) ;

template<typename type_t, type_t ... indexes_c>
constexpr sequence<type_t, min_c, nexts_c..., max_c>
reverse_sequence(
    sequence<type_t, indexes_c...>) ;

```

and also these two types :

```c++
template<typename type_t, type_t min_c, type_t max_c>
using make_sequence_t = 
    decltype(
        make_sequence(
            std::integral_constant<type_t, min_c>{}, 
            std::integral_constant<type_t, max_c>{})) ;

template<typename type_t, type_t min_c, type_t max_c>
using make_rsequence_t = 
    decltype(
        reverse_sequence(
            make_sequence(
                std::integral_constant<type_t, min_c>{}, 
                std::integral_constant<type_t, max_c>{}))) ;

```
