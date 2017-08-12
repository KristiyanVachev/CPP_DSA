#pragma once
#include "Specials.h"

class State
{
private:
	Specials _special;
	char _value;
	State* _next;
	State* _alternative;
	bool _isFinal;

public:
	State(char value, bool isFinal, Specials special);
	~State();

	//Getters
	bool IsSpecial();
	Specials Special();
	char Value();
	bool IsFinal();
	State* Next();
	State* Alternative();

	//Setters
	void SetIsFinal(bool isFinal);
	void SetNext(State* state);
	void SetAlternative(State* state);
};

inline State::State(char value, bool isFinal = false, Specials special = None)
{
	this->_special = special;
	this->_value = value;
	this->_isFinal = isFinal;

	this->_next = nullptr;
	this->_alternative = nullptr;
}

inline State::~State()
{
}

inline bool State::IsSpecial()
{
	return this->_special != None;
}

inline Specials State::Special()
{
	return this->_special;
}

inline char State::Value()
{
	return this->_value;
}

inline bool State::IsFinal()
{
	return this->_isFinal;
}

inline State* State::Next()
{
	return this->_next;
}

inline State* State::Alternative()
{
	return this->_alternative;
}

inline void State::SetIsFinal(bool isFinal)
{
	this->_isFinal = isFinal;
}

inline void State::SetNext(State* state)
{
	this->_next = state;
}

inline void State::SetAlternative(State* state)
{
	State* lastAlternative = this;

	while (lastAlternative->Alternative() != nullptr)
	{
		lastAlternative = lastAlternative->Alternative();

		//Skip if the alternative is already added
		if (lastAlternative == state)
		{
			return;
		}
	}

	lastAlternative->_alternative = state;
}
