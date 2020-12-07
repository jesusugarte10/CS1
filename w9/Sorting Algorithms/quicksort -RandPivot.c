//Modified based on the code of Arup Guha
//Implementation of quick sort.
//This code was written in the class
//and modified with more comments before uploading

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);
int partition(int *vals, int low, int high);
void quickSort(int *numbers, int low, int high);
void printArray(int arr[], int size);
int is_sorted(int values[], int length);

int main()
{
    int arr[6] = {9, 10, 2, 6, 7, 1};
    int maxindex = 5; //as our arrya size is 6, the max index is 5

    printf("Here is the original array:\n  ");
    printArray(arr, 6); //just printing the array.

    quickSort(arr, 0, maxindex); //calling the quick sort function

    if(is_sorted(arr, 6)) //this function could be useful if your array is big
      printf("\nThe array is sorted!\n");
    else
      printf("\nThe array is NOT sorted!\n");

    printf("\nHere is the sorted array:\n  ");
    printArray(arr, 6);//displaying the array after sorting

    return 0;
}

//this function taks an array and its lenght and returns 1 if it is sorted
//returns 0 if the array is not sorted
int is_sorted(int values[], int length) {

    int i;

    // Return false if any adjacent pair is out of order.
    for (i=0; i<length-1; i++)
        if (values[i] > values[i+1])
            return 0;

    return 1;
}

// Swaps the values pointed to by a and b.
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Pre-condition: low and high are valid indexes into values
// Post-condition: Returns the partition index such that all the values
//                 stored in vals from index low to until that index are
//                 less or equal to the value stored there and all the values
//                 after that index until index high are greater than that
//
int partition(int *vals, int low, int high)
{
  // Pick a random partition element and swap it into index low.
  int i = low + rand()%(high-low+1);
  swap(&vals[low], &vals[i]);

  int lowpos = low; //here is our pivot located.

  low++; //our starting point is after the pivot.

// Run the partition so long as the low and high counters don't cross.
  while(low<=high)
  {
    // Move the low pointer until we find a value too large for this side.
    while(low<=high && vals[low]<=vals[lowpos]) low++;

    // Move the high pointer until we find a value too small for this side.
    while(high>=low && vals[high] > vals[lowpos]) high--;

    // Now that we've identified two values on the wrong side, swap them.
    if (low<high)
     swap(&vals[low], &vals[high]);
  }

  // Swap the pivot element element into its correct location.
  swap(&vals[lowpos], &vals[high]);

  return high; //return the partition point
}

// Pre-condition: s and f are value indexes into numbers.
// Post-condition: The values in numbers will be sorted in between indexes s
//                 and f.
void quickSort(int* numbers, int low, int high) {

    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(numbers,low,high);
        quickSort(numbers,low,split-1);
        quickSort(numbers,split+1,high);
    }
}


//Prints a given array
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
