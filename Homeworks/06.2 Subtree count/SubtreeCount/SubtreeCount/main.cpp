/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kristiyan Vachev
* @idnumber 61905
* @task 6.2
* @compiler VS
*
*/

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "BinaryTree/BinaryTree.h"
#include "LinkedList/LinkedList.h"

int main(char argc, char* argv[])
{
	std::string fileName = "input.txt";
	if (argc > 1)
	{
		fileName = argv[1];
	}

	LinkedList<int> numbers;

	//Reading file
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);

		int value;
		while (lineStream >> value)
		{
			numbers.AddTail(value);
		}
	}

	//Create binary tree
	BinaryTree tree;

	Node<int>* currNode = numbers.Head();

	while (currNode != nullptr)
	{
		tree.Add(currNode->Value());

		currNode = currNode->Next();
	}

	//Provide input
	int n;
	std::cin >> n;

	int subTrees = tree.SubTrees(n);

	std::cout << "Subtrees with " << n << " elements: " << subTrees <<std::endl;

	//Rewrite the same file with the save values?

	return 0;
}
