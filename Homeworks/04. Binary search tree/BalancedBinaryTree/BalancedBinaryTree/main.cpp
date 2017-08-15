/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kristiyan Vachev
* @idnumber 61905
* @task 4
* @compiler VS
*
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

//Dynamic array is tested here: https://github.com/KristiyanVachev/CPP_DSA/blob/master/Exercises/DynamicArray/DynamicArray/DynamicArray/main.cpp
//Merge sort is tested here: https://github.com/KristiyanVachev/CPP_DSA/blob/master/Exercises/MergeSort/MergeSort/MergeSort/main.cpp
#include "DynamicArray/DynamicArray.h"
//BBTree is tested here: https://github.com/KristiyanVachev/CPP_DSA/blob/master/Exercises/BalancedBinaryTree/BalancedBinaryTree/BalancedBinaryTree/main.cpp
#include "BBTree/BBTree.h"

int main(int argc, char** argv)
{
	//Read input file
	char* fileName = "file.txt";

	if (argc > 1)
	{
		fileName = argv[1];
	}

	DynamicArray* arr = new DynamicArray;

	std::ifstream reader(fileName);

	while (!reader.eof())
	{
		int key;
		reader.read((char*)&key, sizeof(key));

		int size = 0;
		reader.read((char*)&size, sizeof(size));

		char *line = new char[size + 1];
		reader.read(line, size);

		line[size] = '\0';

		if (line[0] != '\0')
		{
			arr->Add(key, line);
		}
	}

	//Sort input
	arr->Sort();

	//Construct balanced binary tree with the input
	BBTree* tree = new BBTree(arr);

	//Delete input
	delete arr;

	//Parsing commands
	//Code for parsing commands is taken from Ivan Mladenov
	std::string input;
	while (std::getline(std::cin, input))
	{
		if (input[0] == 'a')
		{
			std::string stringifiedKey = "";
			std::string data = "";
			bool isKey = true;

			for (int i = 4; i < input.length(); i++)
			{
				char current = input[i];
				if (current == ' ' && isKey)
				{
					isKey = false;
					continue;
				}

				if (isKey)
				{
					stringifiedKey += current;
				}
				else
				{
					data += current;
				}
			}

			tree->Add(std::stoi(stringifiedKey), data);
		}
		else if (input[0] == 's')
		{
			std::string stringifiedKey = "";
			std::string data = "";
			bool isKey = true;

			for (int i = 7; i < input.length(); i++)
			{
				char current = input[i];
				if (current == ' ' && isKey)
				{
					isKey = false;
					continue;
				}

				if (isKey)
				{
					stringifiedKey += current;
				}
				else
				{
					data += current;
				}
			}

			bool result = tree->Search(std::stoi(stringifiedKey), data);
			std::cout << result << std::endl;
		}
		else
		{
			if (input[6] == 'a')
			{
				std::string stringifiedKey = "";

				for (int i = 10; i < input.length(); i++)
				{
					stringifiedKey += input[i];
				}

				int result = tree->RemoveAll(std::stoi(stringifiedKey));
				std::cout << result << std::endl;
			}
			else
			{
				std::string stringifiedKey = "";
				std::string data = "";
				bool isKey = true;

				for (int i = 7; i < input.length(); i++)
				{
					char current = input[i];
					if (current == ' ' && isKey)
					{
						isKey = false;
						continue;
					}

					if (isKey)
					{
						stringifiedKey += current;
					}
					else
					{
						data += current;
					}
				}

				bool result = tree->Remove(std::stoi(stringifiedKey), data);
				std::cout << result << std::endl;
			}
		}
	}

	delete tree;

	return 0;
}
