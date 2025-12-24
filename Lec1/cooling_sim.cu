#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>


/// We will use this function:
/// T_n = T_{n-1} + K(T_room - T_{n-1})
/// where K is a constant that depends on the material and environment.
/// T_room = 20.0 (room temperature)



int main() {
    const float k = 0.5;
    const float ambient_temp = 20;
    thrust::device_vector<float> temp{42, 24, 50};
    auto op = [=] __host__ __device__ (float temp_val) {
        float diff = ambient_temp - temp_val ;
        return temp_val + k*diff;
    };

    for (int step=0; step <3; step++) {
        thrust::transform(temp.begin(), temp.end(), temp.begin(), op);    
	thrust::host_vector<float> temp_host = temp;
	for (float t : temp_host) std::cout << t << " ";
        std::cout << "\n";
    }

}
