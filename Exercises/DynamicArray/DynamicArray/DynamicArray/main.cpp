// DynamicArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DynamicArray.h"

#include <iostream>
#include "TestClass.h"

using namespace std;

int main()
{
	DynamicArray<TestClass> arr;

	arr.Add(new TestClass(2));
	arr.Add(new TestClass(4));
	arr.Add(new TestClass(8));
	arr.Add(new TestClass(16));
	arr.Add(new TestClass(32));
	arr.Add(new TestClass(64));

	for (int i = 0; i < arr.Lenght(); i++)
	{
		cout << arr.Data()[i]->Value() << endl;
	}

	return 0;
}

