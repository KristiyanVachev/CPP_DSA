#include "stdafx.h"
#include "LinkedList.h"


LinkedList::LinkedList()
{
	this->_head = nullptr;
	this->_tail = nullptr;
}


LinkedList::~LinkedList()
{
}

Node* LinkedList::Head()
{
	return this->_head;
}

Node* LinkedList::Tail()
{
	return this->_tail;
}

void LinkedList::AddTail(char ch, int multiplier)
{
	Node* newNode = new Node(ch);

	if (this->_head == nullptr)
	{
		this->_head = newNode;
		this->_tail = newNode;
	}

	this->_tail->SetNext(newNode);
	this->_tail = newNode;
}
