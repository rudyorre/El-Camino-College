#include <iostream>

typedef struct sElem
{
	int Row;
	int Col;
	int Val;
	struct sElem* Next;
	struct sElem* Back;
}tElem;

class CList
{
public:
	CList();
	~CList();

private:
	tElem* mPtr;
	tElem* mLast;

public:
	void Insert(tElem* Elem);
	void Delete(int Row, int Col);
	tElem* Search(int Row, int Col);
	void Evaluate(int Row, int Col, int Val);
	void Print();
};