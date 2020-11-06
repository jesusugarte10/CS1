/*
* C Program to Implement an array based linear Queue 
*/
#include <stdio.h>
#include<stdlib.h>
#define MAX 5
#define EMPTY -9999

//defining the structure for the queue
typedef struct Queue
{
  int queue_array[MAX];
  int rear;
  int front;  
}Queue;


//takes the reference of a queue and insert the item in the queue
void enQueue(Queue *q, int add_item)
{
    if (q->rear <MAX)
    {
        q->queue_array[q->rear++] = add_item;
        printf("\nAdded to queue\n");
    }
    else
    {
        printf("Queue Overflow \n");
    }
} /*End of insert()*/

//returning the front item if not empty and increase front
int deQueue(Queue *q)
{
    if(q->front==q->rear)
    {
        printf("\n Empty. \n");
        return EMPTY;
    }
    else
        return q->queue_array[q->front++];
} /*End of delete() */

void display(Queue q)
{
    int i;
    if (q.front == q.rear)
    printf("Queue is empty \n");
    else
    {
        printf("\nQueue is : \n");
        //display the array from front to the rear
        for (i = q.front; i < q.rear; i++)
            printf("%d ", q.queue_array[i]);
        printf("\n\n");
    }
} /*End of display() */


void initQ(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

int main()
{
    int choice;
    int data;
    Queue myQ;

    initQ(&myQ);
  
    while (1)
    {
        printf("1.Insert element to queue \n");
        printf("2.Delete element from queue \n");
        printf("3.Display all elements of queue \n");
        printf("4.Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nWhat data you want to put in the queue?: ");
                scanf("%d", &data);
                enQueue(&myQ,data);
                display(myQ);
                break;
            case 2:
                data = deQueue(&myQ);
                if(data!=EMPTY)
                {
                    printf("\n%d deleted from queue\n", data);                display(myQ);
                }        
                break;
            case 3:
                display(myQ);
                break;
            case 4:
                exit(1);
            default:
                printf("Wrong choice \n");
        } /*End of switch*/
    } /*End of while*/
    return 0;
} /*End of main()*/

