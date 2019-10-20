#ifndef IMMORTALSTACK_IM_STACK_H
#define IMMORTALSTACK_IM_STACK_H

#include <stack>

template <typename T>
class ImStack {
    ImStack();
    ImStack(size_t size);
    ImStack(std::initializer_list<T> init_list);
    ImStack(const std::stack<T>& other_stack);

    void pop();
    void push(const T& element);
    void pop(T&& element);
    bool empty() const;
    size_t size() const;
    T& top();
    const T& top() const;

    ImStack<T>& operator=(const ImStack<T>& other_stack);
    // ImStack<T>& operator=(const std::stack<T>& other_stack);
    ImStack<T>& operator=(ImStack<T>&& other_stack);
    // ImStack<T>& operator=(std::stack<T>&& other_stack);

    bool operator==(const ImStack<T>& other_stack);

    void swap(const ImStack<T>& other_stack);
    // void swap(const std::stack<T>& other_stack);
    ~ImStack();
private:
    size_t sz;
    size_t capacity;
    T* buf;

    const size_t POISON;

    void Reallocate();
    void FillCanaries();
    void FillHash();

    // [CANARY][HASH][CUR_SIZE][BUFFER_SIZE][B-U-F-F-E-R][CANARY]
};

#endif //IMMORTALSTACK_IM_STACK_H
