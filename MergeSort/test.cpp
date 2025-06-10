#include<iostream>
#include "MergeSort.h"

using namespace std;

void main()
{
	int dataToSort[8] = {3, 41, 52, 26, 38, 57, 9, 49};
	MergeSort(dataToSort, 0, 7, ASCEND);
	for(int i = 0; i < 8; i++)
		cout<<dataToSort[i]<<endl;
}