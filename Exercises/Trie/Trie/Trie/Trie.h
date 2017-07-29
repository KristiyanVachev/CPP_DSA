#pragma once

#include "TrieNode.h"

class Trie
{
private:
	TrieNode* _start;

public:
	Trie();
	~Trie();

	TrieNode* Start();
	TrieNode* Add(TrieNode* node, char ch, bool isFinal, int value);
};

inline Trie::Trie()
{
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
	TrieNode* newNode = new TrieNode(ch, isFinal, value);

	node->SetFirstChild(newNode);

	return newNode;
}
