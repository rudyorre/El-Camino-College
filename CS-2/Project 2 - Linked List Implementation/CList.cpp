#include "pch.h"
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
	while (tmp != nullptr)
	{
		tElem* next = tmp->Next;
		delete tmp;
		tmp = next;
	}
	mPtr = 0;
}

void CList::Insert(tElem* Elem)
{
	tElem* tmp = new tElem;
	tmp->Row = Elem->Row;
	tmp->Col = Elem->Col;
	tmp->Val = Elem->Val;
	tmp->Next = nullptr;

	if (mPtr == nullptr)
	{
		mPtr = tmp;
		mLast = tmp;
	}
	else if (Search(tmp->Row, tmp->Col) == nullptr)
	{
		mLast->Next = tmp;
		mLast = mLast->Next;
	}
	else
	{
		Search(tmp->Row, tmp->Col)->Val = tmp->Val;
	}
}


void CList::Delete(int Row, int Col)
{
	bool found = false;
	tElem* ptr = nullptr;
	tElem* prev = nullptr;
	ptr = mPtr;

	while (ptr != nullptr)
	{
		if (ptr->Row == Row && ptr->Col == Col)
		{
			found = true;
			break;
		}
		prev = ptr;
		ptr = ptr->Next;
	}

	if (found)
	{
		if (ptr == mPtr)
		{
			mPtr = ptr->Next;
			if (mPtr == nullptr)
			{
				mLast = nullptr;
			}
		}
		else
		{
			if (ptr == mLast)
			{
				prev->Next = nullptr;
				mLast = prev;
			}
			else
			{
				prev->Next = ptr->Next;
			}
		}
	}
	delete ptr;
}

tElem* CList::Search(int Row, int Col)
{
	tElem* tmp = nullptr;
	tmp = mPtr;
	bool found = false;

	while (tmp != nullptr)
	{
		if (tmp->Row == Row && tmp->Col == Col)
		{
			found = true;
			break;
		}
		tmp = tmp->Next;
	}

	if (!found)
	{
		tmp = nullptr;
	}

	return tmp;
}


void CList::Print()
{
	tElem *tmp;
	tmp = mPtr;
	while (tmp != nullptr)
	{
		cout << tmp->Row << " " << tmp->Col << " " << tmp->Val << endl;
		tmp = tmp->Next;
	}
}