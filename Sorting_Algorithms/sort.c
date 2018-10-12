// File to hold all sorting functions - Jared Johansson

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "queue.h"
#include <limits.h>

// swap two indecies of an array
void swap(DATA_TYPE *a, int x, int y)
{
  DATA_TYPE temp = a[x];
  a[x] = a[y];
  a[y] = temp;
}

// Best O(n), Worst O(n^2)
void bubbleSort(DATA_TYPE *a, int n)
{
  // go is to determine if list is already sorted
  int i, go = 1;

  if (a == NULL || n <= 1)
    return;

  // Will leave sorted end out of next pass by modifying n
  while (n > 1 && go)
  {
    go = 0;
    // Check entire unsorted section, subtracting 1 from n to stay in array
    for (i = 0; i < n - 1; i++)
      if (a[i] > a[i + 1])
      {
        swap(a, i, (i + 1));
        go = 1;
      }
    n--;
  }
}

// Best O(n^2), Worst O(n^2)
void selectionSort(DATA_TYPE *a, int n)
{
  int i, j = 0, minIndex;

  if (a == NULL || n <= 1)
    return;

  // O(n)
  for (; n > 1; n--, j++)
  {
    // Start pass after sorted area
    minIndex = j;

    // Find smallest number, O(n)
    for (i = j; i < n + j - 1; i++)
      if (a[minIndex] > a[i + 1])
        minIndex = i + 1;

    swap(a, minIndex, j);
  }
}

// Best O(n), Worst O(n^2)
void insertionSort(DATA_TYPE *a, int n)
{
  int i, j;
  DATA_TYPE t;

  if (a == NULL || n <= 1)
    return;

  for (i = 1; i < n; i++)
  {
    j = i;
    t = a[j];
    while (a[j-1] > t && j >= 1)
    {
      a[j] = a[j-1];
      j--;
    }
    a[j] = t;
  }
}

// Best O(MAX{n, m}), Worst O(n + m) where m is the size of the buckets[]
// Both mean the same, runtime is whichever is larger
void countingSort(DATA_TYPE *a, int n)
{
  int *buckets, min = INT_MAX, max = INT_MIN, j, i, size;

  if (a == NULL || n <= 1)
    return;

  // Find min and max values of array, O(n)
  for (i = 0; i < n; i++)
  {
    if (a[i] < min)
      min = a[i];
    if (a[i] > max)
      max = a[i];
  }

  size = max - min;
  if ((buckets = calloc(size, sizeof(int))) == NULL)
  {
    printf("ERROR: Not enough memory!\n");
    return;
  }

  // Place into buckets, O(n)
  for (i = 0; i < n; i++)
    buckets[a[i] - min]++;

  // Remove from buckets, O(n)
  for (i = 0, j = 0; i < size; i++)
    while (buckets[i] != 0)
    {
      a[j++] = min + i;
      --buckets[i];
    }

  free(buckets);
}

// Best O(nlogm), Worst O(nlogm)
// Where m is the number of digits in highest number
void radixSort(DATA_TYPE *a, int n)
{
  int i, mult = 1, max = 0, index;
  Node **buckets, *temp;

  if (a == NULL || n <= 1)
    return;

  if ((buckets = malloc(sizeof(Node *) * 10)) == NULL)
  {
    printf("ERROR: Not enough memeory!\n");
    return;
  }

  // Adjustable for size of largest int, O(C)?
  do
  {
    mult = mult * 10;
    // Place into linked lists, O(n)
    for (i = 0; i < n; i++)
    {
      index = (a[i] / (mult / 10)) % mult;
      //buckets[index] = insertNodeEnd(buckets[index], a[i]);
      if (max < a[i])
        max = a[i];
    }

    // Remove from linked lists, O(n)
    for (i = 0, index = 0; index < 10; index++)
    {
      while (buckets[index] != NULL)
      {
        a[i++] = buckets[index]->data;
        temp = buckets[index];
        buckets[index] = buckets[index]->next;
        free(temp);
      }
    }
  }while ((max / mult) > 0);

  for (i = 0; i < 10; i++)
    free(buckets[i]);
  free(buckets);
}

// Best O(n^2), Worst O(n^2)??
void bucketSort(DATA_TYPE *a, int n )
{
  int i, index, temp = 0, size = 1, mult = 1;
  Node **buckets, *aux;

  if (a == NULL || n <= 1)
    return;

  if ((buckets = calloc(10, sizeof(Node *))) == NULL)
  {
    printf("ERROR: Not enough memory!\n");
    return;
  }

  // get largest number and its size, O(n)
  for (i = 0; i < n; i++)
    temp = (temp < a[i]) ? a[i] : temp;

  //printf("Largest number: %d ", temp);

  while (temp > 9)
  {
    temp = temp / 10;
    mult *= 10;
  }

  //printf("& mult is: %d\n", mult);

  // place into buckets
  for (i = 0; i < n; i++)
  {
    index = a[i] / mult % 10;
    buckets[index] = insertNodeEnd(buckets[index], a[i]);
    //printLinkedList(buckets[index]);
  }

  //printf("sssssort\n");
  // Sort buckets accending
  for (i = 0; i < 10; i++)
  {
    buckets[i] = sortAccending(buckets[i]);
    //printLinkedList(buckets[i]);
  }

  // remove from buckets
  for (i = 0, index = 0; index < 10; index++)
  {
    while (buckets[index] != NULL)
    {
      a[i] = buckets[index]->data;
      aux = buckets[index];
      buckets[index] = buckets[index]->next;
      free(aux);
      i++;
    }
  }

  //printf("removed?\n");
  free(buckets);
}

// Best O(nlogn), Worst O(nlogn)
DATA_TYPE *mergeSort(DATA_TYPE *a, int n)
{
  int i, j, k, mid = n / 2;
  DATA_TYPE *new, *one, *two;

  if (a == NULL)
    return NULL;
  if (n <= 1)
    return a;

  // O(logn)? cutting in half
  one = mergeSort(a, mid);
  two = mergeSort((a + mid), (n - mid));

  if ((new = malloc(sizeof(DATA_TYPE) * n)) == NULL)
  {
    printf("ERROR: Not enough memory!\n");
    return NULL;
  }

  //printf("one = %p, two = %p, mid = %d\n", one, two, mid);

  // O(n)
  for (j = 0, k = 0, i = 0; i < n; i++)
  {
    // Both indecies inbounds
    if (j < mid && k < (n-mid))
    {
      if (one[j] < two[k])
        new[i] = one[j++];
      else
        new[i] = two[k++];
    }
    // If one is out of bounds, fill with other
    else if (j >= mid)
      new[i] = two[k++];
    else
      new[i] = one[j++];
  }

  // O(n)
  for (i = 0; i < n; i++)
  {
    a[i] = new[i];
    //printf("a[%d] = %d\n", i, a[i]);
  }//printf("\n");

  free(new);
  return a;
}

//
void quickSort(DATA_TYPE *a, int n)
{
  int i, pivot, left, right;

  if (a == NULL)
    return;

  // Faster for very large lists
  if (n <= 15)
  {
    bubbleSort(a, n);
    return;
  }

  // Always uses left most index
  pivot = a[0];
  left = 1;
  right = n - 1;

  // Looking through array and swapping
  while (left < right)
  {
    if (a[left] <= pivot)
      left++;
    if (a[right] > pivot )
      right--;
    if (a[left] > pivot && a[right] <= pivot)
    {
      swap(a, left, right);
      left++;
      right--;
    }
  }

  if (a[0] > a[right])
    swap(a, 0, right);

  quickSort(a, right);
  quickSort(a + left, n - left);
}

int main (void)
{
  int i = 0, k;
  DATA_TYPE array[1000] = {0};
  FILE *ifp;

  if ((ifp = fopen("Array1000.txt", "r")) == NULL)
  {
    printf("ERROR: Failed to open file!\n");
    exit(0);
  }

  while (fscanf(ifp, "%d", &k) != EOF)
  {
    //printf("k = %d and ", k);
    array[i] = k;
    //printf("array[%d] = %d\n", i, array[i]);
    i++;
  }

  //DATA_TYPE [10] = {34, 179, 826, 256, 108, 329, 244, 621, 233, 402};
  quickSort(array, 1000);

  for (i = 0; i < 1000; i++)
    printf("array[%d] = %d\n", i, array[i]);

  fclose(ifp);

  return 0;
}
