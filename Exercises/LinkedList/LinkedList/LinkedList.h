#pragma once
#include "Node.h"

template <typename type> class LinkedList
{
private:
	Node<type>* _first;
	Node<type>* _last;

public:
	LinkedList();
	~LinkedList();

	Node<type>* First();
	void AddLast(Node<type>* node);
};

template <typename type>
LinkedList<type>::LinkedList()
{
	this->_first = nullptr;
	this->_last = nullptr;
}

template <typename type>
LinkedList<type>::~LinkedList()
{
}

template <typename type>
Node<type>* LinkedList<type>::First()
{
	return this->_first;
}

template <typename type>
void LinkedList<type>::AddLast(Node<type>* node)
{
	if (this->_first == nullptr)
	{
		this->_first = node;
		this->_last = node;
	}
	else
	{
		this->_last->SetNext(node);
		this->_last = node;
	}
}
