#pragma once


#include <iostream>


#include "String.h"


template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node<T>* previous;

	Node(T data);


	template <typename U>
	friend std::ostream& operator<<(std::ostream& outputStream, const Node<U>& node);
};


template <typename T>
Node<T>::Node(T data) {
	this->data = data;
	next = nullptr;
	previous = nullptr;
}


template <typename T>
std::ostream& operator<<(std::ostream& outputStream, const Node<T>& node) {
	outputStream << node.data;
	return outputStream;
}
