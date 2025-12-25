#include<ranges>
#include<vector>
#include<iostream>
#include<iterator>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> nums = {0,12,3,4,8,10,7,13};
    // int sum{0};
    // using pipe syntex
    // std::ranges::sort(nums);
    auto view = nums
        | std::views::filter([](int i) {return i%2==0;} )
        | std::views::transform([](int i) {return i*i;});
    
    int sum = std::ranges::fold_left(view, 
        0, std::plus{});
    // std::ranges::for_each(view, [&](int i){sum+=i;});

    int acc = std::ranges::fold_right(view, 0, std::plus{});
    std::cout << "Sum of squares of even numbers: " << sum << "  " << acc << "\n";

}
