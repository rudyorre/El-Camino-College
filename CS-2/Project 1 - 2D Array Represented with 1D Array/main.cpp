#include <iostream>
#include "CArray.h"
using namespace std;

int main()
{
    int Rows;
    int Cols;
    
    cout << "Number of rows --> ";
    cin >> Rows;
    cout << "Number of columns --> ";
    cin >> Cols;
    
    CArray Array;
    Array.Init(Rows, Cols);
    for (int i = 0; i < Rows; i++)
    {
        for (int k = 0; k < Cols; k++)
        {
            Array.Set(i, k, i * 100 + k);
        }
    }
    
    for (int i = 0; i < Rows; i++)
    {
        for (int k = 0; k < Cols; k++)
        {
            cout << Array.Get(i, k) << "  ";
        }
        cout << "\n";
    }
    
    //system("pause");
}
