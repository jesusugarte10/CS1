/*COP 2502C Programming Assignment 5
This Program is written by: Jesus Ugarte
University of Central Florida
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define MAXLETTERS 2000001

//Defining trie Structure
typedef struct trie {
    int freq;
    int atBelowFreq;
    int childMaxFreq;
    struct trie* next[26];
} trie;

//Defining Functions
void addToDictionary(trie *root, FILE *inFile);
void prefixQuery(trie *root, FILE* inFile, FILE *outFile);
trie* makeNewNode();
char* queryProcess(trie* root, char* word, int k, int wordLenght);
void insertWordInTrie(trie* root, char* word, int k, int wordLenght, int frequency);
void freeTrieMemory(trie* root);

//Main Function
int main(void)
{
    //atexit reportmemory leak
    atexit(report_mem_leak);

    //Opening Files
    FILE *inFile = fopen("in.txt","r");
    FILE *outFile = fopen("out.txt", "w");

    // Make this from the start. Root node for our trie.
    trie* root = makeNewNode();

    //Reading total number of queries to be done
    int n, query;
    fscanf(inFile, "%d", &n);

    //Iterating thorugh n number of queries read from file
    for(int i = 0; i < n; i++)
    {
        //Making sure which instruction to perform
        fscanf(inFile, "%d", &query);

        if (query == 1)
            addToDictionary(root, inFile);
        else
            prefixQuery(root, inFile, outFile);
    }

    //Free Memory
    freeTrieMemory(root);

    //closing files
    fclose(inFile);
    fclose(outFile);
    return 0;
}

//Function in charge of reading and inserting word into the dictionary
void addToDictionary(trie *root, FILE *inFile)
{
    char word[MAXLETTERS];
    int freq;
    fscanf(inFile, "%s", word);
    fscanf(inFile, "%d", &freq);

    //Start Process of Inserting word into the dictionary
    insertWordInTrie(root, word, 0, strlen(word), freq);
}

// Inserts howMany copies of word starting at index k into the trie pointed to by root.
void insertWordInTrie(trie* root, char* word, int k, int wordLenght, int frequency) 
{
    // increment frquency at and below the node progresively.
    root->atBelowFreq += frequency;

    // Here is our base case. We got to the end, so add 1 to our node and stop.
    if (k == wordLenght) {
        root->freq += frequency;
        return;
    }

    // Code reaches here if new node is neccesary
    if (root->next[word[k]-'a'] == NULL) 
        root->next[word[k]-'a'] = makeNewNode();
    
    // Calculate the size of new node
    int newChildThisPath = root->next[word[k]-'a']->atBelowFreq + frequency;

    // If this changes my max subtree size, update.
    if (newChildThisPath > root->childMaxFreq)
        root->childMaxFreq = newChildThisPath;

    // Insert recursively
    insertWordInTrie(root->next[word[k]-'a'], word, k+1, wordLenght, frequency);
}

//Funciton in charge of reading values of word and frequency and calling the queryProcess Function
void prefixQuery(trie *root, FILE *inFile, FILE *outFile)
{
    //Reading values for word and frequency
    char word[MAXLETTERS];
    int freq;
    fscanf(inFile, "%s", word);

    //Begin Process for Prefix Query after reading Values
    char *answer = queryProcess(root, word, 0, strlen(word));

    //Printing final results after traversing trie
    if (answer == NULL)
        fprintf(outFile, "unknown word\n");
    else 
        fprintf(outFile , "%s\n", answer);

    //Free "answer" string since memory is allocated in queryProcess Function
    free(answer);
}


// Recursively inserts word, starting at index k into the trie pointed to by root. The length
// of the word is wLen. We pass this in to avoid calling strlen multiple times.
char* queryProcess(trie* root, char* word, int k, int wordLenght) 
{
    // Here we count how many future nodes are maximums.
    int numMax = 0, idx = 0;

    // If it reaches here it means we have found the end
    if (k == wordLenght) 
    {
        // Allocate space now.
        char* res = malloc( (numMax+1)*sizeof(char) );
        res[numMax] = '\0';

        // No kids below.
        if (root->childMaxFreq == 0) 
            return NULL;

        for (int i=0; i<26; i++) 
        {
            if (root->next[i] == NULL) 
                continue;
            if (root->next[i]->atBelowFreq == root->childMaxFreq)
                numMax++;
        }
        // Go through letters again.
        for (int i=0; i<26; i++) {

            if (root->next[i] == NULL) 
                continue;
            // Is this a max next letter? If so, add it to the string.
            if (root->next[i]->atBelowFreq == root->childMaxFreq)
                res[idx++] = (char)('a'+i);
        }
        return res;
    }
    // Check for null pointer error and return accordingly.
    if (root->next[word[k]-'a'] == NULL) 
        return NULL;

    // If we get here, we just recurse.
    return queryProcess(root->next[word[k]-'a'], word, k+1, wordLenght);
}

// Returns a pointer to a newly allocated empty trienode.
trie* makeNewNode() 
{
    // Create a new node, set everything to 0, null.
    trie* tmp = malloc(sizeof(trie));
    tmp->atBelowFreq = 0;
    tmp->childMaxFreq = 0;
    tmp->freq =0;

    for (int i=0; i<26; i++)
        tmp->next[i] = NULL;

    // This is a pointer to our new node.
    return tmp;
}

// Frees all the memory pointed to by root, directly and indirectly.
void freeTrieMemory(trie* root) 
{
    // Go to all children.
    for (int i=0; i<26; i++) {

        // Free this subtree, if it exists.
        if (root->next[i] != NULL)
            freeTrieMemory(root->next[i]);
    }

    // Now free our node.
    free(root);
}