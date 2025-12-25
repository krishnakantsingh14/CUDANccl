#include <vector>
#include <iostream>
#include <algorithm> 


int main() {
    std::vector<int> numbers = {1,2,3,4,5};
    for (auto it=numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::vector<int> inputs = {1, 2,3,4};
    std::vector<int> output(inputs.size()); 
    std::transform(
        inputs.begin(), inputs.end(), output.begin(),
        [](int x){return x*x;}
    );

    // for (auto ito=output.begin(); ito != output.end(); ++ito) {
    //     std::cout << *ito << " ";
    // }
    // std::cout << "\n";
    // Using range based-loop C++20 style 
    
    for (auto ito : output) {
        std::cout << ito << " ";
    }
    std::cout << "\n";

}