#pragma once

#include <iostream>
#include "LinkedList.h"

class RLEString
{
private:
	size_t _lenght;
	LinkedList* _nodes;

public:
	//Big 4
	RLEString(char const*);
	RLEString(const RLEString& other);
	~RLEString();
	RLEString* operator=(RLEString other);

	friend std::ostream& operator<<(std::ostream& os, const RLEString&);
	size_t Length() const;
	char& operator[](int i);
	RLEString operator+(RLEString const & right) const;
	void Splice(int start, int length);
	void Insert(const RLEString& rles, int pos);
};

