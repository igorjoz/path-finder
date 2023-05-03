#pragma once


#include <iostream>

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() {}

    Pair(const T1& firstValue, const T2& secondValue) : first(firstValue), second(secondValue) {}

    Pair(const Pair<T1, T2>& other) : first(other.first), second(other.second) {}

    Pair<T1, T2>& operator=(const Pair<T1, T2>& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
};

