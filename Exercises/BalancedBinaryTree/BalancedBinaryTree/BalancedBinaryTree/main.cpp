// BalancedBinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "BBTree.h";
#include "DynamicArray/DynamicArray.h"

using namespace std;

int main()
{
	DynamicArray arr;
	arr.Add(2, "Two");
	arr.Add(3, "Three");
	arr.Add(6, "Six");
	arr.Add(5, "Five");
	arr.Add(1, "One");
	arr.Add(4, "Four");

	arr.Sort();

	for (int i = 0; i < arr.Lenght(); i++)
	{
		cout << arr.Data()[i]->Key() << " ";
	}

	cout << endl;

	BBTree* tree = new BBTree(&arr);
	

    return 0;
}
