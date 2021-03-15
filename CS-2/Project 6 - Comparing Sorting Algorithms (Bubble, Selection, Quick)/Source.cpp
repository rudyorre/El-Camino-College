#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "CSort.h"
using namespace std;

int* create(int size);
void copy(int* original, int* copy, int size);
void print(int* arr, int size);
void measure(int size);

int main()
{
	int* original = create(100);

	CSort sort;
	int* arr = new int[100];
	
	//bubble sort
	copy(original, arr, 100);

	cout << "bubble sort" << endl;
	print(arr, 100);

	sort.bubble(arr, 100);
	print(arr, 100);

	//selection sort
	copy(original, arr, 100);

	cout << "selection sort" << endl;
	print(arr, 100);

	sort.selection(arr, 100);
	print(arr, 100);

	//quick sort
	copy(original, arr, 100);

	cout << "quick sort" << endl;
	print(arr, 100);

	sort.quick(arr, 100);
	print(arr, 100);
	
	//sort time
	measure(1024 * 128);
	measure(1024 * 256);
	measure(1024 * 512);

}

int* create(int size)
{
	int* arr = new int[size];
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % size;
	}

	return arr;
}

void copy(int* original, int* copy, int size)
{
	for (int i = 0; i < size; i++)
	{
		copy[i] = original[i];
	}
}

void print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << setw(5) << arr[i];
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}

void measure(int size)
{
	int* original = create(size);
	int* arr = new int[size];
	CSort sort;

	copy(original, arr, size);
	DWORD start = GetTickCount64();
	sort.bubble(arr, size);
	DWORD end = GetTickCount64();
	printf("bubble sort   size = %d, time= %d\n", size, end - start);

	copy(original, arr, size);
	start = GetTickCount64();
	sort.selection(arr, size);
	end = GetTickCount64();
	printf("selection sort   size = %d, time= %d\n", size, end - start);

	copy(original, arr, size);
	start = GetTickCount64();
	sort.quick(arr, size);
	end = GetTickCount64();
	printf("quick sort   size = %d, time= %d\n", size, end - start);

	cout << endl;
}
