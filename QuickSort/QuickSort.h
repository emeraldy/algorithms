#pragma once

#define ASCEND  1
#define DESCEND 2


int Split(int* data, int begin, int end, int order);
void QuickSort(int* data, int begin, int end, int order);