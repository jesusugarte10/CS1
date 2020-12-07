/* COP 3502C Assignment 3
This program is written by: Jesus Enrique Ugarte Osta
University of Central Florida*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leak_detector_c.h"

typedef struct monster {
    int id;
    char name[64];
    char element[64];
    int population;
    double weight;
} monster;

typedef struct {
    long long int compares;
    long long int copies;
    long long int split;
} sort_results;

void print_clocks(clock_t clocks);
int compareTo(monster *m1, monster *m2, int criteria);
int isSorted(monster *m, int length, int criteria);
void originalToTemp(monster *Monster, monster *temp, int n);
void swap(monster *arr1, monster *arr2);
void RunAlgorithm(monster *temp, sort_results *results, int n, int criteria, int k);
void MainProgram(monster *Monster, monster *temp, int n, FILE* outFile1, FILE* outFile2, FILE* outFile3, int criteria);
void selectionSort(monster *arr, sort_results *results, int n, int criteria);
void bubbleSort(monster *arr, sort_results *results, int n, int criteria);
void insertionSort(monster *arr, sort_results *results,int i, int n, int criteria);
void quickSort(monster *arr, int low, int high,  sort_results *results, int criteria);
int partition(monster *vals, int low, int high, sort_results *results, int criteria);
void mergeSort(monster *arr, int l, int r, sort_results *results, int criteria, int fast);
void merge(monster *arr, int l, int m, int r,  sort_results *results, int criteria);

int main(void)
{
    atexit(report_mem_leak);

    FILE *outFile1 = fopen("criteria_1.csv", "w");
    FILE *outFile2 = fopen("criteria_2.csv", "w");
    FILE *outFile3 = fopen("criteria_3.csv", "w");

    fprintf(outFile1, "DataSize, SelectionSortCompare, SelectionSortCopy, SelectionSortTime, BubbleSortCompare, BubbleSortCopy, BubbleSortTime, InsertionSortCompare, InsertionSortCopy, InsertionSortTime, MergeSortCompare, MergeSortCopy, MergeSortTime, Merge_InsertionSortCompare, Merge_InsertionSortCopy, Merge_InsertionSortTime, QuickSortCompare, QuickSortCopy, QuickSortTime\n");
    fprintf(outFile2, "DataSize, SelectionSortCompare, SelectionSortCopy, SelectionSortTime, BubbleSortCompare, BubbleSortCopy, BubbleSortTime, InsertionSortCompare, InsertionSortCopy, InsertionSortTime, MergeSortCompare, MergeSortCopy, MergeSortTime, Merge_InsertionSortCompare, Merge_InsertionSortCopy, Merge_InsertionSortTime, QuickSortCompare, QuickSortCopy, QuickSortTime\n");
    fprintf(outFile3, "DataSize, SelectionSortCompare, SelectionSortCopy, SelectionSortTime, BubbleSortCompare, BubbleSortCopy, BubbleSortTime, InsertionSortCompare, InsertionSortCopy, InsertionSortTime, MergeSortCompare, MergeSortCopy, MergeSortTime, Merge_InsertionSortCompare, Merge_InsertionSortCopy, Merge_InsertionSortTime, QuickSortCompare, QuickSortCopy, QuickSortTime\n");
    
    //PROGRAM ONLY WORKS WITH DATA SETS OF 10k to 90K Values
    char* filename[6]= {"10K.txt", "20K.txt", "30K.txt", "40K.txt", "50K.txt", "60K.txt"};

    for(int i = 0; i < 3; i++)//criteria loop
    {
        for(int j = 0; j < 6; j++)//file loop
        {

            FILE *inFile;
            inFile = fopen(filename[j], "r");
            char* getNumber = filename[j];

            int n = (atoi(&filename[j][0])) * 1000 ; //add multiplier
            monster *Monster = malloc(n * sizeof(monster));
            monster *temp = malloc(n * sizeof(monster));

            //Scanning first and fourth Line for name and weight respectively
            for(int k = 0; k < n; k++)
                fscanf(inFile, "%s %*s %*s %lf", Monster[k].name, &Monster[k].weight);
                
            printf("\n========\n");
            printf("Processing Criteria %d and file %s\n", i+1, filename[j]);
            printf("========\n"); 

            MainProgram(Monster, temp, n, outFile1, outFile2, outFile3, i);
            
            fclose(inFile);
            free(Monster);
            free(temp);
        }
    }   

    fclose(outFile1);
    fclose(outFile2);
    fclose(outFile3);
}

void MainProgram(monster *Monster, monster *temp, int n, FILE* outFile1, FILE* outFile2, FILE* outFile3, int i)
{
    clock_t start_cpu, end_cpu;

    sort_results results;

    char* algorithms[6] = {"selection", "bubble", "insertion", "merge", "merge/insertion", "quick"};
    char* criteriaName[3] = {"name", "weight", "name and weight"};

    if(i == 0)
        fprintf(outFile1, "%d", n);
    if(i == 1)
        fprintf(outFile2, "%d", n);
    if(i == 2)
        fprintf(outFile3, "%d", n);
    
    //k equals number of algorithms to analyze
    for(int k = 0; k < 6; k++)
    {   
        //restore temp array with original array
        originalToTemp(Monster, temp, n);
        results.compares = 0;
        results.copies = 0;
        results.split = 0;

        printf("Array Status: not sorted by %s before calling %s sort\n", criteriaName[i], algorithms[k]);

        start_cpu = clock();
        RunAlgorithm(temp, &results, n, i, k);
        end_cpu = clock();

        if(isSorted(temp, n, i) == 1)
            printf("Array Status: sorted by %s after returning from %s sort\n", criteriaName[i], algorithms[k]);
        
        print_clocks(end_cpu - start_cpu);
        printf("Total number of comparisons: %lld\n", results.compares);
        printf("Total number of copy operations: %lld\n", results.copies);

        //Printing Files
        if(i == 0)
            fprintf(outFile1, ",%lld, %lld, %lf", results.compares, results.copies, ((double)(end_cpu - start_cpu)/ CLOCKS_PER_SEC ));
        if(i == 1)
            fprintf(outFile2, ",%lld, %lld, %lf", results.compares, results.copies, ((double)(end_cpu - start_cpu)/ CLOCKS_PER_SEC ));
        if(i == 2)
            fprintf(outFile3, ",%lld, %lld, %lf", results.compares, results.copies, ((double)(end_cpu - start_cpu)/ CLOCKS_PER_SEC ));
    }

    if(i == 0)
        fprintf(outFile1, "\n");
    if(i == 1)
        fprintf(outFile2, "\n");
    if(i == 2)
        fprintf(outFile3, "\n");
}

void RunAlgorithm(monster *temp, sort_results *results, int n, int criteria, int k)
{
    if(k == 0)
        selectionSort(temp, results, n, criteria);

    if(k == 1)
        bubbleSort(temp, results, n, criteria);

    if(k == 2)
        insertionSort(temp, results, 1, n, criteria);

    if(k == 3)
        mergeSort(temp, 0, n-1, results, criteria, 0);

    if(k == 4)
        mergeSort(temp, 0, n-1, results, criteria, 1);

    if(k == 5)
        quickSort(temp, 0, n-1, results, criteria);
}

void selectionSort(monster *arr, sort_results *results, int n, int criteria)
{
    int i, j, min_idx;
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;

		for (j = i+1; j < n; j++)
        {   //look for smallest item of array
            if(compareTo(&arr[j], &arr[min_idx], criteria) < 0)
            {   
                min_idx = j;
            }
            results->compares++;
        }
		// Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
        results->copies+=3;
	}
}

void bubbleSort(monster *arr, sort_results *results, int n, int criteria)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {   //compare and lookign for item greater than current index
            if (compareTo(&arr[j], &arr[j+1], criteria) > 0)
            {   //swap if item is greater than idex
                swap(&arr[j], &arr[j+1]);
                results->copies+=3;
            }
            results->compares++;
        }
    }
}

void insertionSort(monster *arr, sort_results *results, int low, int n, int criteria)
{
    int i, j;

    for (i = low; i < n; i++)
    {
        monster item = arr[i];
        results->copies++;

        //Move items that are greater than key, to one position ahead of current position
        for(j=i-1; j>=0; j--)
        {     
            results->compares++;
            if(compareTo(&arr[j], &item, criteria) > 0)
            {   //assigning Values
                arr[j+1] = arr[j];
                results->copies++;
            }
            else
                break;
        }
        arr[j+1] = item;
        results->copies++;
    }
}

void merge(monster *arr, int l, int m, int r,  sort_results *results, int criteria)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // create temp arrays 
    monster *L = (monster*) malloc(n1*sizeof(monster));
    monster *R = (monster*) malloc(n2*sizeof(monster));

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        results->copies++;
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1+ j];
        results->copies++;
    }
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {   
        if (compareTo(&L[i], &R[j], criteria) <= 0)
        {
            arr[k] = L[i];
            results->copies++;
            i++;
            
        }
        else
        {
            arr[k] = R[j];
            results->copies++;
            j++;
        }
        k++;
        results->compares++;
    }
    //Copy the remaining elements of L[]
    while (i < n1)
    {
        arr[k] = L[i];
        results->copies++;
        i++;
        k++;
    }
    //Copy the remaining elements of R[]
    while (j < n2)
    {
        arr[k] = R[j];
        results->copies++;
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(monster *arr, int l, int r, sort_results *results, int criteria, int fast)
{
    if (l < r)
    {
        //get mid point
        int m = (l+r)/2;
        // Sort first and second halves
        mergeSort(arr, l, m, results, criteria, fast);
        mergeSort(arr, m+1, r, results, criteria, fast);
        //merge
        merge(arr, l, m, r, results, criteria);
    }
    else if(fast == 1 && (l - r) <= 25)
        insertionSort(arr, results, l, r, criteria);
}

int partition(monster *arr, int low, int high, sort_results *results, int criteria)
{
    // Pick a random partition element and swap it into index low.
    int i = low + rand()%(high-low+1);
    swap(&arr[low], &arr[i]);
    results->copies+=3;
    results->compares++;

    int lowpos = low; //here is our pivot located.
    low++; //our starting point is after the pivot.

    // Run the partition so long as the low and high counters don't cross.
    while(low<=high)
    {
        // Move the low pointer until we find a value too large for this side.
        while(low<=high && compareTo(&arr[low], &arr[lowpos], criteria) <= 0) 
        {
            low++;
            results->compares++;
        }
        // Move the high pointer until we find a value too small for this side.
        while(high>=low && compareTo(&arr[high], &arr[lowpos], criteria) > 0) 
        {
            high--;
            results->compares++;
        }
        // Now that we've identified two values on the wrong side, swap them.
        if (low<high)
        {
            swap(&arr[low], &arr[high]);
            results->copies+=3;
        }
    }

    // Swap the pivot element element into its correct location.
    swap(&arr[lowpos], &arr[high]);
    results->copies+=3;

    return high; //return the partition point

}

void quickSort(monster *arr, int low, int high, sort_results *results, int criteria)
{
    // Only have to sort if we are sorting more than one number
    if (low < high) 
    {
        int split = partition(arr, low, high, results, criteria);
        quickSort(arr, low, split - 1, results, criteria);
        quickSort(arr, split + 1, high, results, criteria);
    }
}

void swap(monster *arr1, monster *arr2)
{
    monster t = *arr1;
    *arr1 = *arr2;
    *arr2 = t;
}

//Copy contents of original array to a temporary array to be sorted
void originalToTemp(monster *Monster, monster *temp, int n)
{
    for(int i = 0; i < n ; i++)
    {
        strcpy(temp[i].name, Monster[i].name);
        temp[i].weight = Monster[i].weight;
    }
}

//prints execution time
void print_clocks(clock_t clocks) 
{
    printf("Total time taken %lf seconds\n", ((double) clocks) / CLOCKS_PER_SEC);
}

//Depending on the criterion, the function should return negative equal or positive
int compareTo(monster *m1, monster *m2, int criteria)
{
    if(criteria == 0)
        return strcmp(m1->name, m2->name);

    else if(criteria == 1)
        return m1->weight - m2->weight;

    else //criteria is == 2
    {   
        // if strings are equal return numbers comparison
        if(compareTo(m1, m2, 0) == 0)
            return compareTo(m1, m2, 1);
        //else return name comparison
        else
            return compareTo(m1, m2, 0);
    }
    return 0;
}

//The function returns 1 if it is sorted and return 0 if the array is not sorted.
int isSorted(monster *arr, int n, int criteria)
{   
    for(int i = 0; i < n-1 ; i++)
    {
        //checkig if number next in index is greater or equal to current index
        if(compareTo(&arr[i], &arr[i+1], criteria) > 0)
            return 0;
    }
    return 1;
}