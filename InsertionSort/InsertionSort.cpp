#include "InsertionSort.h"

void InsertionSort(int data[], int dataSize, int sortOrder)
{
    //sort in ascending order
    for (int i = 1; i < dataSize; i++)
    {
        int j = i - 1;
        int key = data[i];
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }

    if (sortOrder == DESCEND)
    {
        int temp;
        for (int i = 0; i < dataSize / 2; i++)
        {
            temp = data[i];
            data[i] = data[dataSize - 1 - i];
            data[dataSize - 1 - i] = temp;
        }
    }
}