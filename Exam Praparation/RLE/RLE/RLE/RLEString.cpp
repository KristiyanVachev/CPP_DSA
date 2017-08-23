#include "stdafx.h"
#include "RLEString.h"


RLEString::RLEString(char const* string)
{
	this->_nodes = new LinkedList();
	this->_lenght = std::strlen(string);

	for (int i = 0; i < this->_lenght; i++)
	{
		if (this->_nodes->Tail() != nullptr && this->_nodes->Tail()->Char() == string[i])
		{
			this->_nodes->Tail()->IncreaseMultiplier();
		}
		else
		{
			this->_nodes->AddTail(string[i]);
		}
	}
}

RLEString::RLEString(const RLEString& other)
{
	this->_nodes = other._nodes;
	this->_lenght = other._lenght;
}

RLEString::~RLEString()
{
}

RLEString* RLEString::operator=(RLEString other)
{
	this->_nodes = other._nodes;
	this->_lenght = other._lenght;
	
	return this;
}

size_t RLEString::Length() const
{
	return this->_lenght;
}

char& RLEString::operator[](int i)
{
	if (i >= this->_lenght || i < 0)
	{
		throw std::invalid_argument("Index out of range");
	}
	
	char ch;
	Node* currNode = this->_nodes->Head();
	int passedCount = 0;

	while (currNode != nullptr)
	{
		passedCount += currNode->Multiplier();

		if (i < passedCount)
		{
			ch = currNode->Char();
			break;
		}
		
		currNode = currNode->Next();
	}

	return ch;
}

RLEString RLEString::operator+(RLEString const& right) const
{
	RLEString result = (*this);

	result._lenght += right.Length();

	if (result._nodes->Tail()->Char() == right._nodes->Head()->Char())
	{
		result._nodes->Tail()->SetMultiplier(result._nodes->Tail()->Multiplier() + right._nodes->Head()->Multiplier());
		result._nodes->Tail()->SetNext(right._nodes->Head()->Next());
	}
	else
	{
		result._nodes->Tail()->SetNext(right._nodes->Head());
	}

	//TODO set result's tail to be right's tail

	return result;

}

void RLEString::Splice(int start, int length)
{

}

void RLEString::Insert(const RLEString& rles, int pos)
{

}

std::ostream& operator<<(std::ostream& os, const RLEString &rle)
{
	Node* currNode = rle._nodes->Head();

	while (currNode != nullptr)
	{
		for (int i = 0; i < currNode->Multiplier(); i++)
		{
			os << currNode->Char();
		}

		currNode = currNode->Next();
	}

	return os;
}
