// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TrieNode.h"
#include "iostream"
#include "Trie.h"

using namespace std;

int main()
{
	////Testing TrieNode
	//TrieNode node = TrieNode('k');
	//TrieNode node2 = TrieNode('o');
	//TrieNode node3 = TrieNode('i');
	
	//node.SetFirstChild(&node2);
	//node2.SetRightSibling(&node3);

	//cout << node.FirstChild()->RightSibling()->Character() << endl;

	Trie trie;

	cout << trie.Start()->Character() << endl;

	TrieNode* node = trie.Add(trie.Start(), 'k');

	cout << node->Character() << endl;

    return 0;
}

