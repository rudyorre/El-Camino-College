#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	Map m;
	Map n;

	m.insert("A", 0.0);
	m.insert("B", 0.25);
	m.insert("C", 0.50);
	m.insert("D", 0.75);
	m.insert("E", 1.00);
	m.insert("F", 1.25);

	n.insert("B", 0.1);
	n.insert("F", 1.25);
	n.insert("G", 1.50);
	n.insert("H", 1.75);
	n.insert("I", 2.00);
	n.insert("J", 2.25);
	n.insert("K", 2.50);
	n.insert("L", 2.75);

	Map result;

	combine(m, n, result);
	print(result);

	subtract(m, n, result);
	print(result);
}