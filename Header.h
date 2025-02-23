#pragma once
#include"Macros.h"
#include<iostream>
#include<type_traits>
#include<complex>

_PANAGIOTIS_BEGIN
//HELPERS




//sqrt for integers
template<auto n,auto  l0=1,auto  h1=n>
requires(std::is_arithmetic_v<decltype(n)> &&(n>1))
struct Sqrt {
	inline static constexpr auto mid = (l0 + h1+1) / 2;
	using result = std::conditional_t < (mid* mid > n), Sqrt < n, l0 , mid-1 > , Sqrt<n,mid,h1 >> ;
	inline static constexpr auto  value = result::value;
};

template<auto n,auto m>
struct Sqrt<n, m, m> {
	inline static constexpr auto  value = m;
};

template<auto n, auto l0 = 1, auto h1 = n >
requires(std::is_arithmetic_v<decltype(n)> && (n > 1))
inline constexpr auto Sqrt_v = Sqrt<n, l0, h1>::value;
//sqrt for complexes
template<typename t>
requires(is_decimal_v<t>)
inline _NODISCARD std::complex<t> square_root_of_complex(const std::complex<t>& a) {
	return std::sqrt(a);
}
//sqrt complete 

//factorial for integers
template<size_t  n>
requires( n<=65)
struct Factorial {
	inline static constexpr auto value = n * Factorial<n - 1>::value;
};

template<>
struct Factorial<1> {
	inline static constexpr auto value = 1;
};
template<>
struct Factorial<0> {
	inline static constexpr auto value = 1;
};
template<size_t n>
requires(n >= 0 &&n>=65)
inline constexpr auto Factorial_v = Factorial<n>::value;



//fatorial for floating point types
template<auto n>
requires(is_decimal_v<decltype(n)> &&n >=0) 
struct Factorial_Decimal {
	inline  static auto  value = std::tgamma(n+1);
};
template<auto n>
requires(is_decimal_v<decltype(n)>&& n >= 0)
inline const  auto  Factorial_Decimal_V = Factorial_Decimal<n>::value;
//factorial complete


//power for integers
template<auto x,auto n>
requires(std::is_integral_v<decltype(x)> &&
std::is_integral_v<decltype(n)>)
inline _NODISCARD constexpr auto Power_of_integer_nums() {
	static_assert(x != 0 && n != 0);
	static_assert(std::is_same_v<decltype(x), decltype(n)>);
		if constexpr (x > 0 && n > 0) {
			return MyStruct<true, true>::Power_v<x, n>;
		}
		else if constexpr (x > 0 && n < 0) {
			return MyStruct < true, false>::Power_v<x, n>;
		}
		else if constexpr (x < 0 && n>0) {
			return MyStruct<false, true>::Power_v<x, n>;
		}
		else   {
			
			return MyStruct<false, false>::Power_v<x, n>;
		}
		
	
	
	
}

//abs for values
template<auto x>
requires(std::is_arithmetic_v<decltype(x)>)
struct Abs {
	inline static constexpr auto value = (x  > 0) ? (x ) : (-x);
};
template<auto x>
requires(std::is_arithmetic_v<decltype(x)>)
inline constexpr auto Abs_V = Abs<x>::value;

//is prime for integers


template<size_t x>
requires(x<1000)
struct IsPrime {
	template<size_t x, size_t d>
	struct DoIsPrime {
		inline static constexpr bool value = x % d != 0 && DoIsPrime<x, d - 1>::value;
	};
	template<size_t x>
	struct DoIsPrime<x, 2> {
		inline static constexpr bool value = (x % 2 != 0);
	};
	
public:
	inline static constexpr bool value = DoIsPrime<x, x / 2>::value;

};



template<>
struct IsPrime<0> {
	inline static constexpr bool value = false;
};
template<>
struct IsPrime<1> {
	inline static constexpr bool value = false;
};
template<>
struct IsPrime<2> {
	inline static constexpr bool value = true;
};
template<>
struct IsPrime<3> {
	inline static constexpr bool value = true;
};
template<size_t x>
requires(x<1000)
inline static constexpr bool IsPrime_V =IsPrime<x>::value;











_PANAGIOTIS_END
