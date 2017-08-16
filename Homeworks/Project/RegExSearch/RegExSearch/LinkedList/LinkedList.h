#pragma once
#include "Node.h"

//Manually tested here - https://github.com/KristiyanVachev/CPP_DSA/blob/master/Exercises/LinkedList/LinkedList/main.cpp

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
	void Remove(Node<type>* node);
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

	Node<type>* currNode = this->Head();
	Node<type>* nextNode;

	do
	{
		nextNode = currNode->Next();
		delete currNode;
		currNode = nextNode;
	} while (nextNode != nullptr);	
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

template <typename type>
void LinkedList<type>::Remove(Node<type>* node)
{
	if (node == this->Head())
	{
		this->_head = this->Head()->Next();
		delete node;
		return;
	}

	Node<type>* currentNode = this->Head();

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
