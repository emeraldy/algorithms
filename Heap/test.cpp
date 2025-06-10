#include"HeapSort.h"
#include<iostream>
using namespace std;


void main()
{
	int dataToSort[10] = { -1, 33, 10, 200, 7, -3, 1, 2, 66, 0 };
	HeapSort(dataToSort, 10, ASCEND);
	for (int i = 0; i < 10; i++)
		cout << dataToSort[i] << endl;
}