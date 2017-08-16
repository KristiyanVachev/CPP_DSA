/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kristiyan Vachev
* @idnumber 61905
* @task 6.1
* @compiler VS
*
*/

#include "stdafx.h"
#include <iostream>

#include "LinkedList/LinkedList.h"
#include "DynamicArray/DynamicArray.h"

LinkedList<int>* Program(LinkedList<int>* first, LinkedList<int>* second);

int main()
{
	LinkedList<int>* first = new LinkedList<int>();
	first->AddTail(2);
	first->AddTail(5);
	first->AddTail(4);
	first->AddTail(1);
	first->AddTail(3);

	LinkedList<int>* second = new LinkedList<int>();
	second->AddTail(2);
	second->AddTail(4);
	second->AddTail(6);
	
	LinkedList<int>* intersected = Program(first, second);

	//Print the linked list in order
	Node<int>* currNode = intersected->Head();

	while (currNode != nullptr)
	{
		std::cout << currNode->Value() << " ";

		currNode = currNode->Next();
	}

	std::cout << std::endl;

	//Free memory
	delete first;
	delete second;
	delete intersected;

	return 0;
}

LinkedList<int>* Program(LinkedList<int>* first, LinkedList<int>* second)
{
	DynamicArray firstNumbers;

	//Add first list's numbers to an array
	Node<int>* currNode = first->Head();

	while (currNode != nullptr)
	{
		firstNumbers.Add(currNode->Value());

		currNode = currNode->Next();
	}

	//Sort the array to allow for binary search
	firstNumbers.Sort();

	//Array for the intersected numbers
	DynamicArray intersectedNumbers;

	currNode = second->Head();

	while (currNode != nullptr)
	{
		//If a number in the second list is contained in the first save it
		if (firstNumbers.Contains(currNode->Value()))
		{
			intersectedNumbers.Add(currNode->Value());
		}

		currNode = currNode->Next();
	}

	//Sort the intersected numbers and add them to a new linked list
	intersectedNumbers.Sort();

	LinkedList<int>* intersectedList = new LinkedList<int>();

	for (int i = 0; i < intersectedNumbers.Lenght(); i++)
	{
		intersectedList->AddTail(intersectedNumbers.Data()[i]);
	}

	return intersectedList;
}

