/* COP 3502C Assignment 4
This program is written by: Jesus Enrique Ugarte Osta
Unniversity Of Central Florida
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leak_detector_c.h"
#define MAXLEN 51

FILE *outFile;

typedef struct itemNode
{
    char name[MAXLEN];
    int count;
    struct itemNode *left, *right;
}itemNode;

typedef struct treeNameNode
{
    char treeName[MAXLEN];
    struct treeNameNode *left, *right;
    itemNode *theTree;
}treeNameNode;

treeNameNode* createTreeNameNode(char* name);
treeNameNode* insert( treeNameNode *root, treeNameNode *element);
treeNameNode* buildNameTree(treeNameNode *my_root, char* TreeName, char* name, int val);
treeNameNode* SearchNameNode(treeNameNode *root, char* treeName);
itemNode* Insert_Item( itemNode *root, itemNode *element);
void traverse_in_traverse(treeNameNode *root);
void traverse_in_name(treeNameNode *root);
void traverse_in_items(itemNode *root);
void searchItem(treeNameNode *my_root, char* name, char* treeName);
itemNode* Search_Item_Node(itemNode *root, char* treeNameVal);
void freeMemory_items(itemNode *root);
void freeMemory(treeNameNode *root);
int numnodes(itemNode* root);
void get_balance(treeNameNode* root);
void Item_Before(treeNameNode* temp_node, char* name);
int Find_NumberOfPreviousItems(itemNode *root, char* name);
void Count_Tree(treeNameNode* temp_node, char* name);
int Find_Count(itemNode *root);
void Reduce(treeNameNode* my_root, char* name, int val);

//Delete for Item Node
void Delete_node(treeNameNode* my_root, char* treename, char* name);
itemNode* delete(itemNode* root, char* value);
itemNode* parent(itemNode *root, itemNode *node);
int isLeaf(itemNode *node);
int hasOnlyLeftChild(itemNode *node);
int hasOnlyRightChild(itemNode *node);
itemNode* minVal(itemNode *root);

//Delete for Tree Name
void Delete_Name_Main(treeNameNode* my_root, treeNameNode* localized_root, char* treename);
void deleteItemTree(itemNode *root);
treeNameNode* parent_name(treeNameNode *root, treeNameNode *node);
treeNameNode* delete_name(treeNameNode* root, char* value);
int isLeaf_name(treeNameNode *node);
int hasOnlyLeftChild_name(treeNameNode *node);
int hasOnlyRightChild_name(treeNameNode *node);
treeNameNode* minVal_name(treeNameNode *root);

int main(void)
{
    atexit(report_mem_leak);
    FILE* inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");

    treeNameNode *my_root = NULL, *temp_node;

    char treename[MAXLEN], name[MAXLEN], instruction[MAXLEN];
    int nTreeNames, nItems, nQueries, val;

    fscanf(inFile, "%d %d %d", &nTreeNames, &nItems, &nQueries);
    //Creating TreeName Nodes
    for(int i = 0; i < nTreeNames; i++)
    {
        fscanf(inFile, "%s", treename);
        //create new node
        temp_node = createTreeNameNode(treename);
        //insert node
        my_root = insert(my_root, temp_node);
    }

    //Build Name Tree 
    for(int i = 0; i < nItems; i++)
    {
        fscanf(inFile, "%s %s %d", treename, name, &val);
        my_root = buildNameTree(my_root, treename, name, val);
    }

    //TRAVERSE GOES HERE
    traverse_in_name(my_root);
    traverse_in_traverse(my_root); 

    //Query Section
    for(int i = 0; i < nQueries; i++)
    {
        //Getting Query from inFile
        fscanf(inFile, "%s", instruction);

        if(strcmp(instruction, "search") == 0)
        {
            fscanf(inFile, "%s %s", treename, name);
            temp_node = SearchNameNode(my_root, treename);
            searchItem(temp_node, name, treename);
        }
        else if(strcmp(instruction, "item_before") == 0)
        {
            fscanf(inFile, "%s %s", treename, name);
            temp_node = SearchNameNode(my_root, treename);
            Item_Before(temp_node, name);
        }
        else if(strcmp(instruction, "height_balance") == 0)
        {
            fscanf(inFile, "%s", treename);
            temp_node = SearchNameNode(my_root, treename);
            get_balance(temp_node);
        }
        else if(strcmp(instruction, "count") == 0)
        {
            fscanf(inFile, "%s", treename);
            temp_node = SearchNameNode(my_root, treename);
            Count_Tree(temp_node, treename);
        }
        else if(strcmp(instruction, "reduce") == 0)
        {
            fscanf(inFile, "%s %s %d", treename, name, &val);
            temp_node = SearchNameNode(my_root, treename);
            Reduce(temp_node, name, val);
        }
        else if(strcmp(instruction, "delete") == 0)
        {
            fscanf(inFile, "%s %s", treename, name);
            temp_node = SearchNameNode(my_root, treename);
            Delete_node(temp_node, treename, name);
        }
        else if(strcmp(instruction, "delete_name") == 0)
        {
            fscanf(inFile, "%s", treename);
            temp_node = SearchNameNode(my_root, treename);
            Delete_Name_Main(my_root, temp_node, treename);
        }
    }
    freeMemory(my_root);
    fprintf(outFile, "\n");
    fclose(inFile);
    fclose(outFile);
    return 0;
}

//Main Function for Delete Node
void Delete_node(treeNameNode* my_root, char* treename, char* name)
{
    my_root->theTree = delete(my_root->theTree, name);
    fprintf(outFile, "\n%s deleted from %s", name, treename);
}

//Main Function to Delete name 
void Delete_Name_Main(treeNameNode* my_root, treeNameNode* localized_root, char* treename)
{
    //Delete all elements of treeItems First
    deleteItemTree(localized_root->theTree);
    free(localized_root->theTree);
    localized_root->theTree = NULL;

    //Delete treename after
    my_root = delete_name(my_root, treename);
    fprintf(outFile, "\n%s deleted", treename);
}

//deletes Given tree Name
treeNameNode* delete_name(treeNameNode* root, char* value) 
{
    treeNameNode *delnode, *new_del_node, *save_node;
    treeNameNode *par;

    char save_val[MAXLEN];

    delnode = SearchNameNode(root, value); // Get a pointer to the node to delete.
    par = parent_name(root, delnode); // Get the parent of this node.

    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf_name(delnode)) // case 1
    {
        // Deleting the only node in the tree.
        if (par == NULL) 
        {
            free(root); // free the memory for the node.
            return NULL;
        }

        // Deletes the node if it's a left child.
        if (strcmp(value, par->treeName) < 0)
        {
            free(par->left); // Free the memory for the node.
            par->left = NULL;
        }

        // Deletes the node if it's a right child.
        else 
        {
            free(par->right); // Free the memory for the node.
            par->right = NULL;
        }
        return root; // Return the root of the new tree.
    }
    // Take care of the case where the node to be deleted only has a left child
    if (hasOnlyLeftChild_name(delnode)) 
    {
        // Deleting the root node of the tree.
        if (par == NULL) 
        {
            save_node = delnode->left;
            free(delnode); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (strcmp(value, par->treeName) < 0) 
        {
            save_node = par->left; // Save the node to delete.
            par->left = par->left->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

        // Deletes the node if it's a right child.
        else 
        {
            save_node = par->right; // Save the node to delete.
            par->right = par->right->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }
        return root; // Return the root of the tree after the deletion.
    }

    // Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild_name(delnode)) 
    {
        // Node to delete is the root node.
        if (par == NULL) 
        {
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }

        // Delete's the node if it is a left child.
        if (strcmp(value, par->treeName) < 0) 
        {
            save_node = par->left;
            par->left = par->left->right;
            free(save_node);
        }

        // Delete's the node if it is a right child.
        else 
        {
            save_node = par->right;
            par->right = par->right->right;
            free(save_node);
        }
        return root;
    }

    //if your code reaches hear it means delnode has two children
    // Find the new physical node to delete.
    new_del_node = minVal_name(delnode->right);
    strcpy(save_val, new_del_node->treeName);
    delete_name(root, save_val);  // Now, delete the proper value.

    // Restore the data to the original node to be deleted.
    strcpy(delnode->treeName, save_val);
    return root;
}

void Reduce(treeNameNode* my_root, char* name, int val)
{
    //search item first
    itemNode *temp_node = Search_Item_Node(my_root->theTree, name);

    //checking if the final result would become less than 1
    if(temp_node->count-val > 0)
        temp_node->count = temp_node->count - val;

    else
        my_root->theTree = delete(my_root->theTree, name);

    fprintf(outFile, "\n%s reduced", name);
}

// Returns the parent of the node pointed to by node in the tree rooted at root
treeNameNode* parent_name(treeNameNode *root, treeNameNode *node) 
{
    // Take care of NULL cases.
    if (root == NULL || root == node)
        return NULL;

    // The root is the direct parent of node.
    if (root->left == node || root->right == node)
        return root;

    // Look for node's parent in the left side of the tree.
    if (strcmp(node->treeName, root->treeName) < 0)
        return parent_name(root->left, node);

    // Look for node's parent in the right side of the tree.
    else if (strcmp(node->treeName, root->treeName) > 0)
        return parent_name(root->right, node);

    return NULL; // Catch any other extraneous cases.
}

// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf_name(treeNameNode *node) 
{
  return (node->left == NULL && node->right == NULL);
}

// Returns 1 if node has a left child and no right child.
int hasOnlyLeftChild_name(treeNameNode *node) 
{
  return (node->left!= NULL && node->right == NULL);
}

// Returns 1 if node has a right child and no left child.
int hasOnlyRightChild_name(treeNameNode *node) 
{
    return (node->left== NULL && node->right != NULL);
}

// Returns a pointer to the node storing the minimum value in the tree
// with the root, root. Will not work if called with an empty tree.
treeNameNode* minVal_name(treeNameNode *root) 
{
    // Root stores the minimal value.
    if (root->left == NULL)
        return root;

    // The left subtree of the root stores the minimal value.
    else
        return minVal_name(root->left);
}


// Will delete the node storing value in the tree rooted at root.
// The function returns a pointer to the root of the resulting tree.
itemNode* delete(itemNode* root, char* value) 
{
    itemNode *delnode, *new_del_node, *save_node;
    itemNode *par;

    char save_val[MAXLEN];
    int num_val;

    delnode = Search_Item_Node(root, value); // Get a pointer to the node to delete.
    par = parent(root, delnode); // Get the parent of this node.

    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) // case 1
    {
        // Deleting the only node in the tree.
        if (par == NULL) 
        {
            free(root); // free the memory for the node.
            return NULL;
        }

        // Deletes the node if it's a left child.
        if (strcmp(value, par->name) < 0)
        {
            free(par->left); // Free the memory for the node.
            par->left = NULL;
        }

        // Deletes the node if it's a right child.
        else 
        {
            free(par->right); // Free the memory for the node.
            par->right = NULL;
        }
        return root; // Return the root of the new tree.
    }
    // Take care of the case where the node to be deleted only has a left child
    if (hasOnlyLeftChild(delnode)) 
    {
        // Deleting the root node of the tree.
        if (par == NULL) 
        {
            save_node = delnode->left;
            free(delnode); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (strcmp(value, par->name) < 0) 
        {
            save_node = par->left; // Save the node to delete.
            par->left = par->left->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

        // Deletes the node if it's a right child.
        else 
        {
            save_node = par->right; // Save the node to delete.
            par->right = par->right->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }
        return root; // Return the root of the tree after the deletion.
    }

    // Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild(delnode)) 
    {
        // Node to delete is the root node.
        if (par == NULL) 
        {
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }

        // Delete's the node if it is a left child.
        if (strcmp(value, par->name) < 0) 
        {
            save_node = par->left;
            par->left = par->left->right;
            free(save_node);
        }

        // Delete's the node if it is a right child.
        else 
        {
            save_node = par->right;
            par->right = par->right->right;
            free(save_node);
        }
        return root;
    }

    //if your code reaches hear it means delnode has two children
    // Find the new physical node to delete.
    new_del_node = minVal(delnode->right);
    strcpy(save_val, new_del_node->name);
    num_val = new_del_node->count;

    delete(root, save_val);  // Now, delete the proper value.

    // Restore the data to the original node to be deleted.
    strcpy(delnode->name, save_val);
    delnode->count = num_val;
    return root;
}

// Returns the parent of the node pointed to by node in the tree rooted at root
itemNode* parent(itemNode *root, itemNode *node) 
{
    // Take care of NULL cases.
    if (root == NULL || root == node)
        return NULL;

    // The root is the direct parent of node.
    if (root->left == node || root->right == node)
        return root;

    // Look for node's parent in the left side of the tree.
    if (strcmp(node->name, root->name) < 0)
        return parent(root->left, node);

    // Look for node's parent in the right side of the tree.
    else if (strcmp(node->name, root->name) > 0)
        return parent(root->right, node);

    return NULL; // Catch any other extraneous cases.
}

// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(itemNode *node) 
{
  return (node->left == NULL && node->right == NULL);
}

// Returns 1 if node has a left child and no right child.
int hasOnlyLeftChild(itemNode *node) 
{
  return (node->left!= NULL && node->right == NULL);
}

// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(itemNode *node) 
{
    return (node->left== NULL && node->right != NULL);
}

// Returns a pointer to the node storing the minimum value in the tree
// with the root, root. Will not work if called with an empty tree.
itemNode* minVal(itemNode *root) 
{
    // Root stores the minimal value.
    if (root->left == NULL)
        return root;

    // The left subtree of the root stores the minimal value.
    else
        return minVal(root->left);
}

int Find_NumberOfPreviousItems(itemNode *root, char* name) 
{
    if(root == NULL || strcmp(root->name, name)==0) 
        return 0;
    else
        return 1 + Find_NumberOfPreviousItems(root->left, name) + Find_NumberOfPreviousItems(root->right, name);
}

void Item_Before(treeNameNode* temp_node, char* name)
{   
    fprintf(outFile, "\nitem before %s: %d", name, Find_NumberOfPreviousItems(temp_node->theTree, name)/2 + 1);
}

int Find_Count(itemNode *root) 
{
    if(root == NULL) 
        return 0;
    else
        return root->count + Find_Count(root->left) + Find_Count(root->right);
}

void Count_Tree(treeNameNode* temp_node, char* name)
{
    fprintf(outFile, "\n%s count %d",name, Find_Count(temp_node->theTree));
}

int numnodes(itemNode* root) 
{
    if(root == NULL) 
        return 0;
    else
        return 1 + numnodes(root->left) + numnodes(root->right);
}

void get_balance(treeNameNode *root)
{
    int total_left = numnodes(root->theTree->left)/2;
    int total_right = numnodes(root->theTree->right)/2;

    if(total_left == 0)
    {
        total_left = -1;
        total_right = total_right * 2;
    }
    if(total_right == 0)
    {
        total_right = -1;
        total_left = total_left * 2;
    }

    fprintf(outFile, "\n%s: left height %d, right height %d", root->treeName, total_left, total_right);

    fprintf(outFile, ", difference %d", abs(total_left - total_right));

    if(abs(total_left - total_right) == 0)
        fprintf(outFile, ", balanced");
    else
        fprintf(outFile, ", not balanced");
}

void searchItem(treeNameNode *my_root, char* name, char* treeName)
{   
    if(my_root != NULL)
    { 
        //search item
        itemNode *temp_node = Search_Item_Node(my_root->theTree, name);

        if(temp_node != NULL)
            fprintf(outFile, "\n%d %s found in %s", temp_node->count, temp_node->name, my_root->treeName);
        else
            fprintf(outFile, "\n%s not found in %s", name, my_root->treeName);
    }
    else
        fprintf(outFile, "\n%s does not exist", treeName);
}

itemNode* Search_Item_Node(itemNode *root, char* treeNameVal)
{
    if (root != NULL) 
    {
        if (strcmp(root->name, treeNameVal) == 0)
            return root;

        if (strcmp(treeNameVal, root->name) < 0)
            return Search_Item_Node(root->left, treeNameVal);
        else
            return Search_Item_Node(root->right, treeNameVal);
    }
    else
        return NULL;
}

treeNameNode* buildNameTree(treeNameNode *my_root, char* TreeName, char* name, int val)
{
    //allocate memory for new Item node
    itemNode* tempItem;
    tempItem = (struct itemNode*)malloc(sizeof(itemNode));
    strcpy(tempItem->name, name);
    tempItem->count = val;
    tempItem->left = NULL;
    tempItem->right = NULL;

    //Finding root_node with Tree Name
    treeNameNode* tempNode = my_root;
    tempNode = SearchNameNode(my_root, TreeName);

    //insert item to temp Node
    tempNode->theTree = Insert_Item(tempNode->theTree, tempItem);

    return my_root;
}

itemNode* Insert_Item( itemNode *root, itemNode *element) 
{
    if (root == NULL)
        return element;
    else 
    {
        if (strcmp(element->name, root->name) > 0) 
        {
            if (root->right != NULL)
                root->right = Insert_Item(root->right, element);
            else
                root->right = element;
        }
        else 
        {
            if (root->left != NULL)
                root->left = Insert_Item(root->left, element);
            else
                root->left = element;
        }
        return root;
    }
}

treeNameNode* SearchNameNode(treeNameNode *root, char* treeNameVal)
{
    // Check if there are nodes in the tree.
    if (root != NULL) 
    {
        // Found the value at the root.
        if (strcmp(root->treeName, treeNameVal) == 0)
            return root;

        // Search to the left.
        if (strcmp(treeNameVal, root->treeName) < 0)
            return SearchNameNode(root->left, treeNameVal);

        // Or...search to the right.
        else
            return SearchNameNode(root->right, treeNameVal);
    }
    else
        return NULL;
}

treeNameNode* createTreeNameNode(char* name) 
{
    // Allocate space for the node, set the fields.
    treeNameNode* temp;
    temp = (struct treeNameNode*)malloc(sizeof(treeNameNode));
    strcpy(temp->treeName, name);
    temp->theTree = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp; // Return a pointer to the created node.
}

treeNameNode* insert( treeNameNode *root, treeNameNode *element) 
{
    // Inserting into an empty tree.
    if (root == NULL)
        return element;
    
    else 
    {
        // element should be inserted to the right.
        if (strcmp(element->treeName, root->treeName) > 0) 
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

//delete all items of a given tree
void deleteItemTree(itemNode *root)
{
    if (root == NULL) return; 
    // Delete subtrees
    deleteItemTree(root->left);
    free(root->left);
    free(root->right);
    deleteItemTree(root->right);
}

void traverse_in_name(treeNameNode *root) 
{
    // Only traverse the node if it's not null.
    if (root != NULL) 
    {   
        traverse_in_name(root->left); // Go Left.
        fprintf(outFile, "%s ", root->treeName); // Print the root.
        traverse_in_name(root->right); // Go Right.
    }
}

void traverse_in_traverse(treeNameNode *root) 
{
    // Only traverse the node if it's not null.
    if (root != NULL) 
    {   
        traverse_in_traverse(root->left); // Go Left.
        fprintf(outFile, "\n===%s===\n", root->treeName); // Print the root.
        traverse_in_items(root->theTree);
        traverse_in_traverse(root->right); // Go Right.
    }
}

void traverse_in_items(itemNode *root) 
{
    if (root != NULL) 
    {   
        traverse_in_items(root->left); // Go Left.
        fprintf(outFile, "%s ", root->name);
        traverse_in_items(root->right); // Go Right.
    }       
}

void freeMemory(treeNameNode *root)
{
    if (root != NULL) 
    {   
        freeMemory(root->left);
        freeMemory_items(root->theTree);
        free(root);
        freeMemory(root->right);
    }
}

void freeMemory_items(itemNode *root)
{
    if (root != NULL) 
    {   
        freeMemory_items(root->left);
        free(root);
        freeMemory_items(root->right);
    }   
}