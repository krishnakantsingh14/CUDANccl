#include<iostream>
#include<vector>
#include<cmath>
#include<ranges>
#include<iterator>
#include<algorithm>
#include <numeric>


void gaussian_initial_condition(std::span<double> uspan, int N, double L, double dx) { 

    auto uview = std::views::iota(0, N) 
        | std::views::transform ([=]( int i ) { // capture by value, for thread safety
            double x = i*dx;
            return std::exp(-std::pow(x - L/2.0, 2));
        }
    );
    std::ranges::copy(uview, uspan.begin());
}



int main() {

    const int N =100; 
    const double L = 10.0;
    const double alpha = 0.01;
    const double dx = L/(N-1);
    const double dt = 0.1*dx*dx/alpha; // stability condition
    const int timeSteps = 1000;

    std::vector<double> u(N,0);

    gaussian_initial_condition(u, N, L, dx);    
    std::cout << "Temperature at center: " << u[N/2] << std::endl;

}