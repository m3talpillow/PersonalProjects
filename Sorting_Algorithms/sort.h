#ifndef __SORT_H
#define __SORT_H

typedef int DATA_TYPE;
#define DATA_C "%d"

void swap(DATA_TYPE *, int);
void bubbleSort(DATA_TYPE *, int);
void selectionSort(DATA_TYPE *, int);
void countingSort(DATA_TYPE *, int);
void radixSort(DATA_TYPE *, int);
void bucketSort(DATA_TYPE *, int);
DATA_TYPE *mergeSort(DATA_TYPE *, int);
void quickSort(DATA_TYPE *, int);

#endif // __SORT_H
