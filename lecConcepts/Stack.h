#include<deque>

template<typename T>
class Stack {
public:
    [[nodiscard]] auto top() const -> const T& { return stack.front();}
    [[nodiscard]] auto top() -> T& { return stack.front();}

    void  push(const T& pushValue) { stack.push_front(pushValue);}
    void  pop()  { stack.pop_front();}


    [[nodiscard]] auto size() const -> size_t {return stack.size();}
    [[nodiscard]] auto  isEmpty() const -> bool { return stack.empty();}
private:
    std::deque<T> stack{};
};
