#pragma once

class Node
{
private:
	int value;
	Node* leftChild;
	Node* rightChild;
public:
	Node(int value);
	~Node();

	void SetLeft(Node* node);
	void SetRight(Node* node);

	int Value() const;
	Node* Left() const;
	Node* Right() const;
};

inline Node::Node(int value)
{
	this->value = value;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

inline Node::~Node()
{

}

inline void Node::SetLeft(Node* node)
{
	this->leftChild = node;
}

inline void Node::SetRight(Node* node)
{
	this->rightChild = node;
}

inline int Node::Value() const
{
	return this->value;
}

inline Node* Node::Left() const
{
	return this->leftChild;
}

inline Node* Node::Right() const
{
	return this->rightChild;
}
