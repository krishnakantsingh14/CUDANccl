#include<vector>
#include<cmath>
#include<iostream>
#include<ranges>
#include<algorithm>
#include<iterator>

int main() {
    const int N =100; 
    const double L = 10.0;
    const double alpha = 0.01;
    const double dx = L/(N-1);
    const double dt = 0.1*dx*dx/alpha; // stability condition
    const int timeSteps = 1000;
    int index = 0;

    std::vector<double> u(N, 0.0);
    std::vector<double> ugen(N, 0.0);
    // Initial condition: a Gaussian pulse in the center
    // for (int i=0; i<N; ++i) {
    //     double x = i*dx;
    //     u[i] = exp(- (x - L/2)*(x - L/2) );
    // }
    std::ranges::generate(u, [&]() {
        double x = index*dx;
        ++index;
        return std::exp(-(x - L/2)*(x - L/2) );
    });

    auto uview = std::views::iota(0, N)
      | std::views::transform([&](int i) {
            double x = i * dx;
            return std::exp(-std::pow(x - L / 2.0, 2));
        }
    );
    std::ranges::copy(uview, ugen.begin());
    // | std::ranges::to<std::vector<double>>(); -> for c++23 and gcc14

    std::cout << "Temperature at center: " << u[N/2] << "  "<<index << std::endl;
    std::cout << "Temperature at center: " << ugen[N/2] << "  "<<index << std::endl;


    //next[i] = current[i] + r * (current[i+1] - 2.0 * current[i] + current[i-1]);
    // alpha*dt/(dx*dx) -> alpha*(0.1*dx*dx/alpha)/(dx*dx) -> 0.1 ~ alpha
    std::vector<double> u_new(N, 0.0);

    // for (int i=0; i<timeSteps; ++i) {
    //     for (int j=1; j<N-1; ++j) {
    //         u_new[j] = u[j] + alpha*(u[j+1] - 2.0*u[j] + u[j-1]);

    //     }
    //     std::ranges::swap(u, u_new);
    //     for (const auto val : u) {
    //         std::cout << val << " ";
    //     }
    //     std::cout << "\n";
    // }
}
