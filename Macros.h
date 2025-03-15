#pragma once
#include<type_traits>
#include<string>
#include<utility>
#include<exception>
#include<cmath>
#include<concepts>
#define _NODISCARD [[nodiscard]]

#define _PANAGIOTIS_BEGIN namespace panagiotis{


#define _CONSTEXPR constexpr 

#define _PANAGIOTIS_END }


_PANAGIOTIS_BEGIN
//helper type traits 
//BEGIN
template<typename _Ty>

inline _CONSTEXPR bool Is_Decimal_v = std::disjunction_v<std::is_same<_Ty, float>, std::is_same<_Ty, double>, std::is_same<_Ty, long double>>;

template<typename _Ty>
struct Is_Decimal :std::bool_constant<Is_Decimal_v<_Ty>> {};//tag dispatching must support it

 template <class _Ty>
 _CONSTEXPR bool Is_Integer_v = std::_Is_any_of_v<_Ty, bool, char, signed char, unsigned char, wchar_t,
#ifdef __cpp_char8_t
    char8_t,
#endif // defined(__cpp_char8_t)
    char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;

template <class _Ty>
struct Is_Integer : std::bool_constant<Is_Integer_v<_Ty>> {};

//END 
//HELPER STRUCT IN ORDER TO HELP WITH THE POWER OF INTEGERS FUNC 
//COULDN'T FIND A BETTER WAY TO IMPLEMENT IT 
//BEGIN
template<bool condition1,bool condition2>
struct My_Struct;


template <>
struct My_Struct<true,true> {
private:
    template<std::size_t x, std::size_t  n>
    struct Power {
 	  inline static _CONSTEXPR std::size_t value = x * Power<x, n-1>::value;
    };
    template<std::size_t x>
    struct Power<x, 1> {
 	  inline static _CONSTEXPR std::size_t value = x;
    };
public:
 
 template<std::size_t x, std::size_t n>
 static _CONSTEXPR std::size_t Power_v = Power<x, n>::value;
};

// Specialization for false
template <>
struct My_Struct<false,true> {
private:
    template<long long x, std::size_t  n>
    struct Power {
        inline static _CONSTEXPR long long value = x * Power<x, n - 1>::value;
    };
    template<std::size_t x>
    struct Power<x, 1> {
        inline static _CONSTEXPR long long  value = x;
    };
public:

    template<long long x, std::size_t n>
    static _CONSTEXPR long long Power_v = Power<x, n>::value;
};
template <>
struct My_Struct<true,false> {
private:
    template<std::size_t x,long long  n>
    struct Power {
        inline static _CONSTEXPR double value =  (x * Power<x, n - 1>::value);
    };
    template<std::size_t x>
    struct Power<x, 1> {
        inline static _CONSTEXPR double  value =x;
    };
public:

    template<std::size_t x, long long n>
    static _CONSTEXPR double Power_v =1.0/ Power<x, -n>::value;
};


template <>
struct My_Struct<false, false> {
private:
    template<long long x, long long  n>
    struct Power {
        inline static _CONSTEXPR double value =(x * Power<x, n - 1>::value);
    };
    template<long long x>
    struct Power<x, 1> {
        inline static _CONSTEXPR double  value = x;
    };
public:
    template<long long x, long long n>
    static _CONSTEXPR double Power_v =1.0/Power<x, -n>::value;
};
//END




// Custom exception class
class _INVALID_INPUT : public std::exception {//custom exception
private:
    std::string message;
public:
    explicit _INVALID_INPUT(std::string msg) : message(std::move(msg)) {}

    // Override the what() function
    const char* what() const noexcept override {
        return message.c_str();
    }
};

//begin
template<typename _Ty>
concept Less_Than_Comparable = requires(_Ty a, _Ty b) {
    { a < b }noexcept -> std::convertible_to<bool>;
};
template<typename _Ty>
concept Greater_Than_Comparable = requires(_Ty a, _Ty b) {
    { a > b } noexcept-> std::convertible_to<bool>;
};
template<typename _Ty>
concept Comparable = requires(_Ty a, _Ty b) {
    { a == b }noexcept-> std::convertible_to<bool>;
};

template<typename _Ty>
concept Can_Be_Sorted = requires(_Ty a, _Ty b) {
    requires(Comparable< _Ty>);
    requires(Greater_Than_Comparable< _Ty>);
    requires(Less_Than_Comparable< _Ty>);
};
//end





_PANAGIOTIS_END
