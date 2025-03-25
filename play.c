#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// This program takes into acount all the possible ways a monopoly player can move through the board.
// Rolling dices, using cards or going to jail.
// It will display the amount of times its visited each space in the board.
// Using this numbers on a graph, will help us interpret them much better.

#define ROUNDS 100000000

int roll()
{
	int dice1;
	int dice2;
	int	trip_doub;

	
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	trip_doub = rand() % 216;
	if (trip_doub == 33)
		return (0);
	return (dice1 + dice2);
}

void print_board(int *scores)
{
	int i = -1;
	long int moves = 0;

	while (++i < 40)
	{
		printf("([%d]%d)\n", i, scores[i]);
		moves += scores[i];
	}
	printf("total: %ld\n", moves);
}

void print_cells(int *scores)
{
	printf("%d\n", scores[1]);
	printf("%d\n", scores[3]);
	printf("%d\n", scores[5]);
	printf("%d\n", scores[6]);
	printf("%d\n", scores[8]);
	printf("%d\n", scores[9]);
	printf("%d\n", scores[11]);
	printf("%d\n", scores[12]);
	printf("%d\n", scores[13]);
	printf("%d\n", scores[14]);
	printf("%d\n", scores[15]);
	printf("%d\n", scores[16]);
	printf("%d\n", scores[18]);
	printf("%d\n", scores[19]);
	printf("%d\n", scores[21]);
	printf("%d\n", scores[23]);
	printf("%d\n", scores[24]);
	printf("%d\n", scores[25]);
	printf("%d\n", scores[26]);
	printf("%d\n", scores[27]);
	printf("%d\n", scores[28]);
	printf("%d\n", scores[29]);
	printf("%d\n", scores[31]);
	printf("%d\n", scores[32]);
	printf("%d\n", scores[34]);
	printf("%d\n", scores[35]);
	printf("%d\n", scores[37]);
	printf("%d\n", scores[39]);
}

void	ft_bzero(int *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
		s[i++] = 0;
}

int community_chest(int *GO, int *JAIL)
{
	int card;

	card = rand() % 16 + 1;
	if (card == 1)
	{
		(*GO)++;
		return (0);
	}
	if (card == 2)
	{
		(*JAIL)++;
		return (10);
	}
	return (-1);
}

int chance(int p1, int *scores, int *GO, int *JAIL)
{
	int card;

	card = rand() % 16 + 1;
	if (card == 1)
	{
		(*GO)++;
		return (0);
	}
	if (card == 2)
	{
		(*JAIL)++;
		return (10);
	}
	if (card == 3)
		return (5);
	if (card == 4)
		return (39);
	if (card == 5)
		return (p1 - 3);
	if (card == 6)
		return (24);
	if (card == 7)
		return (11);
	if (card == 8 || card == 9)
	{
		while (!(p1 % 10 != 0 && p1 % 5 == 0))
		{
			p1++;
			if (p1 == 40)
				p1 = 0;
		}
		scores[p1]++;
		return (p1);
	}
	return (-1);
}

int main(int argc, char **argv)
{
	int scores[40];
	int p1 = 0;
	int	moves;
	int trip = 0;
	int sent_GO = 0;
	int sent_JAIL = 0;
	int i = 0;
	time_t t;

	ft_bzero(scores, 40);
	srand((unsigned) time(&t));
	if (argc == 1)
		printf("cards: enabled\n");
	else
		printf("cards: disabled\n");
	while (i++ < ROUNDS)
	{
		moves = roll();
		if (!moves)
		{
			sent_JAIL++;
			p1 = 10;
			trip++;
		}
		else
			p1 += moves;
		if (p1 > 39)
			p1 -= 40;
		scores[p1]++;
		if (argc == 1)
		{
			if (p1 == 2 || p1 == 17 || p1 == 33)
			{
				moves = community_chest(&sent_GO, &sent_JAIL);
				if (moves != -1)
				{
					p1 = moves;
					scores[p1]++;
				}
			}
			if (p1 == 7 || p1 == 22 || p1 == 36)
			{
				moves = chance(p1, scores, &sent_GO, &sent_JAIL);
				if (moves != -1)
				{
					p1 = moves;
					scores[p1]++;
				}
			}
		}
		if (p1 == 30)
		{
			p1 = 10;
			scores[p1]++;
		}
	}
	//print_board(scores);
	print_cells(scores);
}
