#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

#include "Tree/BinaryTree.h";

int main()
{
	int n;
	std::cin >> n;

	BinaryTree* tree = new BinaryTree();
	//tree->Add(2);
	//tree->Add(5);
	//tree->Add(3);
	//tree->Add(4);
	//tree->Add(1);
	//tree->Add(6);

	//Read first set of numbers and add them inside the tree
	std::string input;
	std::cin >> input;
	std::ifstream reader(input);
	while (!reader.eof())
	{
		long newNumber = 0;
		reader.read((char*)&newNumber, sizeof(newNumber));

		tree->Add(newNumber);
	}

	reader.close();
	--n;

	BinaryTree* intersectedTree = new BinaryTree();

	//Read each next file and save every number that is within the original tree
	while (n > 0)
	{
		std::ifstream reader(input);

		while (!reader.eof())
		{
			long nextNumber = 0;
			reader.read((char*)&nextNumber, sizeof(nextNumber));

			if (tree->Search(nextNumber) != nullptr)
			{
				intersectedTree->Add(nextNumber);
			}
		}

		reader.close();

		delete tree;
		tree = intersectedTree;
		intersectedTree = new BinaryTree();

		--n;
	}

	//intersectedTree->Add(4);
	//delete tree;
	//tree = intersectedTree;

	//Write each number into the file
	std::ofstream writer("result.bin", std::ios::binary);

	while (!tree->Nodes()->IsEmpty())
	{
		BNode* currentNode = tree->Nodes()->Pop();
		long number = currentNode->Key();
		writer.write((char*)&number, sizeof(long));
	}

	writer.close();
	delete tree;

	return 0;
}

