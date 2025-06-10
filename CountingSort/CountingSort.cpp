#include"CountingSort.h"

void CountingSort(int* data, int size, int valueCount, int min, int order)
{
	int* sorted = new int[size];//store sorted data
	int* counter = new int[valueCount];//counter for each value in the range

	//count the number of each different value
	for (int i = 0; i < valueCount; i++)//initialise counter to 0
	{
		counter[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		counter[data[i] - min]++;//(data - min) to get its rank in the range 
	}

	//compute accumulated number of values less than or equal to a value
	for (int i = 1; i < valueCount; i++)
	{
		counter[i] += counter[i - 1];
	}

	//sort
	for (int i = size - 1; i >= 0; i--)
	{
		sorted[counter[data[i] - min] - 1] = data[i];//NOTE: array index starts with 0 so the i'th greatest value should be indexed by i-1
		counter[data[i] - min]--;
	}

	//transfer sorted back to the input array
	for (int i = 0; i < size; i++)
	{
		if (order == ASCEND)
		{
			data[i] = sorted[i];
		}
		else
		{
			data[i] = sorted[size - 1 - i];
		}
	}

	//clean up
	delete[] sorted;
	delete[] counter;
}