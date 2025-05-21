#include <iostream>
#include <cassert>

template <typename Derived>
class less_than_comparable {
public:
    friend bool operator>(const Derived& lhs, const Derived& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Derived& lhs, const Derived& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs) && !(rhs < lhs);
    }

    friend bool operator!=(const Derived& lhs, const Derived& rhs) {
        return !(lhs == rhs);
    }
};

template <typename Derived>
class counter {
    inline static int count_ = 0;
public:
    counter() { ++count_; }
    counter(const counter&) { ++count_; }
    counter(counter&&) noexcept { ++count_; }

    ~counter() { --count_; }

    static int count() { return count_; }
};

class Number : public less_than_comparable<Number>, public counter<Number> {
    int m_value;
public:
    Number(int value) : m_value{value} {}

    int value() const { return m_value; }

    bool operator<(const Number& other) const {
        return m_value < other.m_value;
    }
};
