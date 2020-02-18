#ifndef INT_INT_H
#define INT_INT_H

#include <cstdlib>

size_t _comparisons = 0;

// Should be constructed with int-like type. Otherwise
template <typename T>
class Int {
    public:
        // Constructors, destructor and copy/move-things
        Int();
        Int(T other_integer);
        operator T();

        ~Int();
        Int(const Int& other_integer);
        Int& operator=(const Int& other_integer);
        Int(Int&& other_integer) noexcept;
        Int& operator=(Int&& other_integer) noexcept;

        // Arithmetics
        Int operator+() const;
        Int operator-() const;
        Int& operator++();
        Int& operator--();
        Int operator++(int);
        Int operator--(int);


        template <typename T_>
        friend const Int<T_> operator+(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend const Int<T_> operator-(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend const Int<T_> operator*(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend const Int<T_> operator/(const Int<T_>& lhv, const Int<T_>& rhv);

        // Comparison operators
        template <typename T_>
        friend bool operator==(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend bool operator!=(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend bool operator<(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend bool operator>(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend bool operator<=(const Int<T_>& lhv, const Int<T_>& rhv);

        template <typename T_>
        friend bool operator>=(const Int<T_>& lhv, const Int<T_>& rhv);

    private:
        T int_;
};

template <typename T>
Int<T>::Int() {
    int_ = 0;
}

template <typename T>
Int<T>::Int(T other_integer) {
    int_ = other_integer;
}

template <typename T>
Int<T>::operator T() {
    return T(int_);
}

template <typename T>
Int<T>::~Int() {

}

template <typename T>
Int<T>::Int(const Int<T>& other_integer) {
    int_ = other_integer.int_;
}

template <typename T>
Int<T>& Int<T>::operator=(const Int<T>& other_integer) {
    if (&other_integer == this) {
        return *this;
    }
    int_ = other_integer.int_;
    return *this;
}

template <typename T>
Int<T>::Int(Int<T>&& other_integer) noexcept {
    int_ = other_integer.int_;
}

template <typename T>
Int<T>& Int<T>::operator=(Int<T>&& other_integer) noexcept {
    if (&other_integer == this) {
        return *this;
    }
    int_ = other_integer.int_;
    return *this;
}

template <typename T>
Int<T> Int<T>::operator+() const {
    return Int<T>(int_);
}

template <typename T>
Int<T> Int<T>::operator-() const {
    return Int<T>(-int_);
}

template <typename T>
Int<T>& Int<T>::operator++() {
    ++int_;
    return this;
}

template <typename T>
Int<T>& Int<T>::operator--() {
    --int_;
    return this;
}

template <typename T>
Int<T> Int<T>::operator++(int) {
    T temp = int_;
    ++int_;
    return Int<T>(temp);
}

template <typename T>
Int<T> Int<T>::operator--(int) {
    T temp = int_;
    --int_;
    return Int<T>(temp);
}

template <typename T>
const Int<T> operator+(const Int<T>& lhv, const Int<T>& rhv) {
    return Int<T>(lhv.int_ + rhv.int_);
}

template <typename T>
const Int<T> operator-(const Int<T>& lhv, const Int<T>& rhv) {
    return Int<T>(lhv.int_ - rhv.int_);
}

template <typename T>
const Int<T> operator*(const Int<T>& lhv, const Int<T>& rhv) {
    return Int<T>(lhv.int_ * rhv.int_);
}

template <typename T>
const Int<T> operator/(const Int<T>& lhv, const Int<T>& rhv) {
    return Int<T>(lhv.int_ / rhv.int_);
}

template <typename T>
bool operator==(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ == rhv.int_;
}

template <typename T>
bool operator!=(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ != rhv.int_;
}

template <typename T>
bool operator<(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ < rhv.int_;
}

template <typename T>
bool operator>(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ > rhv.int_;
}

template <typename T>
bool operator<=(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ <= rhv.int_;
}

template <typename T>
bool operator>=(const Int<T>& lhv, const Int<T>& rhv) {
    ++_comparisons;
    return lhv.int_ >= rhv.int_;
}


#endif //INT_INT_H
