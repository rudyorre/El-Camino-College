class CGraph
{
private:
	int** Graph;
	int Size;
	int Source;
	int Infinity;
public:
	CGraph(int** matrix, int size, int source);
	~CGraph();
	void Dijkstra();
	int MinDistance(int* Distance, bool* Visited);
	void PrintPath(int Parent[], int j);
	void PrintSolution(int* Distance, int* Parent);
};