#include "CGraph.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

CGraph::CGraph(int** graph, int size, int source)
{
	Graph = graph;
	Size = size;
	Source = source;
	Infinity = 9999;
}

CGraph::~CGraph()
{
	delete Graph;
}

int CGraph::MinDistance(int* Distance, bool* Visited)
{
	int min = INT_MAX;
	int index = 0;

	for (int i = 0; i < Size; i++)
	{
		if (!Visited[i] && Distance[i] <= min)
		{
			min = Distance[i];
			index = i;
		}
	}

	return index;
}

void CGraph::PrintPath(int* Parent, int index)
{
	if (Parent[index] == -1) return;

	PrintPath(Parent, Parent[index]);

	printf("%d ", index);
}

void CGraph::PrintSolution(int* Distance, int* Parent)
{
	int src = 0;
	cout << left << setw(12) << "Vertex" << setw(12) << "Distance" << setw(12) << "Path";

	for (int i = 0; i < Size; i++)
	{
		cout << endl << left << setw(12) << to_string(src) + " -> " + to_string(i) << setw(12) << Distance[i] << src << " ";

		PrintPath(Parent, i);
	}
}

void CGraph::Dijkstra()
{
	int* Distance = new int[Size];
	bool* Visited = new bool[Size];
	int* Parent = new int[Size];

	Parent[0] = -1;
	for (int i = 0; i < Size; i++)
	{
		
		Distance[i] = INT_MAX;
		Visited[i] = false;
	}

	Distance[Source] = 0;

	for (int count = 0; count < Size - 1; count++)
	{
		int u = MinDistance(Distance, Visited);

		Visited[u] = true;

		for (int v = 0; v < Size; v++)
		{
			if (!Visited[v] && Graph[u][v] && Distance[u] + Graph[u][v] < Distance[v])
			{
				Parent[v] = u;
				Distance[v] = Distance[u] + Graph[u][v];
			}
		}
	}

	PrintSolution(Distance, Parent);
}