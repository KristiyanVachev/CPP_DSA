/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kristiyan Vachev
* @idnumber 61905
* @task 5
* @compiler VS
*
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "Tree/BinaryTree.h";

bool IsFile(std::string fileName);

int main()
{
	int n = 2;
	std::cin >> n;

	BinaryTree* tree = new BinaryTree();

	//Read first set of numbers and add them inside the tree
	std::string input = "123456.bin";
	std::cin >> input;
	
	if (!IsFile(input))
	{
		std::cout << "Invalid file path" << std::endl;
		delete tree;
		return 1;
	}

	std::ifstream reader(input);
	while (!reader.eof())
	{
		long newNumber = 0;
		reader.read((char*)&newNumber, sizeof(newNumber));

		//EOF reads until it meets a bad character, thus every time reading one more character than necessary
		if (!reader.eof())
		{
			tree->Add(newNumber);
		}
	}

	reader.close();
	--n;

	BinaryTree* intersectedTree = new BinaryTree();

	//Read each next file and save every number that is within the original tree
	while (n > 0)
	{
		input = "4.bin";
		std::cin >> input;

		if (!IsFile(input))
		{
			std::cout << "Invalid file path" << std::endl;
			delete tree;
			delete intersectedTree;
			return 1;
		}

		std::ifstream intersectionReader(input);

		while (!intersectionReader.eof())
		{
			long nextNumber;
			intersectionReader.read((char*)&nextNumber, sizeof(nextNumber));

			//EOF reads until it meets a bad character, thus every time reading one more character than necessary
			if (!intersectionReader.eof())
			{
				if (tree->Search(nextNumber) != nullptr)
				{
					intersectedTree->Add(nextNumber);
				}
			}
		}

		intersectionReader.close();

		delete tree;
		tree = intersectedTree;
		intersectedTree = new BinaryTree();

		--n;
	}

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

bool IsFile(std::string fileName)
{
	char* path = _strdup(fileName.c_str());

	struct stat s;
	if (stat(path, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			return false;
		}
		else if (s.st_mode & S_IFREG)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}