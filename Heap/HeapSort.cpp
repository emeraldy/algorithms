#include"Heap.h"
#include"HeapSort.h"
#include<iostream>
using namespace std;

void HeapSort(int data[], int dataSize, int sortOrder)
{
	Heap heap;
	if (sortOrder == ASCEND)
		heap.build(data, dataSize, false);
	else
		heap.build(data, dataSize, true);

	heap.printKeys();

	for (int i = 0; i < dataSize; i++)
		data[i] = heap.extractRoot();		
}