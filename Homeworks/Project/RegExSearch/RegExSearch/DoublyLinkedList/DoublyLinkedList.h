#pragma once
#include "DLNode.h"

template <typename type> class DoublyLinkedList
{
private:
	DLNode<type>* _head;
	DLNode<type>* _tail;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	DLNode<type>* Head();
	DLNode<type>* Tail();
	void AddTail(type* data);
	void Remove(DLNode<type>* node);
};

template <typename type>
DoublyLinkedList<type>::DoublyLinkedList()
{
	this->_head = nullptr;
	this->_tail = nullptr;
}

template <typename type>
DoublyLinkedList<type>::~DoublyLinkedList()
{
	if (this->Head() == nullptr)
	{
		return;
	}

	DLNode<type>* currNode = this->Head();
	DLNode<type>* nextNode;

	do
	{
		nextNode = currNode->Next();
		delete currNode;
		currNode = nextNode;
	} while (nextNode != nullptr);	
}

template <typename type>
DLNode<type>* DoublyLinkedList<type>::Head()
{
	return this->_head;
}

template <typename type>
DLNode<type>* DoublyLinkedList<type>::Tail()
{
	return this->_tail;
}

template <typename type>
void DoublyLinkedList<type>::AddTail(type* data)
{
	DLNode<type>* newNode = new DLNode<type>(data);

	if (this->_head == nullptr)
	{
		this->_head = newNode;
		this->_tail = newNode;
	}
	else
	{
		this->_tail->SetNext(newNode);
		newNode->SetPrevious(this->_tail);

		this->_tail = newNode;
	}
}

template <typename type>
void DoublyLinkedList<type>::Remove(DLNode<type>* node)
{
	if (node == this->Head())
	{
		if (this->Head()->Next() == nullptr)
		{
			this->_head = nullptr;
			this->_tail = nullptr;
		}
		else
		{
			this->_head = node->Next();
			this->_head->SetPrevious(nullptr);
		}

		delete node;

		return;
	}

	if (node == this->_tail)
	{
		this->_tail = node->Previous();
		this->_tail->SetNext(nullptr);

		delete node;

		return;
	}

	node->Previous()->SetNext(node->Next());
	node->Next()->SetPrevious(node->Previous());

	delete node;
}
