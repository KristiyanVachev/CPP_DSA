#pragma once
#include <string>

class Input
{
private:
	int _key;
	std::string _value;

public:
	Input(int key, std::string value);
	~Input();

	int Key();
	std::string Value();
};

inline Input::Input(int key, std::string value)
{
	this->_key = key;
	this->_value = value;
}

inline Input::~Input()
{
}

inline int Input::Key()
{
	return this->_key;
}

inline std::string Input::Value()
{
	return this->_value;
}
