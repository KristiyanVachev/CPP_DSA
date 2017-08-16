#pragma once

struct BNode
{
private:
	long _key;

	BNode* _leftChild;
	BNode* _rightChild;

public:
	BNode(long key);
	~BNode();

	long Key();
	BNode* LeftChild();
	BNode* RightChild();

	void SetLeftChild(BNode* node);
	void SetRightChild(BNode* node);
};

inline BNode::BNode(long key)
{
	this->_key = key;

	this->_leftChild = nullptr;
	this->_rightChild = nullptr;
}

inline BNode::~BNode()
{
}

inline long BNode::Key()
{
	return this->_key;
}

inline BNode* BNode::LeftChild()
{
	return this->_leftChild;
}

inline BNode* BNode::RightChild()
{
	return this->_rightChild;
}

inline void BNode::SetLeftChild(BNode* node)
{
	this->_leftChild = node;
}

inline void BNode::SetRightChild(BNode* node)
{
	this->_rightChild = node;
}
