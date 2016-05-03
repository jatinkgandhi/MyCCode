/* Pass count game challenge (from code gladiator) solution */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int passCount(int input1,int input2,int input3)
{
	unsigned char gameOver;
	int  *PlayersPassCounts;
	/* Signed integer to track who is having the ball */
	int current;
	int index;
	int totalpasscount;
	/*  NumPlayers -> N, MaxPassAllowed -> M, Skip -> L */
	int NumPlayers,MaxPassAllowed,Skip;
	
	if( 0 == input1 || 0 == input2  || 0 == input3)
	{
		fprintf(stderr,"Invalid parameters\n");
		return 0;
	}

	/* Assigning inputs to meaningful names., not necessary though */
	NumPlayers     =  input1;
	MaxPassAllowed =  input2;
	Skip           =  input3;

	PlayersPassCounts = NULL;
	PlayersPassCounts = (int *)malloc(sizeof(int *) *NumPlayers);
	
	if(NULL == PlayersPassCounts)
	{
		fprintf(stderr,"Failed to create counters for each player\n");
		return 0;
	}
	
	memset(PlayersPassCounts,0,sizeof(int *) *NumPlayers);

	gameOver = 0;
	/* Start with first player */
	current  = 0;
	/* Iterate until game is over */
	/* Start with first player having ball as first pass */
	PlayersPassCounts[current] = 1;
	
	while (0 == gameOver)
	{
		if(PlayersPassCounts[current] % 2 !=  0)
		{
			/* Player 'current' has received odd number of times */
			/* Skip backwards 'Skip' times */
			current -= Skip;
		}else
		{
			/* Player 'current' has received even number of times */
			/* Skip forwards 'Skip' times */
			current += Skip;
		}
		
		/* Rollover handling */
		if(current < 0 )
		{
			/* Rolled past first player., lets roll forward */
			current += NumPlayers;
		}else if(current >  NumPlayers)
		{
			/* Skipped forward beyond players, so roll over to beginning */
			current -= NumPlayers;
		}
		
		PlayersPassCounts[current]++;

		/* Check if game is over */
		if(PlayersPassCounts[current] == MaxPassAllowed)
		{
			/* I (current) have received ball M times ..., */
			gameOver = 1;
		}
		
	}

	totalpasscount  = 0;
	/* Check if game was terminated after reaching the count */
	if(1 == gameOver)
	{

		for(index = 0; index < NumPlayers; index++)
		{
			totalpasscount +=  PlayersPassCounts[index];
		}
		/* Reduce one extra count we added at the beginning when ball was given first to the first player..,*/
		if(totalpasscount > 0) totalpasscount--;
	}

	/* Free the memory for counts */
	if(NULL != PlayersPassCounts)
	{
		free(PlayersPassCounts);
	}
	
	return totalpasscount;
}



