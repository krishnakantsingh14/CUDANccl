#include<iostream>
#include "Stack.h"

template<typename T>
auto multiply(T a, T b) -> T {
    return a*b;
}

auto main() -> int {
    using namespace std;
    Stack<double> doubleStack{}; 
    constexpr size_t doubleStackOfSize{5}; 
    double doubleValue{5.5}; 
    
    for (size_t i{0} ; i<doubleStackOfSize; ++i) {
        doubleStack.push(doubleValue);
        // cout<< doubleStack.size() << endl;
        doubleValue += 1.5;  
        cout << doubleStack.top() << " ";

    }

    cout << endl;
    cout << "Pooping elements from the stack" << "\n";
    // for (size_t i{0} ; i<doubleStackOfSize; ++i) {
    while (!doubleStack.isEmpty()) {
        cout << doubleStack.top() << std::endl;
        doubleStack.pop(); 
    }

    cout<< multiply<int>(3., 7.1) << endl;
} 
