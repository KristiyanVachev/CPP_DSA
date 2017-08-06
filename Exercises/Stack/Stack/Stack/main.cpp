// Stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

#include "Stack.h"
#include "TestObject/TrieNode.h"

using namespace std;

int main()
{
	bool isFailing = false;

	TrieNode* value1 = new TrieNode('k');
	TrieNode* value2 = new TrieNode('o');

	Stack<TrieNode> stack;

	if (!stack.IsEmpty())
	{
		cout << "FAIL! must be empty" << endl;
		isFailing = true;
	}

	stack.Add(value1);
	stack.Add(value2);

	if (stack.IsEmpty())
	{
		cout << "FAIL! must not be empty" << endl;
		isFailing = true;
	}

	TrieNode* popped = stack.Pop();

	if (!popped->Character() == 'o')
	{
		cout << "FAIL! wrong element returned" << endl;
		isFailing = true;
	}

	if (!isFailing)
	{
		cout << "All is good!" << endl;
	}

    return 0;
}