/* Made by Jesus Ugarte
Code to Reverse Linked List and to insert element in a given position
*/

#include<stdio.h>
#include<stdlib.h>


 typedef struct node{
	int data;
	struct node *next;
}node;

//this function takes an item and insert it in the linked list pointed by root.
node*  insert_front(node *root, int item)
{
	node *temp;
	//create a new node and fill-up the node
	temp= (node *) malloc(sizeof(node));
	temp->data=item;
	temp->next=NULL;

	if(root==NULL) //if there is no node in the linked list
        root=temp;
    else //there is an existing linked list, so put existing root after temp
    {
        temp->next = root; //put the existing root after temp
        root = temp; //make the temp as the root!
    }
  return root;

}

node* reverse_List(node* head)
{
	if (head == NULL || head->next ==NULL )
	{
		return head;
	}

	node* main_list = head->next;
	node* reversed_List =head;
	reversed_List->next = NULL;

	while (main_list != NULL)
    {
        node* temp = main_list;
        main_list = main_list->next;

        temp->next = reversed_List;
        reversed_List = temp;
    }
    return reversed_List;

}




void insertToPlace(node * head, int val, int place)
{
    if (head == NULL || place <= 1)
    {
        printf("Invalid Input.");
        return;
    }
    
	//Make tmp and allocate memory to it 
	node* temp = (node*)malloc(sizeof(node));
    //set tmps data to val
	temp->data = val;

    //make count variable, set it to 1
	int count = 1;

	while(count + 1 < place && head->next != NULL)
	{
		// update head  (iterate)
		head = head->next;
        //update count 
		count++;
	}
	temp->next = head->next;
	head->next = temp;


}



void display(node* t)
{
  printf("Printing your link list.......");

	while(t!=NULL)
	{
		printf("%d ",t->data);
		t=t->next;
	}
}


int main()
{
	node *root=NULL; //very important line. Otherwise all function will fail

	int ch, ele, place;

	while(1)
	{
		printf("\nMenu:\n0. exit: \n1. insert at front, \n2. reverse, \n3. Insert at place\n\n");
	    scanf("%d",&ch);
		if(ch==0)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);
			root = insert_front(root, ele);

            display(root);

		}
		if(ch==2)
		{
			root = reverse_List(root);
            printf("\nList Reversed\n");

            display(root);
		}

        if(ch==3)
        {
            printf("Enter data (and Integer) and Place (>1) separated by space: ");
            scanf("%d %d",&ele, &place);
            insertToPlace(root, ele, place);

            display(root);

        }
    }

  return 0;
}
