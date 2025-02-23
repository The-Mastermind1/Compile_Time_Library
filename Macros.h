#pragma once
#include<type_traits>
#include<iostream>
#define _NODISCARD [[nodiscard]]

#define _PANAGIOTIS_BEGIN namespace panagiotis{

#define _CONSTEXPR20 constexpr

#define _PANAGIOTIS_END }


_PANAGIOTIS_BEGIN
template<typename _Ty>

inline constexpr bool is_decimal_v = std::disjunction_v<std::is_same<_Ty, float>, std::is_same<_Ty, double>, std::is_same<_Ty, long double>>;

template<typename _Ty>
struct is_decimal :std::bool_constant<is_decimal_v<_Ty>> {};//tag dispatching must support it


template<bool condition1,bool condition2>
struct MyStruct;


template <>
struct MyStruct<true,true> {
private:
    template<size_t x,size_t  n>
    struct Power {
 	  inline static constexpr size_t value = x * Power<x, n-1>::value;
    };
    template<size_t x>
    struct Power<x, 1> {
 	  inline static constexpr size_t value = x;
    };
public:
 
 template<size_t x, size_t n>
 static constexpr size_t Power_v = Power<x, n>::value;
};

// Specialization for false
template <>
struct MyStruct<false,true> {
private:
    template<long long x, size_t  n>
    struct Power {
        inline static constexpr long long value = x * Power<x, n - 1>::value;
    };
    template<size_t x>
    struct Power<x, 1> {
        inline static constexpr long long  value = x;
    };
public:

    template<long long x,size_t n>
    static constexpr long long Power_v = Power<x, n>::value;
};
template <>
struct MyStruct<true,false> {
private:
    template<size_t x,long long  n>
    struct Power {
        inline static constexpr double value = 1.0 / (x * Power<x, n - 1>::value);
    };
    template<size_t x>
    struct Power<x, 1> {
        inline static constexpr double  value =x;
    };
public:

    template<size_t x, long long n>
    static constexpr double Power_v = Power<x, -n>::value;
};


template <>
struct MyStruct<false, false> {
private:
    template<long long x, long long  n>
    struct Power {
        inline static constexpr double value = 1.0 / (x * Power<x, n - 1>::value);
    };
    template<long long x>
    struct Power<x, 1> {
        inline static constexpr double  value = x;
    };
public:
    template<long long x, long long n>
    static constexpr double Power_v =-Power<x, -n>::value;
};


_PANAGIOTIS_END
