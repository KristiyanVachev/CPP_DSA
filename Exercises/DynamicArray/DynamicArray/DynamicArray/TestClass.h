#pragma once

class TestClass
{
private:
	int _value;

public:
	TestClass(int value);
	~TestClass();

	int Value();
};

inline TestClass::TestClass(int value)
{
	this->_value = value;
}

inline TestClass::~TestClass()
{
}

inline int TestClass::Value()
{
	return this->_value;
}