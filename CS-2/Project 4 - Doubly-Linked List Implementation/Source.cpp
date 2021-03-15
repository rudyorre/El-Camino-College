#include <iostream>
#include <fstream>
#include "CList.h"
using namespace std;

int main()
{
	ifstream file;
	file.open("example.txt");
	CList list;

	while (file.peek() != EOF)
	{
		int Row;
		file >> Row;
		int Col;
		file >> Col;
		int Val;
		file >> Val;

		list.Evaluate(Row, Col, Val);
	}

	list.Print();
}