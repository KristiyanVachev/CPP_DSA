#include "stdafx.h"
#include  <iostream>
#include "Tree.h";

using namespace std;
int main()
{
	Tree* tree = new Tree;

	tree->Add(4);
	tree->Add(2);
	tree->Add(3);
	tree->Add(6);
	tree->Add(3);


    return 0;
}

