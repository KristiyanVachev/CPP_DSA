#pragma once
class DynamicArray
{
private:
	size_t _size;
	size_t _used;
	int* _data;

	void Reallocate();

public:
	DynamicArray();
	~DynamicArray();
	int operator[](int i);

	void Add(int element);
	int Lenght();
	int* Data();
};

