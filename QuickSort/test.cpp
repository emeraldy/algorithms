#include<iostream>
#include"QuickSort.h"

using namespace std;

void main()
{
	int dataToSort[8] = { 3, 41, 52, 26, 38, 57, 9, 49 };
	QuickSort(dataToSort, 0, 7, DESCEND);
	for (int i = 0; i < 8; i++)
		cout << dataToSort[i] << endl;
}