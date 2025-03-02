#include"Header.h"
#include <iostream>
#include <numeric>
#include <array>
using namespace panagiotis;





int main() {
    constexpr static std::array<int, 5>numbers1={ 1,2,3,4,5 };
     
    constexpr static std::array<int, 5>numbers2 = { 6,7,8,9,10 };
    constexpr static std::array<int, 5> a=Array_Algorithms::doaddition<int,5>(numbers1.cbegin(), numbers2.cbegin());
    
    
    //constexpr int result = std::accumulate(numbers.begin(), numbers.end(), 0);
    //std::cout << "Sum: " << result << std::endl;
}
