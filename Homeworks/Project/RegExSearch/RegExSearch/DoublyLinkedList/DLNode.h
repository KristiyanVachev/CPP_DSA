#pragma once

template <typename type> class DLNode
{
private:
	DLNode<type>* _nextNode;
	DLNode<type>* _previousNode;

	type* _value;

public:
	DLNode<type>(type* value);
	~DLNode();

	void SetValue(type* value);
	void SetNext(DLNode<type>* nextNode);
	void SetPrevious(DLNode<type>* previousNode);

	DLNode<type>* Next();
	DLNode<type>* Previous();
	type* Value();
};

template <class type>
DLNode<type>::DLNode(type* value)
{
	this->_value = value;
	this->_nextNode = nullptr;
	this->_previousNode = nullptr;
}

template <typename type>
DLNode<type>::~DLNode()
{
	//TODO: Delete only if value is initialized with new.
	//delete this->_value;
}

template <typename type>
void DLNode<type>::SetValue(type* value)
{
	this->_value = value;
}

template <typename type>
void DLNode<type>::SetNext(DLNode<type>* nextNode)
{
	this->_nextNode = nextNode;
}

template <typename type>
void DLNode<type>::SetPrevious(DLNode<type>* previousNode)
{
	this->_previousNode = previousNode;
}

template <typename type>
DLNode<type>* DLNode<type>::Next()
{
	return this->_nextNode;
}

template <typename type>
DLNode<type>* DLNode<type>::Previous()
{
	return this->_previousNode;
}

template <typename type>
type* DLNode<type>::Value()
{
	return this->_value;
}
