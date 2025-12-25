#include <vector>
#include <iostream>
#include <algorithm> 
#include <iterator>

int main() {
    std::vector<int> numbers = {1,2,3,4,5};
    for (auto it=numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::vector<int> inputs = {1, 2,3,4};
    std::vector<int> output(inputs.size()); 
    auto square = [](int x){return x*x;};
    std::transform(
        inputs.begin(), inputs.end(), output.begin(),
        square
    );

    std::ostream_iterator<int> out_it{std::cout, ""};
    std::cout << "Using ostream_iterator: ";
    std::ranges::copy(output, out_it);
    std::cout << "\n";

    std::ranges::for_each(inputs, [](auto x) {
        std::cout << x*x << " ";
    }
    );
    
    std::cout << "\n";

    std::ranges::transform(inputs, out_it, square);
    std::cout << "\n";
}