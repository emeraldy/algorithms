#include<iostream>
#include"CountingSort.h"

using namespace std;

void main()
{
    int dataToSort[8] = { 14, 15, 13, 11, 12, 12, 14, 16 };// range 11 to 16
    CountingSort(dataToSort, 8, 6, 11, ASCEND);
    for (int i = 0; i < 8; i++)
        cout << dataToSort[i] << endl;
}