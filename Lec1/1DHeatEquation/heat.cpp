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

    std::vector<double> u(N, 0.0);
    // Initial condition: a Gaussian pulse in the center
    for (int i=0; i<N; ++i) {
        double x = i*dx;
        u[i] = exp(- (x - L/2)*(x - L/2) );
    }
    //next[i] = current[i] + r * (current[i+1] - 2.0 * current[i] + current[i-1]);
    std::vector<double> u_new(N, 0.0);
    for (int i=0; i<timeSteps; ++i) {
        for (int j=1; j<N-1; ++j) {
            u_new[j] = u[j] + alpha*dt/(dx*dx)*(u[j+1] - 2.0*u[j] + u[j-1]);

        }
        std::ranges::swap(u, u_new);
        for (const auto val : u) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}
