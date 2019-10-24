#ifndef IMMORTALSTACK_IM_STACK_H
#define IMMORTALSTACK_IM_STACK_H

#include <cassert>
#include <functional>
#include <stack>
#include "dump.h"

#define verified(code)  { \
    if(OK()) {\
        code\
        if(!OK()) {\
            Dump<ImStack<T>>()();\
        }\
    } else {\
        Dump<ImStack<T>>()();\
    }    \
}

template <typename T>
class ImStack {
public:
    ImStack();
    explicit ImStack(size_t size);
    ImStack(std::initializer_list<T> init_list);
    explicit ImStack(const std::stack<T>& other_stack);

    void pop();
    void push(const T& element);
    void push(T&& element);
    template <typename ...Args>
        void emplace_back(Args&&... args);
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    T& top();
    const T& top() const;

    ImStack<T>& operator=(const ImStack<T>& other_stack);
    ImStack<T>& operator=(ImStack<T>&& other_stack);
    bool operator==(const ImStack<T>& other_stack);
    void swap(const ImStack<T>& other_stack);
    ~ImStack();

private:
    const size_t MAXSIZE = 1024 * 1024 * 1024 / sizeof(T);  // Gb
    size_t sz;
    size_t capacity;

    // starting canary - buf[0], ending canary - buf[capacity - 1]
    T* buf;

    const size_t POISON = 0xAAAAAAAAAAAAA;
    const size_t CANARYVALUE_S = 0xA3A3A3A3A3A3A;
    const size_t CANARYVALUE_E = 0xBABABABABABAB;

    bool OK();
    void CheckAndReallocate();
    void Reallocate();
    void InitCanaries();
    void InitPoison();

    friend Dump<ImStack<T>>;
};

#endif //IMMORTALSTACK_IM_STACK_H
