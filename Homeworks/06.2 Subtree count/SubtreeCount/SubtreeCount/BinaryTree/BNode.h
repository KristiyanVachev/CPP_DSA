#pragma once

struct BNode
{
private:
	int _key;

	BNode* _leftChild;
	BNode* _rightChild;

public:
	BNode(int key);
	~BNode();

	int Key();
	BNode* LeftChild();
	BNode* RightChild();

	void SetLeftChild(BNode* node);
	void SetRightChild(BNode* node);
};

inline BNode::BNode(int key)
{
	this->_key = key;

	this->_leftChild = nullptr;
	this->_rightChild = nullptr;
}

inline BNode::~BNode()
{
}

inline int BNode::Key()
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
