//Written by Jesus Ugarte
//CS1 University Of Central Florida

#include <stdio.h>
#include <stdlib.h>


int isHeap_recursive(int arr[], int i, int n)
{
    //if i is outside of the array range, it means this part is a heap
    if(i >= n || n <= 0)
        return 1;

    //if there is a left child, compere with it
    if((2*i+1) < n)
        if(arr[2*i+1] < arr[i]) // if my left child is smaller than my parent
            return 0;
    
    //If there is a right child, compare with it
    if((2*i+2) < n)
        if(arr[2*i+2] < arr[i]) // if my right child is smaller than my parent
            return 0;

    //recursively check if left and right childern satisfy min heap
    return (isHeap_recursive(arr, 2*i+1, n) && isHeap_recursive(arr, 2*i+2, n));
}

int isHeap_iter(int arr[], int n)
{
    //start from the root, and go till the last Parent
    for(int i = 0; i <= (n-2)/2; i++)
    {
        //if left child is smaller return false
        if(arr[2*i+1] < arr[i])
            return 0;

        //TODO as homework
        //if right child is smaller,return false
        if(arr[2*i+2] < arr[i])
            return 0;
        
        //BUT WAIT!! we need to check is the right child existes, 2*i+2 < n and if right child is smaller, return false
        if((2*i+2) < n)
            return 0;

    }
    return 1;
}



int main(void)
{

    int arr[6] = {12, 13, 14, 15, 110, 115}; //it is heap
    int arr2[6] = {12, 110, 14, 15, 13, 115}; //not min heap

    //Basically and if/else statement
    isHeap_recursive(arr, 0, 6) ? printf("This is a min Heap!") : printf("This is not a min heap!");

    //TODO" check to see if your isheap_iter works
    isHeap_iter(arr,6) ? printf("\nThis is a min Heap!") : printf("\nThis is not a min heap!");

    return 0;
}