#pragma once

#include "StackNode.h"

template <typename type> class Stack
{
private:
	StackNode<type>* _top;

public:
	Stack();
	~Stack();

	bool IsEmpty();
	void Add(type* value);
	type* Pop();

};

template <typename type>
Stack<type>::Stack()
{
	this->_top = nullptr;
}

template <typename type>
Stack<type>::~Stack()
{
	StackNode<type>* currentNode = this->_top;

	while (!(currentNode == nullptr))
	{
		StackNode<type>* lowerNode = currentNode->Lower();

		delete currentNode->Value();
		delete currentNode;

		currentNode = lowerNode;
	}
}

template<typename type>
bool Stack<type>::IsEmpty()
{
	return this->_top == nullptr;
}

template<typename type>
void Stack<type>::Add(type* value)
{
	StackNode<type>* newNode = new StackNode<type>(value, this->_top);

	this->_top = newNode;
}

template<typename type>
type* Stack<type>::Pop()
{
	StackNode<type>* node = this->_top;
	type* value = node->Value();

	this->_top = node->Lower();

	delete node;

	return value;
}
