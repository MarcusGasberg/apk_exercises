#pragma once

struct NullType {};

template<typename L, typename R>
struct TypeList
{
    typedef L First;
    typedef R Rest;
};


template<typename T0, typename T1>
struct IsSame 
{
    static constexpr bool value = false;
};


template<typename T>
struct IsSame<T, T>
{
    static constexpr bool value = true;
};


template<typename TList, typename T>
struct Contains
{
    static constexpr bool value = IsSame<typename TList::First, T>::value ? true : Contains<typename TList::Rest, T>::value;
};

template<typename T>
struct Contains<NullType, T>
{
    static constexpr bool value = false;
};

template<typename TList, size_t N, size_t NStart = 0>
struct AtIndex
{
    using type = typename AtIndex<typename TList::Rest, N, NStart + 1>::type;
};

template<size_t N, size_t NStart>
struct AtIndex<NullType, N, NStart>
{
    using type = decltype(NullType());
};

template<typename TList, size_t N>
struct AtIndex<TList, N, N>
{
    using type = decltype(TList::First());
};


template<typename TList>
struct PrintIT
{
    PrintIT() { std::cout << typeid(TList::First).name() << std::endl; PrintIT<typename TList::Rest>(); }
};

template<>
struct PrintIT<NullType>
{
    PrintIT() = default;
};