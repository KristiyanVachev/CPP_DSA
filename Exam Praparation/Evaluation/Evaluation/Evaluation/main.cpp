#include "stdafx.h"
#include <iostream>

#include "DynamicArray.h"

using namespace std;

int main()
{	
	DynamicArray arr;
	arr.Add(2);
	arr.Add(4);
	arr.Add(6);
	arr.Add(8);
	arr.Add(10);

	for (int i = 0; i < arr.Lenght(); i++)
	{
		cout << arr.Data()[i] << endl;
	}
}