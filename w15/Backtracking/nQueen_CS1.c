/* C program to solve N Queen Problem using
backtracking */
#define N 6
#include <stdbool.h>
#include <stdio.h>

/* A utility function to print solution */
void printSolution(int board[N][N])
{
    printf("Printing in matrix format: \n");
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf(" %d ", board[i][j]);
		printf("\n");
	}

	printf("Printing in Queen format: \n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
            if (board[i][j] == 1)
                 printf("Q%d ", i+1);

             // No queen here, so print a blank.
             else
                 printf("_  ");
			//printf(" %d ", board[i][j]);
		printf("\n");
	}
}

/* check to see if it is save to put the queen in x,y position */
int isSafe(int board[N][N], int x, int y)
{
   int XminusY = x - y;
   int XplusY = x + y;
   for(int i=0; i<N; i++)
    for (int j=0; j<N; j++)
        if (i==x || j==y || (i-j) == XminusY || (i+j) == XplusY) //if in same row or same column or left/right diagonal as we learned in the class
        {
               if(board[i][j] == 1)
                  return 0;
        }
	return 1;
}

/* A recursive utility function to solve N
Queen problem */
int solveNQUtil(int n, int row, int board[N][N])
{
	/* base case: If all queens are placed
	then return true */
	if (row == n)
		return 1;

	/* Consider this column and try placing
	this queen in all rows one by one */

	int col;
	for (col = 0; col < n; col++) {
            if (isSafe(board, row, col))
            {
                board[row][col] = 1;
                if (solveNQUtil(n, row+1, board)) //try for the next row
                    return 1;
                board[row][col] = 0; //if not successful unmark that place to 0
            }
	}

	/* If the queen cannot be placed in any row in
		this column col then return false */
	return 0;
}

/* This function solves the N Queen problem using
Backtracking. It mainly uses solveNQUtil() to
solve the problem. It returns false if queens
cannot be placed, otherwise, return true and
prints placement of queens in the form of 1s.
Please note that there may be more than one
solutions, this function prints one of the
feasible solutions.*/
int solveNQ()
{
    int i, j;
	int board[N][N];
	//initialize all the positions to 0
	for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            board[i][j] = 0;

	if (solveNQUtil(N, 0, board) == 0) {
		printf("Solution does not exist");
		return 0;
	}

	printSolution(board);
	return 1;
}

// driver program to test above function
int main()
{
	solveNQ();
	return 0;
}
