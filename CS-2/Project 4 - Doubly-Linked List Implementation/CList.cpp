#include "CList.h"
#include <iostream>
using namespace std;

tElem* mPtr;
tElem* mLast;

CList::CList()
{
	mPtr = nullptr;
	mLast = nullptr;
}

CList::~CList()
{
	tElem* tmp = mPtr;
	if (mPtr != nullptr)
	{
		while (tmp->Next != mPtr)
		{
			tElem* del = tmp;
			tmp = tmp->Next;
			delete del;
		}
	}
	delete tmp;
}

void CList::Insert(tElem* Elem)
{
	tElem* tmp = Elem;
	if (mPtr == nullptr)
	{
		mPtr = tmp;
		mPtr->Next = mPtr;
		mPtr->Back = mPtr;
		mLast = mPtr;
	}
	else if (Search(Elem->Row, Elem->Col) == nullptr)
	{
		tElem* last = mPtr->Back;

		mLast->Next = tmp;
		tmp->Back = mLast;
		tmp->Next = mPtr;
		mPtr->Back = tmp;
		mLast = mLast->Next;
	}
	else
	{
		tElem* tmp = Search(Elem->Row, Elem->Col);
		tmp->Val = Elem->Val;
	}
}

void CList::Print()
{
	tElem* tmp = mPtr;
	if (mPtr != nullptr)
	{
		cout << "Forward" << endl;
		while (tmp->Next != mPtr)
		{
			cout << tmp->Row << " " << tmp->Col << " " << tmp->Val << endl;
			tmp = tmp->Next;
		}
		cout << tmp->Row << " " << tmp->Col << " " << tmp->Val << endl << endl;

		cout << "Backward" << endl;
		while (tmp->Back != mLast)
		{
			cout << tmp->Row << " " << tmp->Col << " " << tmp->Val << endl;
			tmp = tmp->Back;
		}
		cout << tmp->Row << " " << tmp->Col << " " << tmp->Val << endl;
	}
	else
	{
		cout << "List is empty" << endl;
	}
}

tElem* CList::Search(int Row, int Col)
{
	tElem* tmp = mPtr;
	bool found = false;

	if (mPtr != nullptr)
	{
		while (tmp->Next != mPtr)
		{
			if (tmp->Row == Row && tmp->Col == Col)
			{
				found = true;
				break;
			}
			tmp = tmp->Next;
		}
		if (!found && tmp->Row == Row && tmp->Col == Col)
		{
			found = true;
		}
	}

	if (!found)
	{
		tmp = nullptr;
	}

	return tmp;
}

void CList::Delete(int Row, int Col)
{
	tElem* Elem = Search(Row, Col);
	if (Elem == mPtr)
	{
		mPtr = Elem->Next;
		if (mPtr == mPtr->Next)
		{
			mPtr = nullptr;
			mLast = nullptr;
		}
		else
		{
			mLast->Next = mPtr;
			mPtr->Back = mLast;
		}
	}
	else
	{
		if (Elem == mLast)
		{
			Elem->Back->Next = mPtr;
			mLast = Elem->Back;
		}
		else
		{
			Elem->Back->Next = Elem->Next;
			Elem->Next->Back = Elem->Back;
		}
	}

	delete Elem;
}

void CList::Evaluate(int Row, int Col, int Val)
{
	if (Val == 0)
	{
		Delete(Row, Col);
	}
	else
	{
		tElem* Elem = new tElem;
		Elem->Row = Row;
		Elem->Col = Col;
		Elem->Val = Val;
		Insert(Elem);
	}
}