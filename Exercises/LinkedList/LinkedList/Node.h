#pragma once

template <typename type> class Node
{
private:
	Node<type>* _nextNode;
	type _value;

public:
	Node<type>(type value);
	~Node();

	void SetValue(type value);
	void SetNext(Node<type>* nextNode);

	Node<type>* Next();
	type Value();
};

template <class type>
Node<type>::Node(type value)
{
	_value = value;
	_nextNode = nullptr;
}

template <typename type>
Node<type>::~Node()
{
}

template <typename type>
void Node<type>::SetValue(type value)
{
	this->_value = value;
}

template <typename type>
void Node<type>::SetNext(Node<type>* nextNode)
{
	this->_nextNode = nextNode;
}

template <typename type>
Node<type>* Node<type>::Next()
{
	return this->_nextNode;
}

template <typename type>
type Node<type>::Value()
{
	return this->_value;
}
