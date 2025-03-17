#pragma once
#include"Macros.h"
#include<iostream>
#include<type_traits>
#include<complex>
#include<array>
#include<vector>
#include<iterator>
#include<utility>
#include<string_view>
#include<algorithm>
_PANAGIOTIS_BEGIN

//sqrt for integers
//can be used to tell you at compile time 
//the sqrt of an unsigned integer
//uses template recursive instantiation 
template<std::size_t n, std::size_t  l0 = 1, std::size_t  h1 = n>
requires(n > 1)
struct Sqrt {
	inline static _CONSTEXPR auto mid = (l0 + h1 + 1) / 2;
	using result = std::conditional_t < (mid* mid > n), Sqrt < n, l0, mid - 1 >, Sqrt<n, mid, h1 >>;
	inline static _CONSTEXPR std::size_t  value = result::value;
};

template<std::size_t n, std::size_t m>
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
	requires(Is_Decimal_v<decltype(n)>&& n >= 0)
struct Factorial_Decimal {
	inline  static auto  value = std::tgamma(n + 1);
};
template<auto n>
requires(Is_Decimal_v<decltype(n)>&& n >= 0)
inline const  auto  Factorial_Decimal_v = Factorial_Decimal<n>::value;
//factorial complete


//power for integers
//can be used at compile time 
//this func only works for integers
//and gives you the result in double
//is prety accurate
template<auto x, auto n>
	requires(std::is_integral_v<decltype(x)>&&
std::is_integral_v<decltype(n)>)
inline _NODISCARD _CONSTEXPR auto  Power_of_integer_nums()noexcept {
	static_assert(x != 0 && n != 0);
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
	else if _CONSTEXPR(x < 0 && n < 0) {

		return My_Struct<false, false>::Power_v<x, n>;
	}




}

//abs for values
//can be used at compile time
template<auto x>
	requires(std::is_arithmetic_v<decltype(x)>)
struct Abs {
	inline static _CONSTEXPR auto value = (x > 0) ? (x) : (-x);
};
template<auto x>
	requires(std::is_arithmetic_v<decltype(x)>)
inline _CONSTEXPR auto Abs_v = Abs<x>::value;

//is prime for integers

//BEGIN
//simple struct that uses recursive instantiation in order to tell if 
//the number you gave is prime at compile time
template<std::size_t x>
	requires(x < 1000)
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
	requires(x < 1000)
inline static _CONSTEXPR bool Is_Prime_v = Is_Prime<x>::value;
//END

//MAX
////enforse same
template<auto first, auto second, auto...rest>
	requires(std::is_arithmetic_v<decltype(first)>)
struct Max {
	//enforse same
	static_assert(std::conjunction_v<std::is_same<decltype(first), decltype(second)>, std::is_same<decltype(second), decltype(rest)>...>, "all types provided must be the same ");
	inline static _CONSTEXPR auto value = (first > second) ? (Max<first, rest...>::value) : (Max<second, rest...>::value);
};



template <auto first, auto second>
	requires(std::is_arithmetic_v<decltype(first)>)
struct Max<first, second> {

	static_assert(std::is_same_v<decltype(first), decltype(second)>, "all types provided must be the same ");
	inline static _CONSTEXPR auto value = (first > second) ? first : second;
};

//Min
template<auto first, auto second, auto...rest>
	requires(std::is_arithmetic_v<decltype(first)>)
struct Min {
	//enforse same
	static_assert(std::conjunction_v<std::is_same<decltype(first), decltype(second)>, std::is_same<decltype(second), decltype(rest)>...>, "all types provided must be the same ");
	inline static _CONSTEXPR auto value = (first > second) ? (Min<second, rest...>::value) : (Min<first, rest...>::value);
};


template <auto first, auto second>
	requires(std::is_arithmetic_v<decltype(first)>)
struct Min<first, second> {

	static_assert(std::is_same_v<decltype(first), decltype(second)>, "all types provided must be the same ");
	inline static _CONSTEXPR auto value = (first > second) ? second : first;

};


//simple helper func to help you check if two 
//arithmetic types are equal 
template<auto first, auto second, typename t = double>
	requires(Is_Decimal_v<t>&& std::is_arithmetic_v<decltype(first)>&&
std::is_arithmetic_v<decltype(second)>)
inline _NODISCARD _CONSTEXPR bool Is_Equal(t epsilon = static_cast<t>(1.0E-8))noexcept {
	return Abs_v<first - second> < epsilon;
}

template<auto x, auto n>
	requires(std::is_integral_v<decltype(x)>&& std::is_integral_v<decltype(n)>
&& std::is_same_v<decltype(x), decltype(n)>&& n >= 0)
struct Terms {
	inline static _CONSTEXPR double value = (1.0 * Power_of_integer_nums<x, n>() / Factorial<n>()) + Terms<x, n - 1>::value;//x^n/n


};

template<auto x>
	requires(std::is_integral_v<decltype(x)>)
struct Terms<x, 0> {

	inline static _CONSTEXPR double value = 1.0;
};
template<auto x, auto iterations = 20>
	requires(std::is_integral_v<decltype(x)>&&
std::is_same_v<decltype(x), decltype(iterations)>)//iterations change with your own risk
inline _CONSTEXPR double Exp() {
	return Terms<x, iterations>::value;
}

//this struct takes a number and returns the fibonaci secuence at compile time  
//this it used template reqursive instantiation 
//BEGIN
template<size_t n>
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
inline _CONSTEXPR size_t Finobacci_v = Finobacci<n>::value;
//END

//this funct takes a string and give the length of it 
//can be used at compile time 
inline _CONSTEXPR std::size_t Str_Len(const char* str) {//works why ??
	return (*str == '\0') ? 0 : 1 + Str_Len(str + 1);
}


class Array_Algorithms {
public:
	//the struct takes from the constructors matrixes to deduce the template params 
	//to tell if the array is a matrix 
	//the types you pass as _Ty must support sizeof dont give incomplete types 
	//Begin
	template<typename _Ty, std::size_t n, std::size_t m>
	struct Is_NxN :std::false_type
	{
		static_assert(Supports_Sizeof_V<_Ty>, "incomplete types are not allowed");
		_CONSTEXPR Is_NxN(const std::array<std::array<_Ty, n>, m>& arr)noexcept {

		}
		_CONSTEXPR Is_NxN(const _Ty(&)[n][m])noexcept {

		}

	};
	template<typename _Ty, std::size_t n>
	struct Is_NxN<_Ty, n, n> : std::true_type
	{
		static_assert(Supports_Sizeof_V<_Ty>, "incomplete types are not allowed");
		_CONSTEXPR  Is_NxN(const std::array<std::array<_Ty, n>, n>&)noexcept {

		}
		_CONSTEXPR Is_NxN(const _Ty(&)[n][n])noexcept {

		}
	};
	//End

	//this func checks simply if the given array is sorted
	//can be used at compile time 
	template<typename _Ty, std::size_t N>
	requires(Can_Be_Sorted<_Ty>)
	inline static _NODISCARD _CONSTEXPR bool Is_Sorted(
		const std::array< _Ty, N>& a) {//func begin
		bool value1 = true;
		bool value2 = true;
		static_assert(N > 0,"array size should be >0");
		//check for ascending order
		for (std::size_t i = 0; i < a.size()-1; i++) {
			if (!(a[i] <= a[i + 1])) {
				value1 = false;
				break;
			}
		}
		//check for descending order
		for (std::size_t i = 0; i < a.size()-1; i++) {
			if (!(a[i] >= a[i + 1])) {
				value2 = false;
				break;
			}
		}
		if (value1 == value2)return false;
		return true;


	}//func end





	//this func takes to array and make the product between them
	//and gives an array as a result
	//can be used at compile time
	template<typename t, std::size_t n, typename _Ty>
	requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static t dotproduct(std::array<t, n>::const_iterator it1,
		std::array<t, n>::const_iterator it2, _Ty val)noexcept {//explicitly specify the template args otherwise the compiler cant deduce them
		//func end
		static_assert(n > 0, "array_size must be >0");

		for (size_t i = 0; i < n; i++) {//for loops are allowed for constexpr
			val += *it1 + *it2;
			it1++;
			it2++;
		}
		return val;

	}//func begin
	//this func takes to array and make the addition between them
	//and gives an array as a result
	//can be used at compile time
	template<typename t, std::size_t n>
		requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static std::array<t, n> doaddition(std::array<t, n>::const_iterator it1,
		std::array<t, n>::const_iterator it2)noexcept {//explicitly specify the template args otherwise the compiler cant deduce them
		//func begin
		static_assert(n > 0, "array_size must be >0");
		std::array<t, n> result;
		for (size_t i = 0; i < n; i++) {//for loops are allowed for constexpr
			result[i] = *it1 + *it2;
			it1++;
			it2++;
		}
		return result;

	}//func end
	//this func takes to array and make the substraction between them
	//and gives an array as a result
	//can be used at compile time
	template<typename t, std::size_t n>
		requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD _CONSTEXPR static std::array<t, n> dosubtraction(std::array<t, n>::const_iterator it1,
		std::array<t, n>::const_iterator it2)noexcept {//explicitly specify the template args otherwise the compiler cant deduce them
		//func begin
		static_assert(n > 0, "array_size must be >0");
		std::array<t, n> result;
		for (size_t i = 0; i < n; i++) {

			result[i] = *it1 - *it2;

			it1++;
			it2++;
		}
		return result;

	}//func end
	//simply print the contents of the array this func
	template<typename t, std::size_t n>
	requires(Is_Decimal_v<t> || Is_Integer_v<t>)
	inline _NODISCARD static std::array<t, n> print1D_array(
		const std::array<t, n>& arr1) {//func begin
		static_assert(n > 0, "array_size must be >0");
		std::cout << "Array Elements:\n";
		for (size_t i = 0; i < n; i++) {

			std::cout << arr1[i] << '\n';
		}
		return;

	}//func end
	
	//this func implements binary search in an array 
	//can be used at compile time
	//if the array you passed is not sorted in ascending order
	//  wrong results will happen 
	template<typename _Ty, std::size_t N>
	requires(Can_Be_Sorted<_Ty> &&
	std::negation_v<std::is_array<_Ty>> &&
		std::negation_v<std::is_same<_Ty,const char *>>) //requires the type to support the operations > ,< ,==
	inline static _NODISCARD _CONSTEXPR std::size_t Binary_Search(const std::array<_Ty, N>& a
		, const _Ty& target, std::size_t start = 0
		, std::size_t end = N) {//func begin
		
		static_assert(N > 0,"array size should be >0");
		std::size_t mid = start + (end - start) / 2;
		//return 5;
		if (mid >= N)return a.size();

		return (a[mid] == target) ? mid : (a[mid] > target ? Binary_Search(a, target, start, mid - 1) : Binary_Search(a, target, mid + 1, end));

	}//func end


	//this func searches an array and returns the index of the element if it is in
	//the array ,if it not is return the size of the array
	//can be used at compile time 
	template<typename _Ty,std::size_t N>
	requires(Can_Be_Sorted<_Ty>&&
	std::negation_v<std::is_array<_Ty>>&&
	std::negation_v<std::is_same<_Ty, const char*>>)
	inline static _NODISCARD _CONSTEXPR std::size_t Linear_Search(const std::array<_Ty, N>&
		a, const _Ty& target) {//func begin
		static_assert(N > 0, "array size should be >0");
		for (std::size_t i = 0; i < a.size(); i++) {
			if (a[i] == target){
				return i;
			}
		}
		return a.size();
	}//func end

	//this func simply implemments the bubble sort algorithm
	//can be used at compile time 
	template<typename _Ty,std::size_t N>
	requires(Greater_Than_Comparable<_Ty> )
	inline static _NODISCARD _CONSTEXPR std::array<_Ty,N> Bubble_Sort(std::array<_Ty, N> a)
		noexcept(noexcept(std::swap(std::declval<_Ty&>(), std::declval<_Ty&>()))) {
		//func begin
		static_assert(N > 1,"the array size should be >1,doesnt make any sence to sort an array with size 1");
		static_assert(std::is_swappable_v<_Ty>,"for elements must be able to call swap");
		for (std::size_t i = 0; i < N - 1; i++) {
			for (std::size_t j = 0; j < N - i - 1; j++) {
				if (a[j] > a[j + 1]) {
					std::swap(a[j], a[j + 1]);
				}
			}
		}
		return a;
		
	}//func end

	//this func simply reverses an array
	//can be used at compile time 
	template<typename _Ty,std::size_t N>
	inline static _NODISCARD _CONSTEXPR std::array<_Ty, N> Reverse_Array(std::array<_Ty, N>a) {
		static_assert(N > 1, "doesnt make any sence to reverse an array with 0 or 1 elements");
		 std::array<_Ty, N> res{};
		 std::size_t j = 0;
		 for (std::size_t i = a.size() - 1; i > 0; i--) {

			 res[j] = a[i];
			 j++;
		 }
		 res[j] = a[0];
		 return res;
	}

	

};

//this func gives the name of the type you passed
//can be used at compile time
template <typename T>
inline _NODISCARD std::string_view Type_Name()
{//func begin
#ifdef __clang__
	return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
	return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
	return __FUNCSIG__;
#else
	return "Unknown Compiler";
#endif
}//func end

//This func simply takes a string and reversed it 
//and simply returns and array with contents of the underlying string reversed
//can be used at compile times
template<std::size_t N>
inline _NODISCARD _CONSTEXPR std::array<char, N> Make_Reversed_String(
	const char(&str)[N])noexcept {//func begin
	static_assert(N > 1, "N should be >1");
	if constexpr (N == 2) {
		return std::array{ str[0],str[1] };
	}
	std::array<char, N> reversed = {}; // Create an array of fixed size

	for (std::size_t i = 0; i < N - 1; ++i) {
		reversed[i] = str[N - 2 - i];  // Reverse the string
	}
	reversed[N - 1] = '\0';  // Null-terminate

	return reversed;
}//func end

//this is a factorial func 
//it simply gives the factorial of an unsigned int 
//requires N<=65
//can be used at compile time
template<std::size_t N>
requires(N <= 65)
inline _NODISCARD _CONSTEXPR std::size_t Factorial() noexcept
{//func begin
	if constexpr (N == 0) {
		return 1;
	}
	else if constexpr (N == 1) {
		return 1;

	}
	else {
		std::size_t val = 1;
		for (std::size_t i = 1; i <= N; i++) {

			val = val * i;
		}
		return val;
	}
}//func end

//this takes a string with digits and returns the integer 
//if you put wrong string inside it will simply stop and return the value 
//that manage to calculate 
inline _NODISCARD _CONSTEXPR  std::size_t Parse_Integer(const char* str, std::size_t value = 0) {//the passed str must contain only digits  
	return (*str >= '0' && *str <= '9') ? Parse_Integer(str + 1, value * (std::size_t)10 + (std::size_t)(*str - '0')) : value;

}

//this structs takes a type t and tells how many dimensions does it have
//for int[5][5] it gives 2 for int [3][4][5] it gives 3 for int it gives 0
//BEGIN
template<typename t>
struct Dimensions {
	inline static _CONSTEXPR std::size_t value = 0;
};
template<typename t, std::size_t n>
struct Dimensions<t[n]> {
	inline static _CONSTEXPR std::size_t value = 1 + Dimensions<t>::value;
};
template<typename t>
struct Dimensions<t[]> {
	inline static _CONSTEXPR std::size_t value = 1 + Dimensions<t>::value;
};

template<typename t>
inline static _CONSTEXPR std::size_t Dimensions_V = Dimensions<t>::value;
//END

//this converts a binary string to decimal 
inline _NODISCARD _CONSTEXPR  std::size_t Binary_To_Decimal(const char* bin, std::size_t value = 0)
{//the passed str must contain only digits,//func begin 

	return (*bin >= '0' && *bin <= '1') ? Binary_To_Decimal(bin + 1, value * (std::size_t)2 + (std::size_t)(*bin - '0')) : value;

}//func end 

//in the standard there is the std::conditional_t type 
// that based on a condition gives types 
//i wanted to make this for values while having a condition
//used perfect forwarding this func and univesal references this func
template<bool condition, typename t, typename u>
inline _NODISCARD _CONSTEXPR decltype(auto) If_Then_Else(t&& value1, u&& value2)noexcept
{//func begin
	//different if to avoid reference collapsing rules
	if constexpr (condition) {

		return std::forward<t>(value1);
	}
	if constexpr (!condition) {
		return std::forward<u>(value2);
	}

}//func end

//this is a struct that take types and 
//takes a t a first and rest types 
//and pretty much tells in which index the type t you are looking for
//is like Type_Index<int,double,float,int> gives 2 for result 
//is the underlying type is not there it gives an index out of range of the types
//BEGIN
template<typename t, typename...types>
struct Type_Index;

template<typename t, typename first, typename...rest>
struct  Type_Index<t, first, rest...> {
	inline _CONSTEXPR static size_t value = std::is_same_v<t, first> ? 0 : 1 + Type_Index<t, rest...>::value;
};
template<typename t>
struct  Type_Index<t> {
	inline _CONSTEXPR static size_t value = 0;
};
//END

//this template uses the SFINAE context to 
//check if the type has a .size() method 
//BEGIN
template<typename t, typename = void>
struct Has_Size :std::false_type {};
template<typename t>
struct Has_Size<t, std::void_t<decltype(std::declval<t>().size())>> :std::true_type {};
template<typename t, typename = void>
inline static _CONSTEXPR bool Has_Size_V = Has_Size<t>::value;
//END
//wrapper type 
template<typename T>
struct Identity { using Type = T; };

//better void_t
//just a better void_t because with the void_t of the standard 
//the is a problem because its a type alias and you can overload template parameters when you use this 
template<typename _Ty, typename...>
struct first :Identity<_Ty> {};
template<typename ...types>
using Void_t = typename first<void, types...>::Type;


//this is a struct that used the SFINAE context to check if for the following types
//you can aply size of 
//BEGIN
template<typename t, typename = void>
struct Supports_Sizeof :std::false_type {};
template<typename t>
struct Supports_Sizeof <t, Void_t<decltype(sizeof(t))>> :std::true_type {};

template<typename t, typename = void>
inline static _CONSTEXPR bool Supports_Sizeof_V = Supports_Sizeof<t>::value;
//END



//BEGIN
//THIS STRUCT SIMPLY TAKES A TYPE PACK AND CHECKS WHITCH TYPE HAS THE BIGGEST SIZE
//AND RETURNS IT AND DOES THAT WITH STD::CONDITIONAL_T AND SIZEOF
//AND ALSO USES TEMPLATE RECURSIVE INSTANTIATION 
//CAN BE USED AT COMPILE TIME 
template<typename ...types>
struct Largest_Type;

template<typename first, typename second, typename...rest>
struct Largest_Type<first, second, rest...> {
	static_assert(Supports_Sizeof_V<first>&& Supports_Sizeof_V<second> && (Supports_Sizeof_V<rest>&&...), "all types must support sizeof operator ,no incomplete types allowed");



	using Type = typename std::conditional_t<
		(sizeof(first) > sizeof(second)),
		Identity<typename Largest_Type<first, rest...>::Type>,
		Identity<typename Largest_Type<second, rest...>::Type>
	>::Type;
};
template<typename first, typename  second>
struct Largest_Type<first, second> {
	static_assert(Supports_Sizeof_V<first>&& Supports_Sizeof_V<second>, "all types must support sizeof operator ,no incomplete types allowed");
	using Type = std::conditional_t<(sizeof(first) > sizeof(second)), first, second>;
};
template<typename first>
struct Largest_Type<first> {
	static_assert(Supports_Sizeof_V<first>, "all types must support sizeof operator ,no incomplete types allowed");
	using Type = first;
};
//END

//takes to C-strings and checks if they are the same
//,the C-strings must have the same length 
//can be used at compile time
template<std::size_t N>
inline _NODISCARD _CONSTEXPR bool Is_Equal_Strings(const char(&str1)[N]
	, const char(&str2)[N])noexcept {//func begin
	for (size_t i = 0; i < N; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}//for loop that checks if they are the same 
	return true;
}//func end


//Is_Palindrome takes a const char (&str)[N] and check if the C-string inside is a palidrome
//compile-time func 
template<std::size_t N>
inline _NODISCARD _CONSTEXPR bool Is_Palindrome(const char(&str)[N])noexcept
{//func begin
	static_assert(N > 1, "N should be >1");
	//if N==1 the C-string is "" so doesnt make any sense for an arg
	if (N == 2)return true;
	//if N==2 the C-string is 2 1 char of course it is palidrome
	std::array<char, N - 1>result1{};
	std::array<char, N - 1>result2{};

	for (std::size_t i = 0; i < N - 1; i++) {
		result1[i] = str[i];

	}//initialize an array with the string

	std::size_t j = 0;

	for (std::size_t i = N - 2; i > 0; i--) {
		result2[j] = str[i];
		j++;
	}//initialize a second array with the string reversed
	result2[j] = str[0];

	if (static_cast<int>(N - 2) >= 0) {
		//checks if this two arrays have the same contents
		for (std::size_t i = 0; i < N - 2; i++) {

			if (result1[i] != result2[i]) {
				return false;
			}
		}
	}
	return true;
}//func end 

//Is_Palidrome second overload takes chars like this Is_Palidrome<'1','0','1'>() 
// you can pass the chars only like this 
//and take this a string and checks if it is a palidrome 
//this overload simply takes a parameter pack more clear code than the other 
//can be used at compile time 
template<auto ...values>
inline _NODISCARD _CONSTEXPR bool Is_Palindrome()
{//func begin
	static_assert(std::conjunction_v<std::is_same<char, decltype(values)>...>);
	static_assert(sizeof...(values) > 0);

	std::array a{ values... };
	std::array b{ values... };
	std::reverse(b.begin(), b.end());

	return a == b;
}//func end

//this func calculates the square root of a long double 
//can be used at compile time
//uses Is_Equal func and uses also recursion
//dont change the values start ,end 
template<long double n, long double start = 1.0l, long   double end = n>
requires(n > 0 )
inline _NODISCARD _CONSTEXPR  long double Sqrt_For_Doubles() 
{//func begin

	constexpr  long double mid = start + (end - start) / 2.0;
	if constexpr (Is_Equal<mid * mid, n, long double>()) {
		return mid;
	}
	else {
		if constexpr (mid * mid > n) {
			return Sqrt_For_Doubles<n, start, mid - 1>();
		}
		else if constexpr (mid * mid < n) {
			return Sqrt_For_Doubles<n, mid + 1, end>();
		}
	}

}//func end 

//simple func that the return the greatest common divison for two unsigned integers
//can be used at compile time
inline _NODISCARD _CONSTEXPR std::size_t GCD(std::size_t a, std::size_t b)
{//func begin
	return (b == 0)?a :GCD(b, a % b);

}//func end

//this func count the number of ones that the binary represntation of n has
//can be used at compile time 
//0b for binary and 0's and 1's
inline _NODISCARD _CONSTEXPR std::size_t Popcount(std::size_t n) 
{//func begin
	return n == 0 ? 0 : (n & 1) + Popcount(n >> 1);
}//func end





_PANAGIOTIS_END



/*
//BEGIN
//THIS STRUCT SIMPLY TAKES A TYPE PACK AND CHECKS WHITCH TYPE HAS THE BIGGEST SIZE
//AND RETURNS IT AND DOES THAT WITH STD::CONDITIONAL_T AND SIZEOF
//AND ALSO USES TEMPLATE RECURSIVE INSTANTIATION
//CAN BE USED AT COMPILE TIME
template<typename ...types>
struct Largest_Type;

//custom wrapper for the conditional of the Largest_Type struct
//can be used at compile time
template<typename param, typename...rest>
struct Wrapper {
	using Type = typename Largest_Type<param, rest...>::Type;
};

template<typename first, typename second, typename...rest>
struct Largest_Type<first, second, rest...> {
	static_assert(Supports_Sizeof_V<first>&& Supports_Sizeof_V<second> && (Supports_Sizeof_V<rest>&&...), "all types must support sizeof operator ,no incomplete types allowed");

	using Type = typename std::conditional_t<
		(sizeof(first) > sizeof(second)),
		 Wrapper<first,rest...>,
		 Wrapper<second,rest...>
	>::Type;
};
template<typename first, typename  second>
struct Largest_Type<first, second> {
	static_assert(Supports_Sizeof_V<first>&& Supports_Sizeof_V<second>, "all types must support sizeof operator ,no incomplete types allowed");
	using Type = std::conditional_t<(sizeof(first) > sizeof(second)), first, second>;
};
template<typename first>
struct Largest_Type<first> {
	static_assert(Supports_Sizeof_V<first>, "all types must support sizeof operator ,no incomplete types allowed");
	using Type = first;
};

//END
*/
