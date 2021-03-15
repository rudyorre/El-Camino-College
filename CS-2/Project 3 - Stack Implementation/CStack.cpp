#include <iostream>
#include "CStack.h"
using namespace std;

int top;
int* stack;

CStack::CStack()
{
	stack = new int[MAX];
	top = -1;
}

CStack::~CStack()
{
	//top = -1;
}

void CStack::push(int x)
{
	if (!isFull())
	{
		stack[++top] = x;
	}
}

int CStack::pop()
{
	if (!isEmpty())
	{
		return stack[top--];
	}
	return -1;
}

bool CStack::isEmpty()
{
	bool isEmpty = false;
	if (top == -1)
	{
		isEmpty = true;
	}
	return isEmpty;
}

bool CStack::isFull()
{
	bool isFull = false;
	if (top == (MAX - 1))
	{
		isFull = true;
	}
	return isFull;
}

void CStack::print()
{
	for (int i = 0; i <= top; i++)
	{
		cout << stack[i] << endl;
	}
}

int CStack::getTop()
{
	int ret = stack[top];
	if (top < 0)
	{
		ret = NULL;	
	}
	return ret;
}

int CStack::size()
{
	return top;
}