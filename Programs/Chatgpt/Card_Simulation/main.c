#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

const char *suits[NUM_SUITS] = {"Hearts", "Diamonds", "Spades", "Clubs"};
const char *ranks[NUM_RANKS] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

int main(void)
{
    int i, j, deck[NUM_SUITS][NUM_RANKS] = {0};
    char again;

    do
    {
        srand(time(0)); // Seed the random number generator

        // Initialize all cards to not drawn
        for (i = 0; i < NUM_SUITS; i++)
        {
            for (j = 0; j < NUM_RANKS; j++)
            {
                deck[i][j] = 0;
            }
        }

        // Open the file for writing
        FILE *fp = fopen("cards.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening file!\n");
            return 1;
        }

        // Draw five random cards
        for (i = 0; i < 5; i++)
        {
            int suit, rank;
            do
            {
                suit = rand() % NUM_SUITS;
                rank = rand() % NUM_RANKS;
            } while (deck[suit][rank] == 1); // Keep drawing until we get a card that hasn't been drawn yet

            // Mark the card as drawn and write it to the file
            deck[suit][rank] = 1;
            fprintf(fp, "Card %d: %s of %s\n", i+1, ranks[rank], suits[suit]);
        }

        // Close the file
        fclose(fp);

        printf("\nDraw again (y/n)? ");
        scanf(" %c", &again);
    } while (again == 'y');

    return 0;
}
