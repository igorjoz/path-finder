#pragma once


#include <stdexcept>


#include "Vector.h"


class PriorityQueue {
private:
    Vector heap;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    int rightChild(int i) {
        return 2 * i + 2;
    }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }

        if (right < size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }

        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    int size() {
        return heap.size();
    }

    bool isEmpty() {
        return heap.isEmpty();
    }

    int top() {
        if (isEmpty()) {
            throw std::runtime_error("PriorityQueue is empty. Cannot get the top element.");
        }
        return heap[0];
    }

    void push(int value) {
        heap.pushBack(value);
        heapifyUp(size() - 1);
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("PriorityQueue is empty. Cannot pop an element.");
        }
        heap[0] = heap[size() - 1];
        heap.popBack();
        heapifyDown(0);
    }
};
