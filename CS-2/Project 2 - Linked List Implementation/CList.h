#pragma once

typedef struct sElem
{
	int Row;
	int Col;
	int Val;
	struct sElem* Next;
} tElem;

class CList
{
public:
	CList();
	~CList();

public:
	tElem* mPtr;
	tElem* mLast;
	void Insert(tElem* Elem);
	void Delete(int Row, int Col);
	tElem* Search(int Row, int Col);
	void Print();
};