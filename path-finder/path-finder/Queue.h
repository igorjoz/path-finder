#include <iostream>

struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return (front == nullptr);
    }

    void enqueue(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "The queue is empty. Cannot dequeue." << std::endl;
            return;
        }

        Node* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }
    }

    int getFront() {
        if (isEmpty()) {
            std::cout << "The queue is empty. Cannot get front element." << std::endl;
            return -1;
        }
        return front->data;
    }

    int getRear() {
        if (isEmpty()) {
            std::cout << "The queue is empty. Cannot get rear element." << std::endl;
            return -1;
        }
        return rear->data;
    }


	void print() {
		if (isEmpty()) {
			std::cout << "The queue is empty." << std::endl;
			return;
		}

		Node* current = front;

		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}


	int size() {
		int count = 0;
		Node* current = front;

		while (current != nullptr) {
			count++;
			current = current->next;
		}

		return count;
	}
};
