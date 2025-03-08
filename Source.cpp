#include"Header.h"
#include <iostream>
#include <numeric>
#include<tuple>
#include<variant>
#include<bitset>
using namespace panagiotis;
template<typename t>
void kati2() {

}
int main() {
	//Supports_Sizeof_V<int[5]>;
	
	std::cout<<typeid(Largest_Type<int[], float, double, size_t, int, std::string>::Type).name();
	
}
