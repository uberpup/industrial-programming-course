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
            Dump<ImStack<T>>(*this);\
        }\
    } else {\
        Dump<ImStack<T>>(*this);\
    }    \
}

//! Template class implementing Immortal Stack
template <typename T>
class ImStack {
public:
    //! trivial constructor
    ImStack();
    //! size constructor
    explicit ImStack(size_t size);
    //! std::initializer_list constructor
    ImStack(std::initializer_list<T> init_list);
    //! std::stack constructor
    explicit ImStack(const std::stack<T>& other_stack);
    //! pops top element, if it exists; sz == 0 -> error
    void pop();
    //! pushes element to ImStack
    void push(const T& element);
    //! pushes element to ImStack by std::move
    void push(T&& element);
    //! emplaces element to ImStack
    template <typename ...Args>
        void emplace_back(Args&&... args);
    //! true if ImStack has no elements
    [[nodiscard]] bool empty() const;
    //! number of elements
    [[nodiscard]] size_t size() const;
    //! returns the top element, not popping it from ImStack
    T& top();
    //! returns the top element, not popping it from ImStack; const
    const T& top() const;

    ImStack<T>& operator=(const ImStack<T>& other_stack) = delete;  // Might be released in the future
    ImStack<T>& operator=(ImStack<T>&& other_stack) = delete;
    bool operator==(const ImStack<T>& other_stack) = delete;
    void swap(const ImStack<T>& other_stack) = delete;
    ~ImStack();

private:
    const size_t MAXSIZE = 1024 * 1024 * 1024 / sizeof(T);  // Gb
    size_t sz;
    size_t capacity;
    // starting canary - buf[0], ending canary - buf[capacity - 1]
    T* buf;
    size_t* hash_buf;

    const size_t POISON = 0xAAAAAAAAAAAAA;
    const size_t CANARYVALUE_S = 0xA3A3A3A3A3A3A;
    const size_t CANARYVALUE_E = 0xBABABABABABAB;

    bool OK();
    void CheckAndReallocate();
    void Reallocate();
    void InitCanaries();
    void InitPoison();
    void InitHash();

    friend Dump<ImStack<T>>;
};

#endif //IMMORTALSTACK_IM_STACK_H
