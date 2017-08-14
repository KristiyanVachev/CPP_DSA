#pragma once

template <typename type> class DynamicArray
{
private:
	type* *_data;
	int _used;
	int _size;

	void Reallocate(int newSize);

public:
	DynamicArray();
	~DynamicArray();

	void Add(type* element);
	type* *Data();
	int Lenght();
};

template <typename type>
void DynamicArray<type>::Reallocate(int newSize)
{
	type* *temp = new type*[newSize];

	for (int i = 0; i < this->_used; i++)
	{
		temp[i] = this->_data[i];
	}

	delete[] this->_data;
	this->_data = temp;
	this->_size = newSize;
}

template <typename type>
DynamicArray<type>::DynamicArray()
{
	this->_data = new type*[0];
	this->_used = 0;
	this->_size = 0;
}

template <typename type>
DynamicArray<type>::~DynamicArray()
{
	this->_size = 0;
	this->_used = 0;
	delete[] this->_data;
	this->_data = nullptr;
}

template <typename type>
void DynamicArray<type>::Add(type* element)
{
	if (this->_size <= this->_used)
	{
		int newSize = (this->_size == 0) ? 2 : this->_size * 2;
		
		Reallocate(newSize);
	}

	this->_data[this->_used++] = element;
}

template <typename type>
type* *DynamicArray<type>::Data()
{
	return this->_data;
}

template <typename type>
int DynamicArray<type>::Lenght()
{
	return this->_used;
}
