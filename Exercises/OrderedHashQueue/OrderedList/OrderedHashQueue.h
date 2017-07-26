#pragma once
#include "Node.h"

//At least the name is descriptive enough
template <typename type> class OrderedHashQueue
{
private:
	bool _isAscending;
	Node<type>* _head;

	void Remove();

public:
	OrderedHashQueue(bool isAscending);
	~OrderedHashQueue();

	type Pop();
	void Add(type data);
};

template <typename type>
OrderedHashQueue<type>::OrderedHashQueue(bool isAscending)
{
	this->_isAscending = isAscending;
	this->_head = nullptr;
}

template <typename type>
OrderedHashQueue<type>::~OrderedHashQueue()
{
	if (this->_head == nullptr)
	{
		return;
	}

	Node<type>* currNode = this->_head;
	Node<type>* nextNode;

	do
	{
		nextNode = currNode->Next();
		delete currNode;
		currNode = nextNode;
	} while (nextNode != nullptr);
}

template <typename type>
type OrderedHashQueue<type>::Pop()
{
	type value = this->_head->Value();

	this->Remove();
	
	return value;
}

template <typename type>
void OrderedHashQueue<type>::Add(type data)
{
	if (this->_head == nullptr)
	{
		Node<type>* newNode = new Node<type>(data);

		this->_head = newNode;

		return;
	}

	Node<type>* currentNode = this->_head;
	Node<type>* previousNode = nullptr;

	do
	{
		if ((_isAscending && currentNode->Value() >= data) || (!_isAscending && currentNode->Value() <= data))
		{
			if (currentNode->Value() == data)
			{
				return;
			}

			Node<type>* newNode = new Node<type>(data);

			if (previousNode == nullptr)
			{
				this->_head = newNode;
			}
			else
			{
				previousNode->SetNext(newNode);
			}

			newNode->SetNext(currentNode);
			return;
		}

		previousNode = currentNode;
		currentNode = currentNode->Next();
	} while (currentNode != nullptr);

	Node<type>* newNode = new Node<type>(data);
	previousNode->SetNext(newNode);
}

template <typename type>
void OrderedHashQueue<type>::Remove()
{
	Node<type>* node = this->_head;

	this->_head = this->_head->Next();
	delete node;
}
