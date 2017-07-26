#pragma once

template <typename type> class ListNode
{
private:
	ListNode<type>* _nextNode;
	type* _value;

public:
	ListNode<type>(type* value);
	~ListNode();

	void SetValue(type* value);
	void SetNext(ListNode<type>* nextNode);

	ListNode<type>* Next();
	type* Value();
};

template <class type>
ListNode<type>::ListNode(type* value)
{
	_value = value;
	_nextNode = nullptr;
}

template <typename type>
ListNode<type>::~ListNode()
{
	//TODO: Delete only if value is initialized with new.
	//delete this->_value;
}

template <typename type>
void ListNode<type>::SetValue(type* value)
{
	this->_value = value;
}

template <typename type>
void ListNode<type>::SetNext(ListNode<type>* nextNode)
{
	this->_nextNode = nextNode;
}

template <typename type>
ListNode<type>* ListNode<type>::Next()
{
	return this->_nextNode;
}

template <typename type>
type* ListNode<type>::Value()
{
	return this->_value;
}
