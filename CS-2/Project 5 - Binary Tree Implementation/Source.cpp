#include <iostream>
#include <fstream>
#include "BinaryTree.h"
using namespace std;

int main()
{
	ifstream file;
	file.open("input.txt");
	BinaryTree tree;

	while (file.peek() != EOF)
	{
		int item;
		file >> item;

		tree.Insert(item);
	}

	tree.Print();
}