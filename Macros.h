#pragma once
#include<type_traits>
#include<string>
#include<utility>
#include<exception>
#include<cmath>
#define _NODISCARD [[nodiscard]]

#define _PANAGIOTIS_BEGIN namespace panagiotis{

#define _CONSTEXPR20 constexpr

#define _PANAGIOTIS_END }


_PANAGIOTIS_BEGIN
template<typename _Ty>

inline constexpr bool is_decimal_v = std::disjunction_v<std::is_same<_Ty, float>, std::is_same<_Ty, double>, std::is_same<_Ty, long double>>;

template<typename _Ty>
struct is_decimal :std::bool_constant<is_decimal_v<_Ty>> {};//tag dispatching must support it

 template <class _Ty>
constexpr bool is_integer_v = std::_Is_any_of_v<_Ty, bool, char, signed char, unsigned char, wchar_t,
#ifdef __cpp_char8_t
    char8_t,
#endif // defined(__cpp_char8_t)
    char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;

 template <class _Ty>
struct is_integer : std::bool_constant<is_integer_v<_Ty>> {};

template<bool condition1,bool condition2>
struct MyStruct;


template <>
struct MyStruct<true,true> {
private:
    template<std::size_t x, std::size_t  n>
    struct Power {
 	  inline static constexpr std::size_t value = x * Power<x, n-1>::value;
    };
    template<std::size_t x>
    struct Power<x, 1> {
 	  inline static constexpr std::size_t value = x;
    };
public:
 
 template<std::size_t x, std::size_t n>
 static constexpr std::size_t Power_v = Power<x, n>::value;
};

// Specialization for false
template <>
struct MyStruct<false,true> {
private:
    template<long long x, std::size_t  n>
    struct Power {
        inline static constexpr long long value = x * Power<x, n - 1>::value;
    };
    template<std::size_t x>
    struct Power<x, 1> {
        inline static constexpr long long  value = x;
    };
public:

    template<long long x, std::size_t n>
    static constexpr long long Power_v = Power<x, n>::value;
};
template <>
struct MyStruct<true,false> {
private:
    template<std::size_t x,long long  n>
    struct Power {
        inline static constexpr double value =  (x * Power<x, n - 1>::value);
    };
    template<std::size_t x>
    struct Power<x, 1> {
        inline static constexpr double  value =x;
    };
public:

    template<std::size_t x, long long n>
    static constexpr double Power_v =1.0/ Power<x, -n>::value;
};


template <>
struct MyStruct<false, false> {
private:
    template<long long x, long long  n>
    struct Power {
        inline static constexpr double value =(x * Power<x, n - 1>::value);
    };
    template<long long x>
    struct Power<x, 1> {
        inline static constexpr double  value = x;
    };
public:
    template<long long x, long long n>
    static constexpr double Power_v =1.0/Power<x, -n>::value;
};







// Custom exception class
class _INVALID_INPUT : public std::exception {
private:
    std::string message;
public:
    explicit _INVALID_INPUT(std::string msg) : message(std::move(msg)) {}

    // Override the what() function
    const char* what() const noexcept override {
        return message.c_str();
    }
};





_PANAGIOTIS_END
