#include <stdio.h>

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void selectionSort(int arr[], int n)
{
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
	    printf("\nIteration# %d\n",i+1);
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;
		// Swap the found minimum element with the first element
		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;

		printArray(arr, n);
	}
}


int main()
{
    int arr[] = { 5,	8,	3,	1,	4,	7,	6,	2};
    int n = 8; //size of the array

     printArray(arr, n);

    selectionSort(arr, n);

    printArray(arr, n);

    return 0;
}
