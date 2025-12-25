#include <vector>
#include <iostream>
#include <algorithm> 
#include <iterator>
#include <random>

int main() {
    
    
    std::vector<int> numbers = {1,2,3,4,5};
    // Traditional way of iterating
    for (auto it=numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::vector<int> inputs = {5, 1, -2,3,4};
    std::vector<int> output(inputs.size());
    // Using lambda to define the operator  
    auto square = [](int x){return x*x;};

    //here we are using std::transform 
    std::transform(
        inputs.begin(), inputs.end(), output.begin(),
        square
    );

    std::ostream_iterator<int> out_it{std::cout, ", "};
    std::cout << "Using ostream_iterator: ";
    std::ranges::copy(output, out_it);
    std::cout << "\n";

    std::ranges::for_each(inputs, [](auto x) {
        std::cout << x*x << " ";
    }
    );
    
    std::cout << "\n";
    // Using ranges transform
    std::ranges::transform(inputs, out_it, square);
    std::cout << "\n";

    //sorting using ranges, is it in place operation? 
    std::ranges::sort(inputs);
    std::cout << "Sorted inputs: ";
    std::ranges::copy(inputs, out_it);
    std::cout << "\n";

    //sort by absolute value with projection 
    std::ranges::shuffle(inputs, std::mt19937{std::random_device{}()});


    std::ranges::sort(inputs, {}, [](int x){return abs(x);});
    std::cout << "Sorted by absolute value: ";
    std::cout << "Sorted inputs: ";
    std::ranges::copy(inputs, out_it);
    std::cout << "\n";
}