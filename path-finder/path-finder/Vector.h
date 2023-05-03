#pragma once


#include <iostream>
#include <stdexcept>

class Vector {
private:
    int* data;
    int capacity;
    int count;

    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        
        for (int i = 0; i < count; ++i) {
			newData[i] = data[i];
        }
        
        delete[] data;
        
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector(int initialCapacity = 4) {
        data = new int[initialCapacity];
        capacity = initialCapacity;
        count = 0;
    }

    ~Vector() {
        delete[] data;
    }

    int& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    int size() {
        return count;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return count == 0;
    }

    void pushBack(int value) {
        if (count == capacity) {
            resize(2 * capacity);
        }
        data[count++] = value;
    }

    void popBack() {
        if (isEmpty()) {
            throw std::runtime_error("Vector is empty. Cannot remove an element.");
        }
        --count;
    }

    void clear() {
        count = 0;
    }
};