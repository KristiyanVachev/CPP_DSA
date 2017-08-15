#pragma once

#include "BTNode.h"
#include "DynamicArray/DynamicArray.h"

class BBTree
{
private:
	BTNode* _root;

	BTNode* Seed(DynamicArray* arr, int start, int end);
	void Free(BTNode* currNode);

public:
	BBTree(DynamicArray* arr);
	~BBTree();

	BTNode* Search(int key, std::string data);
	void Add(int key, std::string data);
	bool Remove(int key, std::string data, bool noData);
	int RemoveAll(int key);
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

inline void BBTree::Free(BTNode* currNode)
{
	BTNode* leftChild = currNode->LeftChild();
	BTNode* rightChild = currNode->RightChild();

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

inline BBTree::BBTree(DynamicArray* arr)
{
	this->_root = Seed(arr, 0, arr->Lenght() - 1);
}

inline BBTree::~BBTree()
{
	Free(this->_root);
}

inline BTNode* BBTree::Search(int key, std::string data)
{
	BTNode* currNode = this->_root;

	while (currNode != nullptr)
	{
		if (currNode->Key() == key && currNode->Data() == data)
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

inline bool BBTree::Remove(int key, std::string data, bool noData = false)
{
	BTNode* parent = nullptr;
	BTNode* currNode = this->_root;
	BTNode* nodeToRemove = nullptr;

	//Find nodeToRemove and it's parent
	while (currNode != nullptr)
	{
		if (currNode->Key() == key && currNode->Data() == data || noData && currNode->Key() == key)
		{
			nodeToRemove = currNode;
			break;
		}

		parent = currNode;

		if (currNode->Key() > key)
		{
			currNode = currNode->LeftChild();
		}
		else
		{
			currNode = currNode->RightChild();
		}
	}

	//Return if not found
	if (nodeToRemove == nullptr)
	{
		return false;
	}

	//If nodeToRemove has no children, just delete it
	if (nodeToRemove->LeftChild() == nullptr && nodeToRemove->RightChild() == nullptr) {
		if (parent->LeftChild() == nodeToRemove)
		{
			parent->SetLeftChild(nullptr);
		}
		else
		{
			parent->SetRightChild(nullptr);
		}
	}
	//IF nodeToRemove has a left or right child set it in its place
	else if (nodeToRemove->RightChild() == nullptr) {
		if (parent->LeftChild() == nodeToRemove)
		{
			parent->SetLeftChild(nodeToRemove->LeftChild());
		}
		else
		{
			parent->SetRightChild(nodeToRemove->LeftChild());
		}

	}
	else if (nodeToRemove->LeftChild() == nullptr) {
		if (parent->LeftChild() == nodeToRemove)
		{
			parent->SetLeftChild(nodeToRemove->RightChild());
		}
		else
		{
			parent->SetRightChild(nodeToRemove->RightChild());
		}
	}
	else
	{
		//Find the smallest element after nodeToRemove
		BTNode* leftMostParent = currNode->RightChild();
		BTNode* leftMost = nodeToRemove->RightChild()->LeftChild();

		while (leftMost->LeftChild() != nullptr)
		{
			leftMostParent = leftMost;
			leftMost = leftMost->LeftChild();
		}

		//Set leftmost's parent to have the leftmost's child
		leftMostParent->SetLeftChild(leftMost->RightChild());

		//Put in in the place of the node to be removed
		leftMost->SetLeftChild(nodeToRemove->LeftChild());
		leftMost->SetRightChild(nodeToRemove->RightChild());

		//Place leftMost in it's new parent's care
		if (parent == nullptr)
		{
			this->_root = leftMost;
		}
		else
		{
			if (nodeToRemove->Key() < parent->Key())
			{
				parent->SetLeftChild(leftMost);
			}
			else
			{
				parent->SetRightChild(leftMost);
			}
		}
	}

	delete nodeToRemove;
	nodeToRemove = nullptr;
}

inline int BBTree::RemoveAll(int key)
{
	int removed = 0;

	while (this->Remove(key, "", true))
	{
		removed++;
	}

	return removed;
}
