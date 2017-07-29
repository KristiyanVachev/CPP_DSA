// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TrieNode.h"
#include "iostream"

using namespace std;

int main()
{
	TrieNode node = TrieNode('k');
	TrieNode node2 = TrieNode('o');
	TrieNode node3 = TrieNode('i');
	
	node.SetFirstChild(&node2);
	node2.SetRightSibling(&node3);

	cout << node.FirstChild()->RightSibling()->Character() << endl;

    return 0;
}

