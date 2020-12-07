//Written By jesus Ugarte
//Lab Exam 2

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode
{
    int income;
    int count;
    struct treeNode *left, *right;
}treeNode;


treeNode* createTreeNameNode(int income, int count);
treeNode* insert( treeNode *root, treeNode *element);
void traverse_print(treeNode *root);
void traverse_Odd(treeNode *root);
int traverse_Highest_Income(treeNode *root);
void traverse_FindCount(treeNode *root, int income);
int is_identical (treeNode* root1, treeNode* root2);



int main(void)
{
    //Opening File
    FILE *fp = fopen("in.txt", "r");
    treeNode *my_root = NULL, *temp_node;
    int n, i, income, count;
   
    //Getting numebr of people
    fscanf(fp,"%d", &n);

    //Iterate n ammount of times and Building Tree
    for(i = 0; i<n; i++)
    {
        //Scanning Values for income and count
        fscanf(fp, "%d", &income);
        fscanf(fp, "%d", &count);

        //Creating Node
        temp_node = createTreeNameNode(income, count);

        //Inserting node
        my_root = insert(my_root, temp_node);
    }
    printf("\nTree constructed from the file");

    //Printing all Values of Tree in Order 
    printf("\nIn-Order:");
    traverse_print(my_root);

    //Printing Values of Tree with only odd number of people count
    printf("\nIncomes with Odd number of poeple count: ");
    traverse_Odd(my_root);

    //Finding hisghest salary first and then looking for count with the provided high income
    printf("\nTotal number of people with the highest income:");
    int value = traverse_Highest_Income(my_root);
    traverse_FindCount(my_root, value); 

    //Making Identical Tree Function
    printf("\n\n%d", is_identical(my_root, my_root));

    return 0;
}

//This Fucniton return 1 f both functions are identical
int is_identical(treeNode* root1, treeNode* root2) 
{
    // Checking if both roots are equal
    if (root1 == NULL && root2 == NULL) 
        return 1; 

    else if (root1 != NULL && root2 == NULL) 
        return 0; 

    else if (root1 == NULL && root2 != NULL) 
        return 0; 

    else 
    {   
        //If Contents of income are the same return 1
        if (root1->income == root2->income && is_identical(root1->left, root2->left) && is_identical(root1->right, root2->right)) 
            return 1; 
        
        //If contents of counts are the same return 1
        if (root1->count == root2->count && is_identical(root1->left, root2->left) && is_identical(root1->right, root2->right)) 
            return 1; 

        //If it reaches here that means that both trees are not identical
        else
            return 0; 
    } 
}



//Print vount value of nod ewith given income
void traverse_FindCount(treeNode *root, int income) 
{
    // Only traverse the node if it's not null.
    if (root != NULL) 
    {   
        traverse_FindCount(root->left, income); // Go Left.
        if(root->income == income)
            printf(" %d", root->count); // Print the root.
        traverse_FindCount(root->right, income); // Go Right.
    }
}

//Finding values with largest income and returning its value
int traverse_Highest_Income(treeNode *root) 
{
    if(root == NULL) 
        return 0;

    int res = root->income;
    int lres = traverse_Highest_Income(root->left);
    int rres = traverse_Highest_Income(root->right);

    if(lres > res)
        res = lres;
    if (rres > res)
        res = rres;

    return res;
}

//Printing Values of with Odd number of people
void traverse_Odd(treeNode *root) 
{
    // Only traverse the node if it's not null.
    if (root != NULL) 
    {   
        traverse_Odd(root->left); // Go Left.
        if(!(root->count % 2 == 0))
            printf(" %d", root->income); // Print the root.
        traverse_Odd(root->right); // Go Right.
    }
}

//Printing values of Tree in In Order Form
void traverse_print(treeNode *root) 
{
    // Only traverse the node if it's not null.
    if (root != NULL) 
    {   
        traverse_print(root->left); // Go Left.
        printf(" (%d, %d),", root->income, root->count); // Print the root.
        traverse_print(root->right); // Go Right.
    }
}

//creating Node
treeNode* createTreeNameNode(int income, int count) 
{
    // Allocate space for the node, set the fields.
    treeNode* temp;
    temp = (struct treeNode*)malloc(sizeof(treeNode));
    temp->income = income;
    temp->count = count;
    temp->left = NULL;
    temp->right = NULL;
    return temp; // Return a pointer to the created node.
}

//Inserting Node
treeNode* insert( treeNode *root, treeNode *element) 
{
    // Inserting into an empty tree.
    if (root == NULL)
        return element;
    
    else 
    {
        // element should be inserted to the right.
        if (element->income > root->income) 
        {
            // There is a right subtree to insert the node.
            if (root->right != NULL)
                root->right = insert(root->right, element);
            // Place the node directly to the right of root.
            else
                root->right = element;
        }

        // element should be inserted to the left.
        else 
        {
            // There is a left subtree to insert the node.
            if (root->left != NULL)
                root->left = insert(root->left, element);

            // Place the node directly to the left of root.
            else
                root->left = element;
        }
        // Return the root pointer of the updated tree.
        return root;
    }
}