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