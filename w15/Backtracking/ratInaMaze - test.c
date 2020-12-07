/* C program to solve Rat in a Maze problem using
backtracking */
#include <stdio.h>

// Maze size
#define N 4

int solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);

/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf(" %d ", sol[i][j]);
		printf("\n");
	}
}

/* A utility function to check if x, y is valid index for N*N maze */
int isSafe(int maze[N][N], int x, int y)
{
	// if (x, y outside maze) return false
	if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
		return 1;

	return 0;
}

/* This function solves the Maze problem using Backtracking. It mainly
uses solveMazeUtil() to solve the problem. It returns false if no
path is possible, otherwise return true and prints the path in the
form of 1s. Please note that there may be more than one solutions,
this function prints one of the feasible solutions.*/
int solveMaze(int maze[N][N])
{
	int sol[N][N] = { { 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 } };

	if (solveMazeUtil(maze, 0, 0, sol) == 0) {
		printf("Solution doesn't exist");
		return 0;
	}

	printSolution(sol);
	return 1;
}

/* A recursive utility function to solve Maze problem */
int solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
	// if (x, y is goal) return true
	if (x == N - 1 && y == N - 1) {
		sol[x][y] = 1;
		return 1;
	}

	// Check if maze[x][y] is valid
	if (isSafe(maze, x, y) == 1) {
		// mark x, y as part of solution path
		sol[x][y] = 1;

       // printf("before x s(%d, %d) mat = %d\n", x+1, y, sol[x][y]);
		/* Move forward in x direction (go down / next row) */
		if (solveMazeUtil(maze, x + 1, y, sol) == 1)
			return 1;
      //  printf("before y s(%d, %d) mat = %d\n", x, y+1, sol[x][y]);
		/* If moving in x direction doesn't give solution then
		Move down in y direction */
		if (solveMazeUtil(maze, x, y + 1, sol) == 1)
			return 1;


		/* If none of the above movements work then BACKTRACK:
			unmark x, y as part of solution path */
		sol[x][y] = 0;
		//printf("after x,y s(%d, %d) mat = %d\n", x, y, sol[x][y]);
		return 0;
	}

	return 0;
}

// driver program to test above function
int main()
{
	int maze[N][N] = { { 1, 0, 0, 1 },
					   { 1, 1, 0, 0 },
					   { 0, 1, 1, 1 },
					   { 1, 1, 0, 1 }
                    };

	solveMaze(maze);
	return 0;
}
