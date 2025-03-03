#include"Header.h"
#include <iostream>
#include <numeric>

using namespace panagiotis;




int main() {
	      // Prints type name with the compiler's internal representation
       
        
    constexpr auto reversed = make_reversed_string("compile");

         for (char c : reversed) {
             std::cout << c;
         }
          std::cout << '\n';  // Output: elipmoc
       
	 
	
}
