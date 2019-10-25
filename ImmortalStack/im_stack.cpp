#include "im_stack.h"

// Stack functions implementation


template <typename T>
ImStack<T>::ImStack(): sz(0), capacity(2) {
    buf = (T*) calloc(sizeof(T), capacity);
    hash_buf = (size_t*) calloc(sizeof(size_t), capacity);

    InitCanaries();
    InitPoison();
    InitHash();
}

template <typename T>
ImStack<T>::ImStack(size_t size) : sz(size),
        capacity(2 >=  1 + sz * 2 ? 2 : 1 + sz * 2)  {

    buf = (T*) calloc(sizeof(T), capacity);
    hash_buf = (size_t*) calloc(sizeof(size_t), capacity);

    InitCanaries();
    InitPoison();
    InitHash();
}

template <typename T>
ImStack<T>::ImStack(const std::stack<T>& other_stack) {
    buf = (T*) calloc(sizeof(T), capacity);
    hash_buf = (size_t*) calloc(sizeof(size_t), capacity);

    InitCanaries();
    InitPoison();
    InitHash();
}

template <typename T>
ImStack<T>::ImStack(std::initializer_list<T> init_list) : sz(init_list.size()),
        capacity(1 + 2 * init_list.size()) {

    buf = (T*) calloc(sizeof(T), capacity);
    hash_buf = (size_t*) calloc(sizeof(size_t), capacity);

    InitCanaries();
    InitPoison();
    InitHash();
}

template <typename T>
ImStack<T>::~ImStack() {
    free(buf);
    free(hash_buf);
}

template <typename T>
template <typename ...Args>
void ImStack<T>::emplace_back(Args&&... args) verified({
    ++sz;
    CheckAndReallocate();

    new(buf[sz]) T(std::forward<Args>(args)...);
    hash_buf[sz] = std::hash<T>(buf(sz));
})

template <typename T>
void ImStack<T>::push(const T& element) verified ({
    ++sz;
    CheckAndReallocate();

    buf[sz] = element;
    hash_buf[sz] = std::hash<T>(buf[sz]);
})

template <typename T>
void ImStack<T>::push(T&& element) verified ({
    ++sz;
    CheckAndReallocate();

    buf[sz] = std::forward<T>(element);
    hash_buf[sz] = std::hash<T>(buf[sz]);
})

template <typename T>
void ImStack<T>::pop() verified ({
    if (!sz) {
        Dump<ImStack<T>>();
    } else {
        buf[sz] = std::hash<T>(POISON);
        --sz;
    }
})

template <typename T>
bool ImStack<T>::empty() const verified ({
    return !sz;
})

template <typename T>
size_t ImStack<T>::size() const verified ({
    return sz;
})

template <typename T>
T& ImStack<T>::top() verified ({
    return buf[sz];
})

template <typename T>
const T& ImStack<T>::top() const verified ({
    return buf[sz];
})

template <typename T>
void ImStack<T>::InitCanaries() {
    buf[0] = reinterpret_cast<T>(CANARYVALUE_S);
    buf[capacity - 1] = reinterpret_cast<T>(CANARYVALUE_E);
}

template <typename T>
void ImStack<T>::InitHash() {
    for (size_t i = 0; i < capacity; ++i) {
        hash_buf[i] = std::hash<T>(buf[i]);
    }
}

template <typename T>
void ImStack<T>::InitPoison() {
    for (size_t i = sz + 1; i < capacity - 1; ++i) {
        buf[i] = std::hash<T>(POISON);
    }
}

template <typename T>
void ImStack<T>::CheckAndReallocate() {
    if (sz * 2 >= capacity) {
        Reallocate();
    }
}

template <typename T>
void ImStack<T>::Reallocate() {
    capacity *= 2;
    capacity += 1;
    buf = (T*) realloc(buf, capacity * sizeof(T));

    buf[capacity] = buf[(capacity - 1)/ 2];

    InitPoison();
}

template <typename T>
bool ImStack<T>::OK() {
    if (this == nullptr) {
        return false;
    }
    if (sz > capacity) {
        return false;
    }
    if (capacity > MAXSIZE) {
        return false;
    }
    if (buf[0] != reinterpret_cast<T>(CANARYVALUE_S)) {
        return false;
    }
    if (buf[capacity - 1] != reinterpret_cast<T>(CANARYVALUE_E)) {
        return false;
    }
    for (size_t i = 0; i < sz; ++i) {
        if (hash_buf[i] != std::hash<T>(buf[i])) {
            return false;
        }
    }
    for (size_t i = sz; i < capacity; ++i) {
        if (hash_buf[i] != std::hash<T>(POISON)) {
            return false;
        }
    }
    return true;
}
