#pragma once

class CSort
{
public:
	CSort();
	~CSort();

public:
	void swap(int& a, int& b);
	void bubble(int* arr, int size);
	void selection(int* arr, int size);
	void quick(int* arr, int size);
	void quick(int* arr, int low, int high);
	int partition(int* arr, int low, int high);
};