#pragma once

template <typename type> class StackNode
{
private:
	StackNode<type>* _lowerNode;
	type* _value;

public:
	StackNode<type>(type* value, StackNode<type>* lower);
	~StackNode();
	
	StackNode<type>* Lower();
	type* Value();
};

template <class type>
StackNode<type>::StackNode(type* value, StackNode<type>* lower)
{
	_value = value;
	_lowerNode = lower;
}

template <typename type>
StackNode<type>::~StackNode()
{

}


template <typename type>
StackNode<type>* StackNode<type>::Lower()
{
	return this->_lowerNode;
}

template <typename type>
type* StackNode<type>::Value()
{
	return this->_value;
}
