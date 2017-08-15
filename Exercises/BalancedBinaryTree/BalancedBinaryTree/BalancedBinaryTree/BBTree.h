#pragma once

#include "BTNode.h"
#include "DynamicArray/DynamicArray.h"

class BBTree
{
private:
	BTNode* _root;

	BTNode* Seed(DynamicArray* arr, int start, int end);

public:
	BBTree(DynamicArray* arr);
	~BBTree();

	bool Search(int key, std::string data);
	void Add(int key, std::string data);
};

inline BTNode* BBTree::Seed(DynamicArray* arr, int start, int end)
{
	if (start <= end)
	{
		int mid = (start + end + 1) / 2;

		//In case there is a key equal to the current, it must go on the right, unballancing it a bit
		while (mid > 0 && arr->Data()[mid]->Key() == arr->Data()[mid - 1]->Key())
		{
			if (mid - 1 < start)
			{
				break;
			}

			mid--;
		}

		BTNode* currNode = new BTNode(arr->Data()[mid]->Key(), arr->Data()[mid]->Value());

		currNode->SetLeftChild(Seed(arr, start, mid - 1));
		currNode->SetRightChild(Seed(arr, mid + 1, end));

		return currNode;
	}

	return nullptr;
}

inline BBTree::BBTree(DynamicArray* arr)
{
	this->_root = Seed(arr, 0, arr->Lenght() - 1);
}

inline BBTree::~BBTree()
{
}

inline bool BBTree::Search(int key, std::string data)
{
	BTNode* currNode = this->_root;

	while (currNode != nullptr)
	{
		if (currNode->Key() == key && currNode->Data() == data)
		{
			return true;
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

	return false;
}

inline void BBTree::Add(int key, std::string data)
{
	BTNode* parent = this->_root;
	BTNode* currNode = this->_root;

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

	BTNode* newNode = new BTNode(key, data);

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
