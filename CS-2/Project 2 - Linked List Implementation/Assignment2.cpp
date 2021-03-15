#include "pch.h"
#include "CList.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	CList list;
	ifstream file;
	file.open("example.txt");
	
	while (file.peek() != EOF)
	{
		int Row;
		file >> Row;
		int Col;
		file >> Col;
		int Val;
		file >> Val;

		if (Val != 0)
		{
			tElem* tmp = new tElem;
			tmp->Row = Row;
			tmp->Col = Col;
			tmp->Val = Val;
			list.Insert(tmp);
		}
		else
		{
			list.Delete(Row, Col);
		}
	}

	list.Print();

	file.close();
}