#include<iostream>
#include "InsertionSort.h"

using namespace std;

void main()
{
	int dataToSort[10] = {3, 20, 41, 5, 1, 7, 100, 33, 9, 120};
	InsertionSort(dataToSort, 10, ASCEND);
	for(int i = 0; i < 10; i++)
		cout<<dataToSort[i]<<endl;
}