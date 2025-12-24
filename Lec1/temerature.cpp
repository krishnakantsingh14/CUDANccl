#include<iostream>
#include <vector>
#include<algorithm>
#include <ranges>


/// We will use this function:
/// T_n = T_{n-1} + K(T_room - T_{n-1})
/// where K is a constant that depends on the material and environment.
/// T_room = 20.0 (room temperature)



int main() {
    const float k = 0.5;
    const float ambient_temp = 20;
    std::vector<float> temp{42, 24, 50};
    auto op = [=](float temp) {
        float diff = ambient_temp - temp;
        return temp + k*diff;
    };

    for (int step=0; step <3; step++) {
        for (float t : temp) std::cout << t << " ";
        std::cout << "\n";
        std::ranges::transform(temp, temp.begin(), op);    
    }

}