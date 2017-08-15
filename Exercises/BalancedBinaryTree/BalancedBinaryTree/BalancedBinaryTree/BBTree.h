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
};

inline BTNode* BBTree::Seed(DynamicArray* arr, int start, int end)
{
	if (start <= end)
	{
		int mid = (start + end + 1) / 2;

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

