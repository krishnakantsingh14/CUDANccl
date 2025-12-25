# Implementation detail

```
#include <ranges>
#include <algorithm>

// ... inside main ...

auto gaussian_view = std::views::iota(0, N) // Create a range of indices [0, 1, 2, ... N-1]
    | std::views::transform([&](int i) {    // Transform each index into a temperature
        double x = i * dx;
        double shift = x - L / 2.0;
        return std::exp(-(shift * shift));
    });

// Copy the calculated values into your vector
std::ranges::copy(gaussian_view, u.begin());
```
**Using ranges**
```
// Instead of L/2 inside the lambda, pre-calculate it
const double mid = L / 2.0;
const double inv_dx = dx; // Multiplication is faster than division

std::ranges::generate(u, [=, index = 0]() mutable {
    double x = (index++) * inv_dx;
    double diff = x - mid;
    return std::exp(-(diff * diff));
});
```

Key Improvement: Note the [=, index = 0] mutable. This is an init-capture. It creates a local version of index inside the lambda itself. This makes the lambda self-contained and "pure," meaning it doesn't mess with variables in your main() function.


**My appraoch was not thread safe**

```
std::ranges::generate(u, [&]() {
    double x = index*dx;
    ++index;
    return std::exp(-(x - L/2)*(x - L/2) );
    });
```
