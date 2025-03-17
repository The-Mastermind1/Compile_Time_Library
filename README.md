# Compile Time Library 🚀⏳ 
# 🔷 C++ Templates & Metaprogramming 🏗️📦

<br>
<br>
# EXPLANATION
# BEGIN
1)This library 936 line of code it is well detailed of what it does<br><br>
2) the Macros.h header serves as a helper library to write exception and macros for the header.h 
and concepts that will be used at header.h<br><br>
3)The header.h simply contains simple utility functions that can be used at compile time <br><br>
4) inside this library there are various of functions structs and classes that use templates pretty much to give result at compile time<br><br>
5)some of them use template recursive instantiation to give the result like:
Is_Prime,Sqrt,Factorial,Fibonnaci,Max,Min,Terms
<br>
<br>
<br>
<br>
6)some of them are simple funcs that use recursion to give the result like :<br>
Str_Len,Parce_Integer,Binary_To_Decimal,Sqrt_For_Doubles,GCD,Popcount
# END
<br><br>
The struct Supports_Sizeof simply check if you can apply sizeof operator into the passed type ,this used sfinaei <br>
<br> there is also a better version of void that solves most of the problems that std::void_t has <br>
<br><br> there is also a struct called dimensions which is pretty much the same with the std::rank from C++ Standard , i
thought about it alone 
<br>
there is also a struct called Largest_Type which takes a list of types and gives the type that is the largest in bytes 
<br>
there are two funcs that check if a string is palidrome you can use whoever you want 
<br>
there is also a wrapped struct called Identity that is used inside void t and largest_type
<br>
the struct has_size simply checks if the type passed supports a method called size();
<br>
there is also a struct called Type_Index that takes a list of type and the returns the index of the desired type like:
Type_Index<int,int,float,double,std::size_t> give 0 
first int is the desired type ,the rest of the types are the types of the list that we are going to search 
<br>

The C++ Standard contains in the header <type_traits> a struct called std::conditional_t which takes a bool condition a first type and a second type 
and based on the condition it returns the first or the second type
<br>
i also created something like this but with values and If_Then_Else based on the condition it gives it returns a value that you gave it 
<br>
there is also a func called Factorial which returns the result but it used for loop not template recursive instantiation 
<br>
the func Make_Reversed_String return the string that is given reversed 
<br>
the func Type_Name gives back the name of the type you gave it along with something else 
<br>
inside the Array_Algorithms class there are simple compile time algorithms for the array and one at runtime like :
<br>
Binary_Search,Is_Sorted,Is_NxN ,dotproduct,doaddition,dosubtraction, print1D_array,Linear_Search,Bubble_Sort,Reverse_Array
<br>
There is also a func called Is_Equal_Strings
<br>
Also GCD=GREATEST COMMOND DIVISOR
<br>
Popcount counts the number of ones that the binary represntation of n has 
<br>
I Wanted a min max that could work with more arguments 
<br> 
there is also a struct called Abs and a func Is_Equal

Power of Integers gives the result x^n 

<br> the func called terms can be used to give the result of e^x and uses an approximation to do that, not the best func ....
you are the one that gives the iterations be careful with that ,the more iterations the better 
<br>
# 👥CONTRIBUTORS:
~The-Mastermind1<br>

# 🙏 Thank You for Reading!
# I appreciate your interest in my project! 🚀

