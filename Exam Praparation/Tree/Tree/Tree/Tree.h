#pragma once
#include "Node.h"

class Tree
{
private:
	Node* root;

public:
	Tree();
	~Tree();

	void Add(int value);
};

inline Tree::Tree()
{
	this->root = nullptr;
}

inline Tree::~Tree()
{

}

inline void Tree::Add(int value)
{
	Node* newNode = new Node(value);

	if (this->root == nullptr)
	{
		this->root = newNode;
		return;
	}

	Node* currNode = this->root;

	while (currNode != nullptr)
	{
		if (currNode->Value() > value)
		{
			if (currNode->Left() == nullptr)
			{
				currNode->SetLeft(newNode);
				return;
			}

			currNode = currNode->Left();
		}
		else
		{
			if (currNode->Right() == nullptr )
			{
				currNode->SetRight(newNode);
				return;
			}

			currNode = currNode->Right();
		}
	}
}
