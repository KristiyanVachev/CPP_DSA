#pragma once

class TrieNode
{
private:
	char _ch;
	bool _isFinal;
	int _value;
	TrieNode* _rightSibling;
	TrieNode* _firstChild;
	TrieNode* _lastChild;

public:
	TrieNode(char ch, bool isFinal, int value);
	~TrieNode();

	char Character();
	bool IsFinal();
	int Value();
	TrieNode* RightSibling();
	TrieNode* FirstChild();

	void SetIsFinal(bool isFinal);
	void SetValue(int value);
	void SetRightSibling(TrieNode* node);
	void AddChild(TrieNode* node);

};

inline TrieNode::TrieNode(char ch, bool isFinal = false, int value = 0)
{
	this->_ch = ch;
	this->_isFinal = isFinal;
	this->_value = value;

	this->_rightSibling = nullptr;
	this->_firstChild = nullptr;
	this->_lastChild= nullptr;
}

inline TrieNode::~TrieNode()
{
}

inline char TrieNode::Character()
{
	return this->_ch;
}

inline bool TrieNode::IsFinal()
{
	return this->_isFinal;
}

inline int TrieNode::Value()
{
	return this->_value;
}

inline TrieNode* TrieNode::RightSibling()
{
	return this->_rightSibling;
}

inline TrieNode* TrieNode::FirstChild()
{
	return this->_firstChild;
}


inline void TrieNode::SetIsFinal(bool isFinal)
{
	this->_isFinal = isFinal;
}

inline void TrieNode::SetValue(int value)
{
	this->_value = value;
}

inline void TrieNode::SetRightSibling(TrieNode* node)
{
	this->_rightSibling = node;
}

inline void TrieNode::AddChild(TrieNode* node)
{
	if (this->_firstChild == nullptr)
	{
		this->_firstChild = node;
		this->_lastChild = node;

		return;
	}

	this->_lastChild->SetRightSibling(node);
	this->_lastChild = node;
}
