#include "stdafx.h"
#include "DynamicArray.h"


void DynamicArray::Reallocate()
{
	if (this->_size == 0)
	{
		this->_size = 2;
		this->_data = new int[2];
	}

	int* newArr = new int[this->_size * 2];

	for (int i = 0; i < this->_size; i++)
	{
		newArr[i] = this->_data[i];
	}

	delete[] this->_data;
	
	this->_data = newArr;
	this->_size = this->_size * 2;
}

DynamicArray::DynamicArray()
{
	this->_size = 0;
	this->_used = 0;
}


DynamicArray::~DynamicArray()
{
}

void DynamicArray::Add(int element)
{
	if (this->_used == this->_size)
	{
		Reallocate();
	}

	this->_data[this->_used] = element;
	this->_used++;
}

int DynamicArray::Lenght()
{
	return this->_used;
}

int* DynamicArray::Data()
{
	return this->_data;
}
