#include "stdafx.h"
#include "Node.h"


Node::Node(char ch, int multiplier)
{
	this->_ch = ch;
	this->_multiplier = multiplier;
	this->_next = nullptr;
}

Node::~Node()
{
}

void Node::SetNext(Node* next)
{
	this->_next = next;
}

void Node::SetMultiplier(int newMupltiplier)
{
	this->_multiplier = newMupltiplier;
}

void Node::IncreaseMultiplier()
{
	this->_multiplier++;
}

Node* Node::Next()
{
	return this->_next;
}

char Node::Char()
{
	return this->_ch;
}

int Node::Multiplier()
{
	return this->_multiplier;
}
