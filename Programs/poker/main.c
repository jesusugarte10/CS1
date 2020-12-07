/*
Created By Isabella Pardo
University Of Central Florida
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SUITS 4
#define NUM_CARDS 5
#define NUM_RANKS 13

//Defining Functions to Be Used
void Process_Cards(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int*suitsInHand_Two);
void buildHand(int *facesInHand_One, int *suitsInHand_One);
void createDecks(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int *suitsInHand_Two);
void printResults(int a, int b, int* facesInHand_One, int *facesInHand_Two);
int analyzeHand(int *facesInHand, int *suitsInHand, bool straight, bool flush, bool four, bool three, int pairs);
int calcResults(bool straight, bool flush, bool four, bool three, int pairs);
void printCards(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int *suitsInHand_Two);
void breakTie(int *facesInHand_One, int *facesInHand_Two);

int main(void)
{
    //Declaring Two Arrays
    int suitsInHand_One[SUITS] = {0};
	int suitsInHand_Two[SUITS] = {0};
    int facesInHand_One[NUM_RANKS] = {0};
    int facesInHand_Two[NUM_RANKS] = {0};

	//Creating Decks
	createDecks(facesInHand_One, suitsInHand_One, facesInHand_Two, suitsInHand_Two);

	//Printing Cards
 	printCards(facesInHand_One, suitsInHand_One, facesInHand_Two, suitsInHand_Two);

	//Process the Information
	Process_Cards(facesInHand_One, suitsInHand_One, facesInHand_Two, suitsInHand_Two);

    //End Of Program
    return 0;
}

//Main Interface to Process the two Hands
void Process_Cards(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int *suitsInHand_Two){

	//Declaring variables to be used
    bool straight, flush, four, three;
    int pairs;

	printf("\nProcessing Cards");
	printf("\n-----------------\n");
    //analyzing Hand 1
    int first_hand_weight = analyzeHand(facesInHand_One, suitsInHand_One, straight, flush, four, three, pairs);

	//analyzing Hand 2
	int second_hand_weight = analyzeHand(facesInHand_Two, suitsInHand_Two, straight, flush, four, three, pairs);

	printf("\nFinal Desicion");
	printf("\n---------------");	
	//Printing Results
	printResults(first_hand_weight, second_hand_weight, facesInHand_One, facesInHand_Two);
}


/*
analyzeHand: Determines whether the hand contains a  straight, a flush, four-of-a-kind,      
and/or a three-of-a-kind; determines the number of pairs; stores the results into 
the external variables straight, flush,  four, three, and pairs.                  
*/
int analyzeHand(int *facesInHand, int *suitsInHand, bool straight, bool flush, bool four, bool three, int pairs) 
{

	int num_consec = 0;
	int rank, suit;

	straight = false;
	flush = false;
	four = false;
	three = false;
	pairs = 0;

	// check for flush – 5 cards of the same suit
	for (suit = 0; suit < SUITS; suit++)
		if (suitsInHand[suit] == 5)
			flush = true;

	// check for straight – eg. One each of 5,6,7,8,9
	//    locate the first card
	rank = 0;
	while (facesInHand[rank] == 0) 
		rank++;

	// count the consecutive non-zero faces
	for (; rank < NUM_RANKS && facesInHand[rank]; rank++)
		num_consec++;

	if (num_consec == 5) {
		straight = true;
		return calcResults(straight, flush, four, three, pairs);
	}

	/* check for 4-of-a-kind, 3-of-a-kind, and pairs */
	for (rank = 0; rank < NUM_RANKS; rank++) {
		if (facesInHand[rank] == 4) 
			four = true;
		if (facesInHand[rank] == 3) 
			three = true;
		if (facesInHand[rank] == 2) 
			pairs++;
	}
	return calcResults(straight, flush, four, three, pairs);
}

//Process to Build Hand of Poker
void buildHand(int *facesInHand, int *suitsInHand){

	int numCards = NUM_CARDS;
	int Value;

	//assigning Values
	while(numCards > 0)
	{
		Value = ((rand()%SUITS));
		suitsInHand[Value]++;

		Value = (rand()%NUM_RANKS);
		facesInHand[Value]++;

		numCards--;
	}
}

//Function to Create Both Decks of Card
void createDecks(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int *suitsInHand_Two){

	time_t t;
   	/* Intializes random number generator */
   	srand(time(NULL));

	//Building First Decks of card
	buildHand(facesInHand_One, suitsInHand_One);

	//Building First Decks of card
	buildHand(facesInHand_Two, suitsInHand_Two);
}

//printing final results
void printResults(int a, int b, int* facesInHand_One, int *facesInHand_Two){

	if(a > b)
		printf("\nFIRST HAND IS THE WINNER\n");

	else if(a < b)
		printf("\nSECOND HAND IS THE WINNER\n");
	else
	{
		printf("\nIT IS A TIE\n");
		printf("\n>>>>BREAKING A TIE\n");

		//break tie
		breakTie(facesInHand_One, facesInHand_Two);
	}
}

//Breaking a tie
void breakTie(int *facesInHand_One, int *facesInHand_Two){

	int highest1 = 0, highest2 = 0;
	int index1, index2;

	//Checking for highest
	for (int i = 0; i < NUM_RANKS; i++)
        if (facesInHand_One[i] >= highest1){
        	highest1 = facesInHand_One[i];
			index1 = i;
		}

	for (int i = 0; i < NUM_RANKS; i++)
        if (facesInHand_Two[i] >= highest2){
			highest2 = facesInHand_Two[i];
			index2 = i;
		}
	
	if(index1 > index2)
		printf("\nFIRST HAND IS THE WINNER\n");
	else if(index1 < index2)
		printf("\nSECOND HAND IS THE WINNER\n");
	else if(facesInHand_One[0] != -1 && facesInHand_Two[0] != -1)
	{
		printf(">>CHECKING FOR NEXT HIGHEST RANK\n");
		//Cards have similar ranking, 
		//Look for second highest for each
		facesInHand_One[index1] = -1;
		facesInHand_Two[index2] = -1;
		//Recursively call the break tie function looking for following highest
		breakTie(facesInHand_One, facesInHand_Two);
	}
	else
	{
		//Handle super weird case where all card have same rank and plot has to be split
		printf("ALL 5 CARDS HAVE SAME RANK, PLOT IS SPLIT\n");
	}
}

//calculatiing results and returning weight hand
int calcResults(bool straight, bool flush, bool four, bool three, int pairs)
{
	if (straight && flush){
		printf("Straight flush\n");
		return 8;
	}
	else if (four){
		printf("Four of a kind\n");
		return 7;
	}
	else if (three && pairs == 1){
		printf("Full house\n");
		return 6;
	}
	else if (flush){
		printf("Flush\n");
		return 5;
	}    
	else if (straight){	
		printf("Straight\n");
		return 4;
	}
	else if (three){
		printf("Three of a kind\n");
		return 3;
	}
		
	else if (pairs == 2){
		printf("Two pairs\n");
		return 2;
	}
	else if (pairs == 1){
		printf("Pair\n");
		return 1;
	}
	else                   
		printf("High card\n");
		return 0;
}

//Printing Cards Generated
void printCards(int *facesInHand_One, int *suitsInHand_One, int *facesInHand_Two, int *suitsInHand_Two){

	//First hand
	printf("\nFirst Hand");
	printf("\n-----------\n");
	for(int i = 0; i < SUITS;i++)
		printf("%d", suitsInHand_One[i]);
	printf("\n");
	for(int i = 0; i < NUM_RANKS;i++)
		printf("%d", facesInHand_One[i]);

	//Second Hand
	printf("\n\nSecond Hand");
	printf("\n-----------\n");
	for(int i = 0; i < SUITS;i++)
		printf("%d", suitsInHand_Two[i]);
	printf("\n");
	for(int i = 0; i < NUM_RANKS;i++)
		printf("%d", facesInHand_Two[i]);
	printf("\n");

}