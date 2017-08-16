#pragma once

#include "BNode.h"

class BinaryTree
{
private:
	BNode* _root;
	int _nSubTreesCount;

	void Free(BNode* currNode);
	int SubTreeCount(BNode* currNode, int n);

public:
	BinaryTree();
	~BinaryTree();

	BNode* Root();
	BNode* Search(int key);
	void Add(int key);
	int SubTrees(int n);
};

inline void BinaryTree::Free(BNode* currNode)
{
	BNode* leftChild = currNode->LeftChild();
	BNode* rightChild = currNode->RightChild();

	delete currNode;

	if (leftChild != nullptr)
	{
		Free(leftChild);
	}

	if (rightChild != nullptr)
	{
		Free(rightChild);
	}
}

inline int BinaryTree::SubTreeCount(BNode* currNode, int n)
{
	int subTreeCount = 1;

	if (currNode->LeftChild() != nullptr)
	{
		subTreeCount += SubTreeCount(currNode->LeftChild(), n);
	}

	if (currNode->RightChild() != nullptr)
	{
		subTreeCount += SubTreeCount(currNode->RightChild(), n);
	}

	if (subTreeCount == n)
	{
		this->_nSubTreesCount++;
	}

	return subTreeCount;
}

inline BinaryTree::BinaryTree()
{
	this->_root = nullptr;
}

inline BinaryTree::~BinaryTree()
{
	Free(this->_root);
}

inline BNode* BinaryTree::Root()
{
	return this->_root;
}

inline BNode* BinaryTree::Search(int key)
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

inline void BinaryTree::Add(int key)
{
	BNode* parent = this->_root;
	BNode* currNode = this->_root;

	while (currNode != nullptr)
	{
		parent = currNode;

		//Key already exists
		if (currNode->Key() == key)
		{
			return;
		}

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

inline int BinaryTree::SubTrees(int n)
{
	this->_nSubTreesCount = 0;

	SubTreeCount(this->_root, n);

	return this->_nSubTreesCount;
}
