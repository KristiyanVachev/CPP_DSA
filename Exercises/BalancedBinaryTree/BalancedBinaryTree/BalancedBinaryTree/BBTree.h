#pragma once

#include "BTNode.h"
#include <vector>;

class BBTree
{
private:
	BTNode* _root;

public:
	BBTree();
	~BBTree();

	BTNode* Root();
};

inline BBTree::BBTree()
{
	this->_root = nullptr;

	//if (start <= end)
	//{
	//	int mid = (start + end + 1) / 2;

	//	*root = CreateBTNode(arr[mid]);
	//	CreateBBTree(&((*root)->left), arr, start, mid - 1);
	//	CreateBBTree(&((*root)->right), arr, mid + 1, end);
	//}
}

inline BBTree::~BBTree()
{
}

inline BTNode* BBTree::Root()
{
	return this->_root;
}
