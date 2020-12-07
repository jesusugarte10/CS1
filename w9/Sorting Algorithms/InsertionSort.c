// C program for insertion sort
#include <math.h>
#include <stdio.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i, item, j;
    for (i = 1; i < n; i++)
    {
         item = arr[i];

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
          for(j=i-1; j>=0; j--)
          {
              if(arr[j]>item)
                arr[j+1] = arr[j];
              else
                break;

          }
          arr[j+1] = item;
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Driver program to test insertion sort */
int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = 5; //size of the array
    printf("Before sorting: ");
    printArray(arr, n);

    insertionSort(arr, n);
    printf("\nAfter sorting: ");
    printArray(arr, n);

    return 0;
}
