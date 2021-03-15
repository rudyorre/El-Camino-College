#include <iostream>
#include <string>
#include <fstream>
#include "CStack.h"
using namespace std;

double evaluate(string postfix, string &error);
double operation(int a, int b, char op);
bool isOperator(char c);
bool isOperand(char c);
double scanNum(char c);

int main()
{
	ifstream file;
	file.open("a3_input.txt");

	while (file.peek() != EOF)
	{
		string line;
		string error;
		getline(file, line);
		double evaluation = evaluate(line, error);

		if (error.length() == 0)
		{
			cout << line << " = " << evaluation << endl;
		}
		else
		{
			cout << line << " = " << error << endl;
		}
		cout << endl;
	}

	file.close();
	system("pause");
}

double evaluate(string postfix, string &error)
{
	int a, b;
	CStack stack;
	int errorType = 0;
	int operandCount = 0;
	int operatorCount = 0;
	
	for (int i = 0; i < postfix.length(); i++)
	{
		char c = postfix[i];
		if (isOperator(c))
		{
			a = stack.getTop();
			stack.pop();
			b = stack.getTop();
			stack.pop();
			stack.push(operation(a, b, c));
			if (c == '/' && a == 0)
			{
				errorType = 2;
				break;
			}
		}
		else if (isOperand(c))
		{
			stack.push(scanNum(c));
		}
		else
		{
			errorType = 1;
			break;
		}
	}

	for (int i = 0; i < postfix.length(); i++)
	{
		char c = postfix[i];
		if (isOperator(c))
		{
			operatorCount++;
		}
		else if (isOperand(c))
		{
			operandCount++;
		}
	}

	if (errorType == 1)
	{
		error = "Error: Invalid operands and/or operators.";
	}
	else if (errorType == 2)
	{
		error = "Error: Divide by zero.";
	}
	else if (operandCount <= operatorCount)
	{
		error = "Error: Insufficient amount of operands.";
	}
	else if (operatorCount < operandCount - 1)
	{
		error = "Error: Insufficient amount of operators.";
	}
	

	return stack.getTop();
}

bool isOperator(char c)
{
	bool ret = false;
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		ret = true;
	}
	return ret;
}

double operation(int a, int b, char op)
{
	double ret = 0.0;
	if (op == '+')
		ret = b + a;
	else if (op == '-')
		ret = b - a;
	else if (op == '*')
		ret = b * a;
	else if (op == '/' && a != 0)
		ret = b / a;
	else if (op == '^')
		ret = pow(b, a);
	
	return ret;
}

bool isOperand(char c)
{
	bool ret = false;
	if (c >= '0' && c <= '9')
	{
		ret = true;
	}
	return ret;
}

double scanNum(char c)
{
	return static_cast<double>(c - '0');
}