#include "BinaryTree.h"
#include <iostream>
using namespace std;

#define PRINTMAX 200

BinaryTree::BinaryTree()
{
	Root = nullptr;
	count = 1;
}

BinaryTree::~BinaryTree()
{
	DeleteTree(Root);
}

sTreeNode* Root;
int count;

void BinaryTree::DeleteTree(sTreeNode* Node)
{
	if (Node == nullptr)
	{
		return;
	}

	DeleteTree(Node->Left);
	DeleteTree(Node->Right);
	delete Node;
}

void BinaryTree::Insert(int item)
{
	sTreeNode* nn = new sTreeNode;
	nn->Data = item;
	nn->Left = nullptr;
	nn->Right = nullptr;

	if (Root == nullptr)
	{
		Root = nn;
	}
	else
	{
		sTreeNode* ptr = Root;
		sTreeNode* prev = Root;
		int Left;

		while (ptr != nullptr)
		{
			if (item < ptr->Data)
			{
				prev = ptr;
				ptr = ptr->Left;
				Left = 1;
			}
			else if (item >= ptr->Data)
			{
				prev = ptr;
				ptr = ptr->Right;
				Left = 0;
			}
		}

		if (Left == 1)
		{
			prev->Left = nn;
		}
		else
		{
			prev->Right = nn;
		}
	}
}

int BinaryTree::Height(sTreeNode* Node)
{
	if (Node == nullptr)
	{
		return 0;
	}
	else
	{
		int LH = Height(Node->Left);
		int RH = Height(Node->Right);
		if (LH > RH)
		{
			return LH + 1;
		}
		else
		{
			return RH + 1;
		}
	}
}

void BinaryTree::Print(sTreeNode* Node)
{
	if (Node == nullptr || count > PRINTMAX)
	{
		return;
	}

	Print(Node->Left);
	if (count <= PRINTMAX)
	{
		cout << Node->Data << " ";
	}
	if (count % 10 == 0)
	{
		cout << endl;
	}
	count++;
	Print(Node->Right);
}

void BinaryTree::Print()
{
	Print(Root);
	cout << endl << "Height: " << Height(Root) << endl;
	count = 1;
}