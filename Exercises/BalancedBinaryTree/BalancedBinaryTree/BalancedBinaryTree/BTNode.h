#pragma once

#include <string>

struct BTNode
{
private:
	int _key;
	std::string _data;

	BTNode* _leftChild;
	BTNode* _rightChild;

public:
	BTNode(int key, std::string data);
	~BTNode();

	int Key();
	std::string Data();
	BTNode* LeftChild();
	BTNode* RightChild();

	void SetLeftChild(BTNode* node);
	void SetRightChild(BTNode* node);
};

inline BTNode::BTNode(int key, std::string data)
{
	this->_key = key;
	this->_data = data;

	this->_leftChild = nullptr;
	this->_rightChild = nullptr;
}

inline BTNode::~BTNode()
{
}

inline int BTNode::Key()
{
	return this->_key;
}

inline std::string BTNode::Data()
{
	return this->_data;
}

inline BTNode* BTNode::LeftChild()
{
	return this->_leftChild;
}

inline BTNode* BTNode::RightChild()
{
	return this->_rightChild;
}

inline void BTNode::SetLeftChild(BTNode* node)
{
	this->_leftChild = node;
}

inline void BTNode::SetRightChild(BTNode* node)
{
	this->_rightChild = node;
}
