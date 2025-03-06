#include"Header.h"
#include <iostream>
#include <numeric>
#include<tuple>
using namespace panagiotis;

void kati(std::array<std::array<int, 4>, 5>::iterator it1) {

}



int main() {
	//constexpr static std::array<std::array<int, 5>, 4>b = {};
	//constexpr bool a=Array_Algorithms::Is_NxN_Matrix(b);
	//std::cout << a << '\n';
	 std::array<std::array<int, 5>, 5>b{};
	 bool a= Array_Algorithms::Is_NxN(b).value;
	std::cout << a << '\n';
	
	
	 int c[5][5] = {};
	 bool d = Array_Algorithms::Is_NxN(c).value;
	std::cout << d << '\n';

	
	

	 
	
}
