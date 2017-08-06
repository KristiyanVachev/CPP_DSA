#pragma once

#include "TrieNode.h"
#include "Stack/Stack.h"

class Trie
{
private:
	TrieNode* _start;
	Stack<TrieNode> _nodes;

	TrieNode* Search(TrieNode* node, char ch);

public:
	Trie();
	~Trie();

	TrieNode* Start();
	TrieNode* Add(TrieNode* node, char ch, bool isFinal, int value);
};

inline TrieNode* Trie::Search(TrieNode* node, char ch)
{
	TrieNode* child = node->FirstChild();

	if (child == nullptr)
	{
		return node;
	}

	do
	{
		if (child->Character() == ch)
		{
			return child;
		}

		child = child->RightSibling();
	} while (child != nullptr);

	return node;
}

inline Trie::Trie()
{
	this->_nodes = Stack<TrieNode>();

	TrieNode* node = new TrieNode(' ', false, 0);

	this->_start = node;
}

inline Trie::~Trie()
{
}

inline TrieNode* Trie::Start()
{
	return this->_start;
}

inline TrieNode* Trie::Add(TrieNode* node, char ch, bool isFinal = false, int value = 0)
{
	TrieNode* nextNode = Search(node, ch);

	if (nextNode == node)
	{
		nextNode = new TrieNode(ch, isFinal, value);
		node->AddChild(nextNode);

		this->_nodes.Add(nextNode);
	}
	else
	{
		if (nextNode->IsFinal() != isFinal)
		{
			nextNode->SetIsFinal(isFinal);
		}

		if (nextNode->Value() != value)
		{
			nextNode->SetValue(value);
		}
	}

	return nextNode;
}
