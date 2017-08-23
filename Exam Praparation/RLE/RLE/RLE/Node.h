#pragma once
class Node
{
private:
	char _ch;
	int _multiplier;
	Node* _next;

public:
	Node(char ch, int multiplier = 1);
	~Node();

	void SetNext(Node* next);
	void SetMultiplier(int newMupltiplier);
	void IncreaseMultiplier();

	Node* Next();
	char Char();
	int Multiplier();
};

