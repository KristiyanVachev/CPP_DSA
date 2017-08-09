#pragma once

class State
{
private:
	//TODO enum for any space, digit and letter
	char _value;
	State* _next;
	State* _alternative;
	bool _isFinal;

public:
	State(char value, bool isFinal);
	~State();

	//Getters
	char Value();
	bool IsFinal();
	State* Next();
	State* Alternative();

	//Setters
	void SetIsFinal(bool isFinal);
	void SetNext(State* state);
	void SetAlternative(State* state);

};

inline State::State(char value, bool isFinal)
{
	this->_value = value;
	this->_isFinal = isFinal;

	this->_next = nullptr;
	this->_alternative = nullptr;
}

inline State::~State()
{
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
	State* lastAlternative = this->Alternative();

	while (lastAlternative != nullptr)
	{
		lastAlternative = lastAlternative->Alternative();
	}

	lastAlternative->SetAlternative(state);
}
