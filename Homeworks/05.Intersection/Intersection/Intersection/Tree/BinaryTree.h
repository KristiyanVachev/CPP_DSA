#pragma once

#include "BNode.h"
#include "Stack/Stack.h"

class BinaryTree
{
private:
	BNode* _root;
	
	Stack<BNode>* _nodes;

public:
	BinaryTree();
	~BinaryTree();

	BNode* Root();
	Stack<BNode>* Nodes();
	BNode* Search(long key);
	void Add(long key);
};

inline BinaryTree::BinaryTree()
{
	this->_root = nullptr;
	this->_nodes = new Stack<BNode>();
}

inline BinaryTree::~BinaryTree()
{
	delete this->_nodes;
}

inline BNode* BinaryTree::Root()
{
	return this->_root;
}

inline Stack<BNode>* BinaryTree::Nodes()
{
	return this->_nodes;
}

inline BNode* BinaryTree::Search(long key)
{
	BNode* currNode = this->_root;

	while (currNode != nullptr)
	{
		if (currNode->Key() == key)
		{
			return currNode;
		}

		if (currNode->Key() > key)
		{
			currNode = currNode->LeftChild();
		}
		else
		{
			currNode = currNode->RightChild();
		}
	}

	return nullptr;
}

inline void BinaryTree::Add(long key)
{
	BNode* parent = this->_root;
	BNode* currNode = this->_root;

	while (currNode != nullptr)
	{
		parent = currNode;

		if (key < currNode->Key())
		{
			currNode = currNode->LeftChild();
		}
		else
		{
			currNode = currNode->RightChild();
		}
	}

	BNode* newNode = new BNode(key);
	this->_nodes->Add(newNode);

	if (parent == nullptr)
	{
		this->_root = newNode;
		return;
	}

	if (key < parent->Key())
	{
		parent->SetLeftChild(newNode);
	}
	else
	{
		parent->SetRightChild(newNode);
	}
}