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
