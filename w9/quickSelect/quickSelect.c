#include <stdio.h>
#include<stdlib.h>
#define SIZE 6


int quickselect(int* numbers, int low, int high, int rank);
int partition(int* vals, int low, int high);
void printArray(int* numbers, int length);
void swap(int *a, int *b);


int main() {

    int arr[6] = {9, 10, 2, 6, 7, 1};

    printf("Here is the original array:\n  ");
    printArray(arr, SIZE); //just printing the array.

    // Get the rank of element they want.
    int rank;
    printf("Which ranked element do you want?: ");
    scanf("%d", &rank);
    if(rank<=0 || rank>SIZE)
    {
        printf("Invalid rank\n");
    }
    else
    {
        // Get the answer and print it out.
        int answer = quickselect(arr,0,SIZE-1, rank);
        printf("The %d smallest element is %d\n", rank, answer);

    }



     return 0;
}


// Pre-condition: low and high are valid indexes into numbers and rank is
//                in between 1 and high-low+1, inclusive.
// Post-condition: The rank smallest element within numbers[low...high]
//                 will be returned. Also, some elements within numbers may
//                 change positions.
int quickselect(int* numbers, int low, int high, int rank) {

    //only number in search name
    if (low == high)
        return numbers[low];

    //partition the array
    int split = partition(numbers, low, high);

    //The partition element is the correct one 
    if(rank -1 == split)
        return numbers[split];

    //looking for a a smaller element than the partition element, look to the left
    else if(rank -1 < split)
        return quickselect(numbers, low, split -1 , rank);

    //looking for a larger element than the partition element, look fo right
    else
        return quickselect(numbers, split+1, high, rank);
}


// Pre-condition: low and high are valid indexes into values
// Post-condition: Returns the partition index such that all the values
//                 stored in vals from index low to until that index are
//                 less or equal to the value stored there and all the values
//                 after that index until index high are greater than that
//                 value.
int partition(int* vals, int low, int high) {

    int temp;
    int i, lowpos;

    // A base case that should never really occur.
    if (low == high) return low;

    // Pick a random partition element and swap it into index low.
    i = low + rand()%(high-low+1);
    temp = vals[i];
    vals[i] = vals[low];
    vals[low] = temp;

	// Store the index of the partition element.
	lowpos = low;

	// Update our low pointer.
	low++;

	// Run the partition so long as the low and high counters don't cross.
	while (low <= high) {

		// Move the low pointer until we find a value too large for this side.
		while (low <= high && vals[low] <= vals[lowpos]) low++;

		// Move the high pointer until we find a value too small for this side.
		while (high >= low && vals[high] > vals[lowpos]) high--;

		// Now that we've identified two values on the wrong side, swap them.
		if (low < high)
		   swap(&vals[low], &vals[high]);
	}

	// Swap the partition element into it's correct location.
	swap(&vals[lowpos], &vals[high]);

	return high; // Return the index of the partition element.
}

// Swaps the values pointed to by a and b.
void swap(int *a, int *b) {
     int temp = *a;
     *a = *b;
     *b = temp;
}

//Prints a given array
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}



