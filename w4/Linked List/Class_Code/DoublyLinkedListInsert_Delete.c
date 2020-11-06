/* Tanvir Ahmed
CS1
This code implements doubly linked list insertions and deletion*/

#include<stdio.h>
#include<stdlib.h>

//defining the node structure
typedef struct node
{
  int data;
  struct node *prev, *next;
} node;


/*takes root of a linked list and insert item to the front of the list.
Returns the root of the list after insertion
*/
node* insert_front(node *root, int item)
{
	node *t;
	node *temp;
	temp= (node *) malloc(sizeof(node));
	temp->data=item;
	temp->prev = NULL;
  //putting temp before root
  //if root is null, temp->next will be null too
	temp->next=root; 

//adjust previous if root is not NULL
	if(root!=NULL)
    root->prev=temp;

    //update the root
    root = temp;

    return root;
}

/*takes root of a linked list and insert item to the end of the list.
Returns the root of the list after insertion
*/
node* insert_end(node* root, int item)
{
	node *t;
	node *temp;
	temp=(node *) malloc( sizeof(node));
	temp->data=item;
	temp->next=NULL;

  //if root ==NULL, there should not be anyone before temp
	if(root==NULL)
	{
	     temp->prev = NULL;
	     root=temp;
    }
	else //we need to traverse to go to the end of the list
	{
 	      t=root;
	      while(t->next!=NULL)
            t=t->next;

        //just join temp to the end and adjust temp->prev
	      t->next=temp;
        temp->prev = t;
	}
  return root;

}

/*takes root of a linked list and delete the first occurance of the item from the the list.
Returns the root of the list after deletion
*/
node* DelListDoubly(node* root, int item)
{
	node *t;
	node *temp;
	if(root==NULL)
		return root; //return as nothing to do
  //if the item is at the root
	if(root->data==item)
	{
		temp=root;
		root=root->next;
    //new condition for doubly compared to singly
		if (root != NULL) 
          root -> prev = NULL;
		free(temp);
		return root;
	}
  //item is not at the root. So, we need to traverse and find it
	t=root;
	while(t->next!=NULL && t->next->data != item)
		t=t->next;

//could not find the item as t reached to the end. So, return
	if(t->next==NULL) 
		return root;
  
  //Found the item
	temp=t->next;
	t->next=t->next->next;
    if (t->next)               //new condition for doubly
       t->next->prev = t;

	free(temp);
	return root;
}

void display(node* t)
{
  printf("\nPrinting your link list.......");

	while(t!=NULL)
	{
		printf("%d ",t->data);
		t=t->next;
	}

}

int main()
{
	node* root=NULL;
	node *t,del;
	int ch,ele,v;
	while(1)
	{
		printf("\nMenu: 1. insert at front, 2. insert at end, 3. Delete 4. exit: ");
	    scanf("%d",&ch);
		if(ch==4)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d",&ele);
			root = insert_front(root, ele);
		
			display(root);
		}
		if(ch==2)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d",&ele);
			root = insert_end(root, ele);
			display(root);
		}
	  if(ch==3)
	  {
		 printf("\nEnter info which u want to DELETE: ");
		 scanf("%d",&ele);
		 root=DelListDoubly(root, ele);
		 display(root);


	  }
	}
	return 0;
}
