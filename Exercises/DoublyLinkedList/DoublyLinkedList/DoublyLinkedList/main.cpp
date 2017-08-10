#include "stdafx.h"
#include "DoublyLinkedList.h"

#include "iostream"

using namespace std;

class MyClass
{
public:
	MyClass(int value);
	~MyClass();

private:
	int value;
};

MyClass::MyClass(int value)
{
	this->value = value;
}

MyClass::~MyClass()
{
}

int main()
{
	DoublyLinkedList<MyClass> nodes;

	MyClass* two = new MyClass(2);
	MyClass* four = new MyClass(4);
	MyClass* eight = new MyClass(8);

	nodes.AddTail(two);
	nodes.AddTail(four);
	nodes.AddTail(eight);

	nodes.Remove(nodes.Head()->Next());

	nodes.Remove(nodes.Head()->Next());

	nodes.Remove(nodes.Head());

    return 0;
}

