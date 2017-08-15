#pragma once

#include "../Input.h";

class DynamicArray
{
private:
	Input* *_data;
	int _used;
	int _size;

	void Reallocate(int newSize);

	void MergeSort(Input* *arr, Input* *arrCopy, int start, int end);
	void Merge(Input* *arr, Input* *mergedArr, int start, int end);
	void Copy(Input* *arr, Input* *arrCopy, int start, int end);

public:
	DynamicArray();
	~DynamicArray();

	void Add(int key, std::string value);
	Input* *Data();
	int Lenght();

	void Sort();
};

inline void DynamicArray::Reallocate(int newSize)
{
	Input* *temp = new Input*[newSize];

	for (int i = 0; i < this->_used; i++)
	{
		temp[i] = this->_data[i];
	}

	delete[] this->_data;
	this->_data = temp;
	this->_size = newSize;
}

inline void DynamicArray::MergeSort(Input** arr, Input** arrCopy, int start, int end)
{
	if (end == start)
	{
		return;
	}

	if (end - start == 1)
	{
		if (arr[start]->Key() > arr[end]->Key())
		{
			Input* temp = arr[start];
			arr[start] = arr[end];
			arr[end] = temp;
		}

		return;
	}

	int middle = start + (end - start) / 2;
	MergeSort(arr, arrCopy, start, middle);
	MergeSort(arr, arrCopy, middle + 1, end);

	Merge(arr, arrCopy, start, end);

	Copy(arr, arrCopy, start, end);
}

inline void DynamicArray::Merge(Input** arr, Input** mergedArr, int start, int end)
{
	int middle = start + (end - start) / 2;

	int placedIndex = start;
	int firstIndex = start;
	int secondIndex = middle + 1;


	while (firstIndex <= middle || secondIndex <= end)
	{
		if (firstIndex == middle + 1)
		{
			mergedArr[placedIndex] = arr[secondIndex];
			secondIndex++;
			placedIndex++;
			continue;
		}

		if (secondIndex == end + 1)
		{
			mergedArr[placedIndex] = arr[firstIndex];
			firstIndex++;
			placedIndex++;
			continue;
		}

		if (arr[firstIndex]->Key() < arr[secondIndex]->Key())
		{
			mergedArr[placedIndex] = arr[firstIndex];
			firstIndex++;
		}
		else
		{
			mergedArr[placedIndex] = arr[secondIndex];
			secondIndex++;
		}

		placedIndex++;
	}
}

inline void DynamicArray::Copy(Input** arr, Input** arrCopy, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		arr[i] = nullptr;
		arr[i] = arrCopy[i];
	}
}

inline DynamicArray::DynamicArray()
{
	this->_data = new Input*[0];
	this->_used = 0;
	this->_size = 0;
}


inline DynamicArray::~DynamicArray()
{
	this->_size = 0;
	this->_used = 0;
	delete[] this->_data;
	this->_data = nullptr;
}

inline void DynamicArray::Add(int key, std::string value)
{
	Input* newInput = new Input(key, value);

	if (this->_size <= this->_used)
	{
		int newSize = (this->_size == 0) ? 2 : this->_size * 2;

		Reallocate(newSize);
	}

	this->_data[this->_used++] = newInput;
}

inline Input* *DynamicArray::Data()
{
	return this->_data;
}

inline int DynamicArray::Lenght()
{
	return this->_used;
}

inline void DynamicArray::Sort()
{
	DynamicArray* arrCopy = new DynamicArray;
	arrCopy->Reallocate(this->_used);

	MergeSort(this->_data, arrCopy->_data, 0, this->_used - 1);
}
