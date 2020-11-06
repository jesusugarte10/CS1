#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct queue{
    struct  node* front;
    struct  node* back;
};


//Function prototypes
void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);
void displayQueue(struct queue* qPtr);

int main()
{
    //Allocate Space for out queue
    struct queue* qPtr = (struct queue*)malloc(sizeof(struct queue));
    init(qPtr);

    int choice;
    int data;

    while(1)
    {
        printf("\n1. Insert item to queue \n2. Delete element from queue \n3. Display all elements in queue \n4. Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\n what do you want to put in?\n");
            scanf("%d", &data);
            enqueue(qPtr, data);
            break;
        case 2:
            data = dequeue(qPtr);
            if (data != -1)
            {
                printf("\n%d Deleted from queue\n", data);
                displayQueue(qPtr);
            }    
            break;
        case 3:
            displayQueue(qPtr);
            break;
        case 4:
            exit(1);
        }
        

    }
    return 0;
}

int enqueue(struct queue* qPtr, int val)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL)
    return 0;

    temp->data = val;
    temp->next = NULL;

    //Case1: queue is Not empty, there is a current back
    if (qPtr->back != NULL)
        qPtr->back->next = temp;

    qPtr->back = temp;

    //case 2: queue is empty
    if(qPtr->front == NULL)
    qPtr->front = temp;
    return 1;

}

int dequeue(struct queue* qPtr)
{
    struct node* tmp;
    int retval;

    //check if the queue is empty
    if (empty(qPtr))
        return -1;

    retval = front(qPtr);
    tmp = qPtr->front;
    qPtr->front = qPtr->front->next;

    //if deleting this node makes the queue empty, change the back as well
    if (qPtr->front == NULL)
    {
        qPtr->back = NULL;
    }

    free(tmp);
    return retval;
}

void displayQueue(struct queue* qPtr)
{
    struct queue* current = qPtr->front;
    while (current)
    {
        current = current->next;
    }
}

//Initiate the queue to NULL
void init(struct queue* qPtr)
{
    qPtr->front = NULL;
    qPtr->back = NULL;
}

int empty(struct queue* qPtr)
{
    return qPtr->front == NULL && qPtr->back == NULL;
}

int front (struct queue* qPtr)
{
    if(qPtr->front != NULL)
        return qPtr->front->data;

    else
    {
        return -1;
    }
    
}






