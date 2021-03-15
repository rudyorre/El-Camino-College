#pragma once

class CArray
{
public:
    CArray();
    ~CArray();
    
private:
    int *mStorage;
    int mRows;
    int mCols;
    
public:
    void Init(int Rows, int Cols);
    int Get(int Row, int Col);
    void Set(int Row, int Col, int Val);
    int GetOffset(int Row, int Col);
};
