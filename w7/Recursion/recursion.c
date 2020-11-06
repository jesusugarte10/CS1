/*
Jesus Ugarte
University Of Central Florida
implement Recursive calls in linked list
*/

#include<stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

struct node {
     int data;
     struct node  *next;
};

struct node* insert(struct node* list,int d );
struct node* del(struct node* list,int d );
void print( struct node *list);
void freeList(struct node* list);
void copy ( struct node *q, struct node **s );

int main(void) 
{
    atexit(report_mem_leak);

    int number = 0, choice=0;
    struct node *pList=NULL;
    struct node *nList = NULL;

    // Let the user add values until they enter -1.
    while(choice!= 4)
    {
        // Get the operation.
        printf("Do you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
        scanf("%d", &choice);

        printf("Your choice is %d\n", choice);

        // Execute the operation.
        if (choice == 1)
        {
           // Get the number.
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
                    // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            printf("\n");
        }
        else if (choice == 2)
        {    // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
                    // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            printf("\n");
        }
        else if (choice == 3)
        {
            if (nList)
                freeList(nList);

            copy(pList, &nList); //passing reference of nList as it is not returning anything
            
            // Look at the list.
            printf("Items in NEW linked list: ");
            print(nList);
            printf("\n");
        }
        else
        {
              break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("\nBye..\n");
    return 0;
}

struct node* insert(struct node* list,int d )
{
    //base case
    if (list==NULL || d <= list->data)
    {
        struct node* pNew = (struct node*)(malloc(sizeof(struct node)));
        pNew->data = d;
        pNew->next = list;
        return pNew;
    }
    //recursive case
    list->next = insert(list->next, d);
    return list;
}

struct node* del(struct node *list, int d) //deletes first instance that matches d
{
    //base case: list in null
    if(list == NULL)
        return NULL;

    //base case 2: dound  the item!
    if(list->data == d)
    {
        struct node* rest = list->next;
        free(list);
        return rest;
    }

    //recursive case
    list->next = del(list->next, d);
    return list;
}

void freeList(struct node *list)
{
    //base case: list is null
    if(list == NULL)
        return;
    
    //recursive case: free the rest of the list
    if(list->next != NULL)
    {
        freeList(list->next);
    }

    //free current node
    free(list);
}

void print(struct node *list)
{

    //base case: list is null
    if (list == NULL)
        return;

    //print lowest to highest
    printf("-->%d", list->data);

    //recursive case:: pritn the rest of the list
    if(list->next != NULL)
    {
        print(list->next);
    }

    //If I put print here it will print in reverse order 
}

void copy ( struct node *q, struct node **s )
{
    //base case
    if (q == NULL)
        return;

    //assign values here q->data
    *s = malloc(sizeof(struct node));
    (*s)->data = q->data;

    //recursive case:: copy the rest of the list
    copy(q->next, &(*s)->next);
}