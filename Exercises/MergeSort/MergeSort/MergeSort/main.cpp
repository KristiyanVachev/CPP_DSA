#include "stdafx.h"
#include <iostream>

void Split(int start, int end);
void Merge(int currArr[], int mergedArr[], int start, int end);
void Copy(int arr[], int arrCopy[], int start, int end);

int arr[] = { 6, 5, 3, 1, 8, 7, 2, 9, 10, 4, 4};
int arrCopy[11];

using namespace std;

int main()
{
	int size = 10;

	for (int i = 0; i <= size; i++)
	{
		cout << arr[i];
	}
	cout << endl;

	Split(0, size);

	for (int i = 0; i <= size; i++)
	{
		cout << arr[i];
	}
	cout << endl;

	//TODO destroy arrayCopy

	return 0;
}

void Split(int start, int end)
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
	Split(start, middle);
	Split(middle + 1, end);

	Merge(arr, arrCopy, start, end);

	Copy(arr, arrCopy, start, end);
}

void Merge(int currArr[], int mergedArr[], int start, int end)
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

void Copy(int arr[], int arrCopy[], int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		arr[i] = arrCopy[i];
	}
}
