#include "CArray.h"

CArray::CArray()
{
    mStorage = nullptr;
}

CArray::~CArray()
{
    delete mStorage;
}

void CArray::Init(int Rows, int Cols)
{
    mRows = Rows;
    mCols = Cols;
    mStorage = new int [Rows * Cols];
}

int CArray::Get(int Row, int Col)
{
    return mStorage[Row * mCols + Col];
}

void CArray::Set(int Row, int Col, int Val)
{
    mStorage[Row * mCols + Col] = Val;
}

int CArray::GetOffset(int Row, int Col)
{
    return Row * mCols + Col;
}
