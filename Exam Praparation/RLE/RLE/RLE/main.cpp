
#include "stdafx.h"
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList nodes;

	nodes.AddTail('k');
	nodes.AddTail('v');

	cout << nodes.Head()->Next()->Char() << endl;

    return 0;
}

