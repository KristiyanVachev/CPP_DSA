#pragma once
#include "Node.h"

template <typename type> class LinkedList
{
private:
	Node<type>* _head;
	Node<type>* _tail;

public:
	LinkedList();
	~LinkedList();

	Node<type>* Head();
	void AddTail(type* data);
};

template <typename type>
LinkedList<type>::LinkedList()
{
	this->_head = nullptr;
	this->_tail = nullptr;
}

template <typename type>
LinkedList<type>::~LinkedList()
{
}

template <typename type>
Node<type>* LinkedList<type>::Head()
{
	return this->_head;
}

template <typename type>
void LinkedList<type>::AddTail(type* data)
{
	Node<type>* newNode = new Node<type>(data);

	if (this->_head == nullptr)
	{
		this->_head = newNode;
		this->_tail = newNode;
	}
	else
	{
		this->_tail->SetNext(newNode);
		this->_tail = newNode;
	}
}
