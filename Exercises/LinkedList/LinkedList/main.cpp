// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

#include "Node.h"
#include "LinkedList.h"
#include "Command.h"

using namespace std;

int main()
{
	//Node<int> node = Node<int>(2);
	//Node<int> nodetwo = Node<int>(4);

	//node.SetNext(&nodetwo);

	//cout << node.Value() << endl;
	//cout << node.Next()->Value() << endl;

	//if (node.Next()->Next() == nullptr)
	//{
	//	cout << "koala" << endl;
	//}

	//LinkedList<int> linkedNotes = LinkedList<int>();

	//linkedNotes.AddLast(&node);
	//linkedNotes.AddLast(&nodetwo);

	//cout << linkedNotes.First()->Next()->Value() << endl;

	LinkedList<Command> linkedNodes = LinkedList<Command>();

	Command command = Command('u', 2, 14);
	Command command2 = Command('d', 4, 23);

	linkedNodes.AddTail(&command);

	linkedNodes.AddTail(&command2);

	cout << linkedNodes.Head()->Next()->Value()->getDestination() << endl;

	return 0;
}

