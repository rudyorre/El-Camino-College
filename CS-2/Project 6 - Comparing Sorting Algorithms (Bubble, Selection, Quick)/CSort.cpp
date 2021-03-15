#include <iostream>
#include <iomanip>
#include "CSort.h"
#define MAX 100
using namespace std;

CSort::CSort()
{
	
}

CSort::~CSort()
{
	
}

void CSort::swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void CSort::bubble(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		bool swapped = false;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

void CSort::selection(int* arr, int size)
{
	int i, j, min;
	for (i = 0; i < size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < size; j++)
			if (arr[j] < arr[min])
			{
				min = j;
			}
		swap(arr[i], arr[min]);
	}
}

void CSort::quick(int* arr, int size)
{
	quick(arr, 0, size - 1);
}

void CSort::quick(int* arr, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(arr, low, high);

		quick(arr, low, pivot - 1);
		quick(arr, pivot + 1, high);
	}
}

int CSort::partition(int* arr, int low, int high)
{
	int pivot = arr[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
