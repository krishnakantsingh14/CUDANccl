#include<iostream>
#include<vector>
#include<cmath>
#include<ranges>
#include<iterator>
#include<algorithm>
#include <numeric>


void gaussian_initial_condition(std::span<double> uspan, double L, double dx) { 
    // static const int n = uspan.size();
    auto uview = std::views::iota(0uz, uspan.size()) 
        | std::views::transform ([=]( int i ) { // capture by value, for thread safety
            double x = i*dx;
            return std::exp(-std::pow(x - L/2.0, 2));
        }
    );
    
    std::ranges::copy(uview, uspan.begin());

}


void simulation_step(std::span<double> uspan, double alpha) {
    auto sim_view = std::views::adjacent<3>(uspan) | std::views::transform([alpha] (auto window) {
        auto [p, c, n] = window;
        return c + alpha*(n-2.0*c + p);
    });
    std::ranges::copy(sim_view, uspan.begin()+1);

}



int main() {

    const int N =100; 
    const double L = 10.0;
    const double alpha = 0.01;
    const double dx = L/(N-1);
    const double dt = 0.1*dx*dx/alpha; // stability condition
    const int timeSteps = 1000;

    std::vector<double> u(N,0);
    std::vector<double> unew(N,0);
    std::span<double> uspan(u);


    gaussian_initial_condition(u, L, dx);   
    auto middle = uspan.subspan(48,52);
    gaussian_initial_condition(middle, 0.1, dx);   
    std::cout << "Temperature at center: " << u[N/2] << std::endl;
    std::cout << "Temperature at start: " << u[1] << std::endl;
    std::cout << "Temperature at last: " << u[N-1] << std::endl;
 

    for (int t=0; t<timeSteps; ++t) {
        simulation_step(uspan, alpha);
        std::cout << "Temperature at center: " << u[N/2] << std::endl;

    }
}
