// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TrieNode.h"
#include "iostream"
#include "Trie.h"

using namespace std;

int main()
{
	//---Testing TrieNode
	//TrieNode node = TrieNode('k');
	//TrieNode node2 = TrieNode('o');
	//TrieNode node3 = TrieNode('i');
	
	//node.SetFirstChild(&node2);
	//node2.SetRightSibling(&node3);

	//cout << node.FirstChild()->RightSibling()->Character() << endl;

	//---Testing Trie
	//Trie trie;

	//cout << trie.Start()->Character() << endl;

	//TrieNode* node = trie.Add(trie.Start(), 'k');

	//cout << node->Character() << endl;

	//---Testing trie Add
	Trie trie;

	TrieNode* currNode = trie.Add(trie.Start(), 'k');
	currNode = trie.Add(currNode, 'o');
	currNode = trie.Add(currNode, 'a');
	currNode = trie.Add(currNode, 'l');
	currNode = trie.Add(currNode, 'a', true, 20);

	currNode = trie.Start();

	while (currNode->FirstChild() != nullptr)
	{
		cout << currNode->Character();
		currNode = currNode->FirstChild();
	}
	
	cout << currNode->Character() << ' ' << currNode->Value() << endl;

	currNode = trie.Add(trie.Start(), 'k');
	currNode = trie.Add(currNode, 'o');
	currNode = trie.Add(currNode, 'l');
	currNode = trie.Add(currNode, 'a', true, 20);

	////Must be l
	cout << trie.Start()->FirstChild()->FirstChild()->FirstChild()->RightSibling()->Character();

    return 0;
}

