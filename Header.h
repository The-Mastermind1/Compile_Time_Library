#pragma once
#include"Macros.h"
#include<iostream>
#include<type_traits>
#include<complex>
#include<array>
#include<vector>
#include<iterator>
#include<string_view>
_PANAGIOTIS_BEGIN






//sqrt for integers
template<std::size_t n,std::size_t  l0=1,auto  h1=n>
requires(n>1)
struct Sqrt {
	inline static _CONSTEXPR auto mid = (l0 + h1+1) / 2;
	using result = std::conditional_t < (mid* mid > n), Sqrt < n, l0 , mid-1 > , Sqrt<n,mid,h1 >> ;
	inline static _CONSTEXPR std::size_t  value = result::value;
};

template<auto n,auto m>
struct Sqrt<n, m, m> {
	inline static _CONSTEXPR std::size_t  value = m;
};

template<std::size_t n, std::size_t l0 = 1, std::size_t h1 = n >
requires(n > 1)
inline _CONSTEXPR auto Sqrt_v = Sqrt<n, l0, h1>::value;
//sqrt for complexes
template<typename t>
requires(Is_Decimal_v<t>)
inline _NODISCARD std::complex<t> square_root_of_complex(const std::complex<t>& a) {
	return std::sqrt(a);
}
//sqrt complete 






//fatorial for floating point types
template<auto n>
requires(Is_Decimal_v<decltype(n)> &&n >=0)
struct Factorial_Decimal {
	inline  static auto  value = std::tgamma(n+1);
};
template<auto n>
requires(Is_Decimal_v<decltype(n)>&& n >= 0)
inline const  auto  Factorial_Decimal_v = Factorial_Decimal<n>::value;
//factorial complete


//power for integers
template<auto x,auto n>
requires(std::is_integral_v<decltype(x)> &&
std::is_integral_v<decltype(n)>)
inline _NODISCARD _CONSTEXPR auto  Power_of_integer_nums() {
	    static_assert(x != 0 && n!=0);
	    static_assert(std::is_same_v<decltype(x), decltype(n)>);
	   
		if _CONSTEXPR(x > 0 && n > 0) {
			return My_Struct<true, true>::Power_v<x, n>;
		}
		else if _CONSTEXPR(x > 0 && n < 0) {
			return My_Struct < true, false>::Power_v<x, n>;
		}
		else if _CONSTEXPR(x < 0 && n>0) {
			return My_Struct<false, true>::Power_v<x, n>;
		}
		else if _CONSTEXPR(x<0 && n<0)  {
			
			return My_Struct<false, false>::Power_v<x, n>;
		}
		
	
	
	
}

//abs for values
template<auto x>
requires(std::is_arithmetic_v<decltype(x)>)
struct Abs {
	inline static _CONSTEXPR auto value = (x  > 0) ? (x ) : (-x);
};
template<auto x>
requires(std::is_arithmetic_v<decltype(x)>)
inline _CONSTEXPR auto Abs_v = Abs<x>::value;

//is prime for integers


template<std::size_t x>
requires(x<1000)
struct Is_Prime {
private:
	template<std::size_t x, std::size_t d>
	struct Do_Is_Prime {
		inline static _CONSTEXPR bool value = x % d != 0 && Do_Is_Prime<x, d - 1>::value;
	};
	template<std::size_t x>
	struct Do_Is_Prime<x, 2> {
		inline static _CONSTEXPR bool value = (x % 2 != 0);
	};
	
public:
	inline static _CONSTEXPR bool value = Do_Is_Prime<x, x / 2>::value;

};



template<>
struct Is_Prime<0> {
	inline static _CONSTEXPR bool value = false;
};
template<>
struct Is_Prime<1> {
	inline static _CONSTEXPR bool value = false;
};
template<>
struct Is_Prime<2> {
	inline static _CONSTEXPR bool value = true;
};
template<>
struct Is_Prime<3> {
	inline static _CONSTEXPR bool value = true;
};
template<std::size_t x>
requires(x<1000)
inline static _CONSTEXPR bool Is_Prime_v =Is_Prime<x>::value;

////enforse same
template<auto first,auto second,auto...rest>
requires(std::is_arithmetic_v<decltype(first)>)
struct Max {
	static_assert(std::conjunction_v<std::is_same<decltype(first), decltype(second)>, std::is_same<decltype(second), decltype(rest)>...>);
	inline static _CONSTEXPR auto value =(first > second)?(Max<first, rest...>::value):(Max<second, rest...>::value);
};

////enforse same
//MAX
template <auto first,auto second>
requires(std::is_arithmetic_v<decltype(first)>)
struct Max<first,second> {
	static_assert(std::is_same_v<decltype(first), decltype(second)>);
	inline static _CONSTEXPR auto value =(first>second)?first:second;
};

template<auto first, auto second, auto...rest>
requires(std::is_arithmetic_v<decltype(first)>)
struct Min {
	static_assert(std::conjunction_v<std::is_same<decltype(first), decltype(second)>, std::is_same<decltype(second), decltype(rest)>...>);
	inline static _CONSTEXPR auto value = (first > second) ? (Min<second, rest...>::value) : (Min<first, rest...>::value);
};

////enforse same
//Min
template <auto first, auto second>
requires(std::is_arithmetic_v<decltype(first)>)
struct Min<first, second> {
	
	static_assert(std::is_same_v<decltype(first), decltype(second)>);
	inline static _CONSTEXPR auto value = (first > second) ? second :first;
	
};

//class Array_Algorithms {
//private:
//	//dot product,esoteriko gin gia array 
//	template<typename t, std::size_t n, std::size_t n2>
//	struct dotproduct {
//		inline static t result(std::array<t, n>::const_iterator it1,
//			std::array<t, n>::const_iterator it2) {
//			
//			return *it1 * *it2 + dotproduct<t,n,n2-1>::result(it1+1,it2+1);
//		}
//	};
//	
//	template<typename t, std::size_t n>
//	struct dotproduct<t,n,0> {
//		inline static t result(std::array<t, n>::const_iterator it1,
//			std::array<t, n>::const_iterator it2) {
//			return t{};
//		}
//	};
//	
//	
//public:
//	template<typename t, std::size_t n>
//	requires(n>0 &&is_decimal_v<t> || is_integer_v<t>)
//	std::array<t,n> dodotproduct(const std::array<t, n>& x, const std::array<t, n>& y) {
//		return dotproduct<t, n, n>::result(x.cbegin(), y.cbegin());
//	}
//	
//
//	
//};

template<auto first,auto second,typename t=double>
requires(Is_Decimal_v<t> &&std::is_arithmetic_v<decltype(first)> &&
std::is_arithmetic_v<decltype(second)>)
inline _NODISCARD _CONSTEXPR bool Is_Equal(t epsilon=static_cast<t>(1.0E-8)) {
	return Abs_v<first-second><epsilon;
}

template<auto x,auto n>
requires(std::is_integral_v<decltype(x)>&& std::is_integral_v<decltype(n)> 
&& std::is_same_v<decltype(x), decltype(n)> && n>=0)
struct Terms {
	inline static _CONSTEXPR double value = (1.0*Power_of_integer_nums<x,n>()/ Factorial<n>())+Terms<x,n-1>::value;//x^n/n


};

template<auto x>
requires(std::is_integral_v<decltype(x)>)
struct Terms<x,0> {
	
	inline static _CONSTEXPR double value = 1.0;
};
template<auto x,auto iterations=20>
requires(std::is_integral_v<decltype(x)> && 
std::is_same_v<decltype(x),decltype(iterations)>)//iterations change with your own risk
inline _CONSTEXPR double Exp() {
	return Terms<x, iterations>::value;
}


template<auto n>
requires(n>=0 && std::is_arithmetic_v<decltype(n)>)
struct Finobacci {
	inline static _CONSTEXPR size_t value = Finobacci<n - 1>::value + Finobacci<n - 2>::value;
};
template<>
struct Finobacci<1> {
	inline static _CONSTEXPR size_t value = 1;
};
template<>
struct Finobacci<0> {
	inline static _CONSTEXPR size_t value = 0;
};
template<auto n>
requires(n >= 0 && std::is_arithmetic_v<decltype(n)>)
inline _CONSTEXPR size_t Finobacci_v= Finobacci<n>::value;

inline _CONSTEXPR std::size_t Str_Len(const char* str) {//works why ??
	return (*str == '\0') ? 0 : 1 + Str_Len(str + 1);
}


class Array_Algorithms {
public:
	template<typename t,std::size_t n,typename _Ty>
	requires(Is_Decimal_v<t>||Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static t dotproduct( std::array<t,n>::const_iterator it1,
		 std::array<t,n>::const_iterator it2,_Ty val){//explicitly specify the template args otherwise the compiler cant deduce them
		static_assert(n > 0, "array_size must be >0");
	   
		for (size_t i = 0; i < n; i++) {//for loops are allowed for constexpr
			val += *it1 + *it2;
			it1++;
			it2++;
		}
		return val;
		
	}
	template<typename t, std::size_t n>
	requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static std::array<t,n> doaddition(std::array<t, n>::const_iterator it1,
		 std::array<t, n>::const_iterator it2) {//explicitly specify the template args otherwise the compiler cant deduce them
		static_assert(n > 0, "array_size must be >0");
		std::array<t, n> result;
		for (size_t i = 0; i < n; i++) {//for loops are allowed for constexpr
			result[i] = *it1 + *it2;
			it1++;
			it2++;
		}
		return result;

	}
	template<typename t, std::size_t n>
	requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static std::array<t, n> dosubtraction( std::array<t, n>::const_iterator it1,
		 std::array<t, n>::const_iterator it2) {//explicitly specify the template args otherwise the compiler cant deduce them
		static_assert(n > 0, "array_size must be >0");
		std::array<t, n> result;
		for (size_t i = 0; i < n; i++) {
		
			result[i] = *it1 - *it2;
			
			it1++;
			it2++;
		}
		return result;

	}
	template<typename t, std::size_t n>
	requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD static std::array<t, n> print1D_array(const std::array<t, n>& arr1){
		static_assert(n > 0, "array_size must be >0");
		std::cout << "Array Elements:\n";
		for (size_t i = 0; i < n; i++) {

			std::cout << arr1[i] << '\n';
		}
		return;

	}
};

template <typename T>
_CONSTEXPR std::string_view Type_Name() {
#ifdef __clang__
	return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
	return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
	return __FUNCSIG__;
#else
	return "Unknown Compiler";
#endif
}

template<std::size_t N>
inline _NODISCARD _CONSTEXPR std::array<char, N> Make_Reversed_String(const char(&str)[N]) {
	
	std::array<char, N> reversed = {}; // Create an array of fixed size
	
	for (std::size_t i = 0; i < N - 1; ++i) {
		reversed[i] = str[N - 2 - i];  // Reverse the string
	}
	reversed[N - 1] = '\0';  // Null-terminate
	
	return reversed;
}
template<std::size_t N>
requires(N<=65)
inline _NODISCARD _CONSTEXPR std::size_t Factorial() {
	if constexpr (N == 0) {
		return 1;
	}
	else if constexpr (N == 1) {
		return 1;

	}
	else {
		std::size_t val = 1;
		for (std::size_t i = 1; i <= N;i++) {
			
			val = val * i;
		}
		return val;
	}
}

inline _NODISCARD _CONSTEXPR  std::size_t Parse_Integer(const char* str, std::size_t value = 0) {//the passed str must contain only digits  
	return (*str >= '0' && *str <= '9') ? Parse_Integer(str + 1, value *(std::size_t)10 +(std::size_t)(*str - '0')) : value;
	
}

template<typename t>
struct Dimensions {
	inline static _CONSTEXPR std::size_t value =0;
};
template<typename t,std::size_t n>
struct Dimensions<t[n]> {
	inline static _CONSTEXPR std::size_t value = 1+ Dimensions<t>::value;
};
template<typename t>
struct Dimensions<t[]> {
	inline static _CONSTEXPR std::size_t value = 1+ Dimensions<t>::value;
};

template<typename t>
inline static _CONSTEXPR std::size_t Dimensions_v = Dimensions<t>::value;





_PANAGIOTIS_END
