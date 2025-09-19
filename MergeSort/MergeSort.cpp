#include <memory>
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
    std::shared_ptr<int[]> firstHalf(new int[sizeFirstHalf]);
    std::shared_ptr<int[]> secondHalf(new int[sizeSecondHalf]);
    //copy the data in question to the temporary store
    for (int i = head, j = 0; i <= mid; i++, j++)
    {
        firstHalf[j] = data[i];
    }
    for (int i = mid + 1, j = 0; i <= tail; i++, j++)
    {
        secondHalf[j] = data[i];
    }


    //sort in ascending order
    int indexTempFirst = 0;
    int indexTempSecond = 0;
    int indexData = head;
    while (1)
    {
        if (order == ASCEND)
        {
            if (firstHalf[indexTempFirst] > secondHalf[indexTempSecond])
            {
                data[indexData] = secondHalf[indexTempSecond];
                indexTempSecond++;
            }
            else
            {
                data[indexData] = firstHalf[indexTempFirst];
                indexTempFirst++;
            }
        }
        else
        {
            if (firstHalf[indexTempFirst] < secondHalf[indexTempSecond])
            {
                data[indexData] = secondHalf[indexTempSecond];
                indexTempSecond++;
            }
            else
            {
                data[indexData] = firstHalf[indexTempFirst];
                indexTempFirst++;
            }
        }
        indexData++;

        //check if either half reaches its sentinel
        if (indexTempFirst == sizeFirstHalf)//first half reaches sentinel
        {
            //copy the remaining of second half back to data
            for (; indexTempSecond < sizeSecondHalf; indexTempSecond++, indexData++)
            {
                data[indexData] = secondHalf[indexTempSecond];
            }
            break;
        }
        else if (indexTempSecond == sizeSecondHalf)//second half reaches sentinel
        {
            //copy the remaining of first half back to data
            for (; indexTempFirst < sizeFirstHalf; indexTempFirst++, indexData++)
            {
                data[indexData] = firstHalf[indexTempFirst];
            }
            break;
        }
    }
}