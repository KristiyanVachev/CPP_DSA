#pragma once

//Manual tests for dynamic array - https://github.com/KristiyanVachev/CPP_DSA/blob/master/Exercises/DynamicArray/DynamicArray/DynamicArray/main.cpp

class DynamicArray
{
private:
	int* _data;
	int _used;
	int _size;
	bool _isSorted;

	void Reallocate(int newSize);

	void MergeSort(int* arr, int* arrCopy, int start, int end);
	void Merge(int* arr, int* mergedArr, int start, int end);
	void Copy(int* arr, int* arrCopy, int start, int end);

public:
	DynamicArray();
	~DynamicArray();

	void Add(int data);
	int* Data();
	int Lenght();

	void Sort();
	bool Contains(int data);
};

inline void DynamicArray::Reallocate(int newSize)
{
	int* temp = new int[newSize];

	for (int i = 0; i < this->_used; i++)
	{
		temp[i] = this->_data[i];
	}

	delete[] this->_data;
	this->_data = temp;
	this->_size = newSize;
}

inline void DynamicArray::MergeSort(int* arr, int* arrCopy, int start, int end)
{
	if (end == start)
	{
		return;
	}

	if (end - start == 1)
	{
		if (arr[start] > arr[end])
		{
			int temp = arr[start];
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

inline void DynamicArray::Merge(int* arr, int* mergedArr, int start, int end)
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

		if (arr[firstIndex] < arr[secondIndex])
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

inline void DynamicArray::Copy(int* arr, int* arrCopy, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		arr[i] = arrCopy[i];
	}
}

inline DynamicArray::DynamicArray()
{
	this->_data = nullptr;
	this->_used = 0;
	this->_size = 0;
	this->_isSorted = false;
}


inline DynamicArray::~DynamicArray()
{
	this->_size = 0;
	this->_used = 0;
	delete[] this->_data;
	this->_data = nullptr;
}

inline void DynamicArray::Add(int key)
{

	if (this->_size <= this->_used)
	{
		int newSize = (this->_size == 0) ? 2 : this->_size * 2;

		Reallocate(newSize);
	}

	this->_data[this->_used++] = key;

	this->_isSorted = false;
}

inline int* DynamicArray::Data()
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

	this->_isSorted = true;
	delete arrCopy;
}

inline bool DynamicArray::Contains(int number)
{
	if (!this->_isSorted)
	{
		this->Sort();
	}

	int start = 0;
	int end = this->_used - 1;

	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (this->_data[mid] == number)
		{
			return true;
		}
		
		if(number < this->_data[mid])
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}

	return false;
}
