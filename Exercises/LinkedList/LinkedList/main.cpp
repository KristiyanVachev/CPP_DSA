// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "Node.h"
#include "LinkedList.h"

using namespace std;

int main()
{
	Node<int> node = Node<int>(2);
	Node<int> nodetwo = Node<int>(4);

	node.SetNext(&nodetwo);

	cout << node.Value() << endl;
	cout << node.Next()->Value() << endl;

	if (node.Next()->Next() == nullptr)
	{
		cout << "koala" << endl;
	}

	LinkedList<int> linkedNotes = LinkedList<int>();

	linkedNotes.AddLast(&node);

	cout << linkedNotes.First()->Value() << endl;

    return 0;
}

