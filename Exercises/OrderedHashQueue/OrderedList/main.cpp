// OrderedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OrderedHashQueue.h"
#include <iostream>

using namespace std;

int main()
{
	OrderedHashQueue<int> queue = OrderedHashQueue<int>(false);

	queue.Add(6);
	queue.Add(4);
	queue.Add(3);
	queue.Add(3);
	queue.Add(5);
	queue.Add(5325);
	queue.Add(5325);
	queue.Add(2324);
	queue.Add(34);
	queue.Add(123);
	queue.Add(0);
	queue.Add(5323);
	queue.Add(122);
	queue.Add(3341);

	queue.Pop();
	int element = queue.Pop();

	cout << element << endl;

    return 0;
}

