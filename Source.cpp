#include"Header.h"
#include <iostream>
#include <numeric>
#include<tuple>
using namespace panagiotis;




int main() {
	constexpr static char a[] = "18446744073709551615";
	constexpr size_t b = Parse_Integer(a);
	std::cout << b << '\n';
	

	 
	
}
