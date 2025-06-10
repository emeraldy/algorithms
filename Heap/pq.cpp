#include"Heap.h"
#include<iostream>
using namespace std;

void main()
{
	int dataToSort[10] = { -1, 33, 10, 200, 7, -3, 1, 2, 66, 0 };
	Heap heap;
	heap.build(dataToSort, 10, false);
	heap.printKeys();
	heap.insert(-2);
	heap.printKeys();
}