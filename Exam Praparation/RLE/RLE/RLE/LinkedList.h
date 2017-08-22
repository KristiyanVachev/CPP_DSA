#pragma once
#include "Node.h"

class LinkedList
{
private:
	Node* _head;
	Node* _tail;

public:
	LinkedList();
	~LinkedList();

	Node* Head();
	Node* Tail();

	void AddTail(char ch, int multiplier = 1);
};

