#include"QuickSort.h"

//treat right-most element as pivot
int Split(int* data, int begin, int end, int order)
{
	int i, j, swapping;

	i = begin - 1;
	j = begin;
	while (j < end)
	{
		if(order == ASCEND)
		{
			if (data[j] < data[end])
			{
				swapping = data[i + 1];
				data[i + 1] = data[j];
				data[j] = swapping;
				i++;
			}
		}
		else
		{
			if (data[j] > data[end])
			{
				swapping = data[i + 1];
				data[i + 1] = data[j];
				data[j] = swapping;
				i++;
			}
		}
		j++;
	}

	//swap pivot point with the less/greater boundary element
	swapping = data[i + 1];
	data[i + 1] = data[end];
	data[end] = swapping;

	return i + 1;
}

void QuickSort(int* data, int begin, int end, int order)
{
	int pivot;
	if (begin < end)
	{
		pivot = Split(data, begin, end, order);
		QuickSort(data, begin, pivot - 1, order);
		QuickSort(data, pivot + 1, end, order);
	}
}