#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "secretSanta.h"

/*
 	Open a file containing the names of participants, assign each player a number and randomly
	assign each player to another one.
*/
int generateRandom(int max)
{
	return rand() % max;
}	

int main(void)
{
	FILE* inputfile = fopen("input.txt", "r");
	FILE* outputfile = fopen("output.txt", "w");
	char c;
	int playerCount = 0;
	int randomNum;
	int i;
	Player* playerList = NULL;
	int* availablePlayers = NULL;

	if(inputfile == NULL)
	{
		perror("Input file error: "); 
	}
	else 
	{
		/* Seed the random number generator */
		srand(time(NULL));
		
		/* Get number of player (assuming each player name is on a separate line) */
		do {
			c = fgetc(inputfile);

			if(c == '\n')
			{
				++playerCount;
			}
		}
		while(c != EOF);
		
		/* Reset file pointer to beginning of file */
		rewind(inputfile);

		printf("Player count: %d\n", playerCount);
		
		/* Allocate memory to store players */
		playerList = malloc(playerCount * sizeof(Player));
		
		/* Allocate memory to store the list of players that are available for assignment */
		availablePlayers = malloc(playerCount * sizeof(int));
		
		/* Assign each entry in availablePlayers to 1 (true) */
		for (i = 0; i < playerCount; ++i)
			availablePlayers[i] = 1;

		/* Parse file contents, copy player names and number into player buffer */
		for (i = 0; i < playerCount; ++i)
		{
			fscanf(inputfile, "%s", playerList[i].name);
			playerList[i].num = i;
		}

		/* Assign a players randomly in pairs */
		for (i = 0; i < playerCount; ++i)
		{
			/* Generate random pairs */
			do {
				randomNum = generateRandom(playerCount);
			}
		       	while (availablePlayers[randomNum] == 0 || randomNum == i);

			availablePlayers[randomNum] = 0;

			printf("%s is assigned to: %s\n", playerList[i].name, playerList[randomNum].name);

			fprintf(outputfile, "%s is assigned to: %s\n", playerList[i].name, playerList[randomNum].name);
		}

		/* Close input & output .txt files and free struct array */
		fclose(inputfile);
		fclose(outputfile);
		free(playerList);
		free(availablePlayers);
	}
	

	return 0;
}


