// Arup Guha
// 6/26/07
//Modified and updated by Tanvir Ahmed 5/26/2020
// Example of how to implement a queue with an array.
#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1
#define INIT_SIZE 10

// Stores our queue.
struct queue {
    int* elements;
    int front;
    int numElements;
    int queueSize;
};

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);
void displayQueue(struct queue* qPtr);



int main()
{
    int choice;
    int data;

    int i;
    // Allocate space for our queue and initialize it.
    struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
    
    init(MyQueuePtr);

    while (1)
    {
        printf("\n1.Insert element to queue \n");
        printf("2.Delete element from queue \n");
        printf("3. Display all elements of queue \n");
        printf("4.Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("\nWhat data you want to put in the queue?: ");
                scanf("%d", &data);
                enqueue(MyQueuePtr, data);
                displayQueue(MyQueuePtr);
                break;
            case 2:
                data = dequeue(MyQueuePtr);
                if(data!=EMPTY)
                    printf("\n%d deleted from queue\n", data);
                displayQueue(MyQueuePtr);
                break;
            case 3:
                displayQueue(MyQueuePtr);
                break;
            case 4:
                exit(1);
            default:
                printf("Wrong choice \n");
        } /*End of switch*/
    } /*End of while*/
    return 0;
} /*End of main()*/

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: Display the content of the queue.
void displayQueue(struct queue* qPtr)
{
    if(empty(qPtr))
    {
        printf("\nNo data in the Queue...");
        return;
    }
    printf("\nContents in the queue : ");
    if (qPtr->front+qPtr->numElements < qPtr->queueSize)
    {
        for (int i = qPtr->front; i < qPtr->front+qPtr->numElements; i++)
            printf("%d ",qPtr->elements[i]);
    }
    else
    {
        for (int i = qPtr->front; i < qPtr->queueSize; i++)
            printf("%d ",qPtr->elements[i]);
        for (int i = 0; i < (qPtr->front+qPtr->numElements)%qPtr->queueSize; i++)
            printf("%d ",qPtr->elements[i]);
    }

    printf("\n");
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
//                 empty queue.
void init(struct queue* qPtr) {

     // The front index is 0, as is the number of elements.
     qPtr->elements = (int*)malloc(sizeof(int)*INIT_SIZE);
     qPtr->front = 0;
     qPtr->numElements = 0;
     qPtr->queueSize = INIT_SIZE;
}

// Pre-condition: qPtr points to a valid struct queue and val is the value to
//                enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
//                 no change will be made to the queue and 0 will be returned.

// Note: Right now, I don't know how to detect that the realloc failed, so 0
//       does not get returned.

int enqueue(struct queue* qPtr, int val) {

    int i;

    // Regular case where our queue isn't full.
    if (qPtr->numElements != qPtr->queueSize) {

        // Enqueue the current element. Note the use of mod for the wraparound
        // case. Edit the number of elements.
        qPtr->elements[(qPtr->front+qPtr->numElements)%qPtr->queueSize] = val;
        (qPtr->numElements)++;

        // Signifies a successful operation.
        return 1;
    }

    // Case where the queue is full, we must find more space before we enqueue.
    else {

         // Allocate more space!
         qPtr->elements = realloc(qPtr->elements, (qPtr->queueSize)*sizeof(int)*2);

         // Copy all of the items that are stored "before" front and copy them
         // into their new correct locations.
         for (i=0; i<=qPtr->front-1; i++)
             qPtr->elements[i+qPtr->queueSize] = qPtr->elements[i];

         // Enqueue the new item, now that there is space. We are guaranteed that
         // no wraparound is necessary here.
         qPtr->elements[i+qPtr->queueSize] = val;

         // More bookkeeping: The size of the queue as doubled and the number of
         // elements has increased by one.
         (qPtr->queueSize) *= 2;
         (qPtr->numElements)++;

         return 1;
    }

}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
//                 at the front of the queue is deleted from the queue and
//                 returned. Otherwise, -1 is returned to signify that the queue
//                 was already empty when the dequeue was attempted.
int dequeue(struct queue* qPtr) {

    int retval;

    // Empty case.
    if (qPtr->numElements == 0)
        return EMPTY;

    // Store the value that should be returned.
    retval = qPtr->elements[qPtr->front];

    // Adjust the index to the front of the queue accordingly.
    qPtr->front = (qPtr->front + 1)% qPtr->queueSize;

    // We have one fewer element in the queue.
    (qPtr->numElements)--;

    // Return the dequeued element.
    return retval;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int empty(struct queue* qPtr) {
    return qPtr->numElements == 0;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value
//                 stored at the front of the queue is returned. Otherwise,
//                 -1 is returned to signify that this queue is empty.
int front(struct queue* qPtr) {
    if (qPtr->numElements != 0)
        return qPtr->elements[qPtr->front];
    else
        return EMPTY;
}
