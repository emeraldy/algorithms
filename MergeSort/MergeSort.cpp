#include "MergeSort.h"

void MergeSort(int* data, int begin, int end, int order)
{
    if (begin < end)
    {
        int splitPoint = (begin + end) / 2;
        MergeSort(data, begin, splitPoint, order);
        MergeSort(data, splitPoint + 1, end, order);
        Sort(data, begin, splitPoint, end, order);
    }
}

void Sort(int* data, int head, int mid, int tail, int order)
{
    int sizeFirstHalf = mid - head + 1;
    int sizeSecondHalf = tail - (mid + 1) + 1;
    int* tempFirstHalf = new int[sizeFirstHalf];//temporary store for the data in question
    int* tempSecondHalf = new int[sizeSecondHalf];
    //copy the data in question to the temporary store
    for (int i = head, j = 0; i <= mid; i++, j++)
        tempFirstHalf[j] = data[i];
    for (int i = mid + 1, j = 0; i <= tail; i++, j++)
        tempSecondHalf[j] = data[i];


    //sort in ascending order
    int indexTempFirst = 0;
    int indexTempSecond = 0;
    int indexData = head;
    while (1)
    {
        if (order == ASCEND)
        {
            if (tempFirstHalf[indexTempFirst] > tempSecondHalf[indexTempSecond])
            {
                data[indexData] = tempSecondHalf[indexTempSecond];
                indexTempSecond++;
            }
            else
            {
                data[indexData] = tempFirstHalf[indexTempFirst];
                indexTempFirst++;
            }
        }
        else
        {
            if (tempFirstHalf[indexTempFirst] < tempSecondHalf[indexTempSecond])
            {
                data[indexData] = tempSecondHalf[indexTempSecond];
                indexTempSecond++;
            }
            else
            {
                data[indexData] = tempFirstHalf[indexTempFirst];
                indexTempFirst++;
            }
        }
        indexData++;

        //check if either half reaches its sentinel
        if (indexTempFirst == sizeFirstHalf)//first half reaches sentinel
        {
            //copy the remaining of second half back to data
            for (; indexTempSecond < sizeSecondHalf; indexTempSecond++, indexData++)
                data[indexData] = tempSecondHalf[indexTempSecond];
            break;
        }
        else if (indexTempSecond == sizeSecondHalf)//second half reaches sentinel
        {
            //copy the remaining of first half back to data
            for (; indexTempFirst < sizeFirstHalf; indexTempFirst++, indexData++)
                data[indexData] = tempFirstHalf[indexTempFirst];
            break;
        }
    }

    delete[] tempFirstHalf;
    delete[] tempSecondHalf;
}