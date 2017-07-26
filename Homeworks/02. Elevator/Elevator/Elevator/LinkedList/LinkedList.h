#pragma once
#include "ListNode.h"

template <typename type> class LinkedList
{
private:
	ListNode<type>* _head;
	ListNode<type>* _tail;

public:
	LinkedList();
	~LinkedList();

	ListNode<type>* Head();
	void AddTail(type* data);
	void Remove(ListNode<type>* node);
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
	if (this->Head() == nullptr)
	{
		return;
	}

	ListNode<type>* currNode = this->Head();
	ListNode<type>* nextNode;

	do
	{
		nextNode = currNode->Next();
		delete currNode;
		currNode = nextNode;
	} while (nextNode != nullptr);	
}

template <typename type>
ListNode<type>* LinkedList<type>::Head()
{
	return this->_head;
}

template <typename type>
void LinkedList<type>::AddTail(type* data)
{
	ListNode<type>* newNode = new ListNode<type>(data);

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

template <typename type>
void LinkedList<type>::Remove(ListNode<type>* node)
{
	if (node == this->Head())
	{
		this->_head = this->Head()->Next();
		delete node;
		return;
	}

	ListNode<type>* currentNode = this->Head();

	while (currentNode->Next() != nullptr)
	{
		if (currentNode->Next() == node)
		{
			if (node == this->_tail)
			{
				this->_tail = currentNode;
				currentNode->SetNext(nullptr);
			}
			else
			{
				currentNode->SetNext(node->Next());
			}

			delete node;
			return;
		}

		currentNode = currentNode->Next();
	}
}
