# C++ Iterators 
0. Memory model
1. transform
2. Zip iterator
3. 

**Before**
```
for (auto ito=output.begin(); ito != output.end(); ++ito) {
    std::cout << *ito << " ";
}
std::cout << "\n";
```

**Modern: Using range based-loop C++20 style** 

```
for (auto ito : output) {
    std::cout << ito << " ";
}
```
**Modern: Using range**
```
    std::ostream_iterator<int> out_it{std::cout, ""};
    std::cout << "Using ostream_iterator: ";
    std::ranges::copy(output, out_it);
    std::cout << "\n";
```

**Date**: 01/01/2026
```
std::views::ostream<int> output {std::cout, " "};
std::views::copy(from, output)
```
**for_each and for_each_n**
```
std::views::for_each(a, [](auto i){std::cout << i*2 << " "});
std::views::for_each(a, [&](){sum+=i});

```

**fill and generate**
```
std::views::fill(a, 5)
std::views::fill_n(a.begin(), 3, 5)
std::views::generate(a, generator)
std::views::generate_n(a.begin(), 5, generator)
```







