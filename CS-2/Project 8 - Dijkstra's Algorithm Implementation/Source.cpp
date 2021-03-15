#include <iostream>
#include <fstream>
#include "CGraph.h"
using namespace std;

int main()
{
	ifstream file;
	file.open("example.txt");

	int size;
	file >> size;

	int** matrix = new int* [size];

	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			int num;
			file >> num;

			matrix[i][j] = num;
		}
	}

	int source;
	file >> source;

	CGraph Graph(matrix, size, source);

	Graph.Dijkstra();
}