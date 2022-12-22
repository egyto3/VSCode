#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateCards(int *Card1, int *Card2, int *CardDealer);

// struct Cards
// {

// }

int main()
{
    int Card1 = 0, Card2 = 0, CardDealer = 0, CardSum = 0;
    const enum Options { Stand,
                         Hit,
                         Double };
    int Choice = 0;
    int TrueCount = 0;

    generateCards(&Card1, &Card2, &CardDealer);
    printf("%d %d %d \n", Card1, Card2, CardDealer);
    if ((Card1 == Card2)) // Split table
    {
    }
    else
    {
        if ((Card1 == 11) || (Card2 == 11)) // Soft total table
        {
            if ((Card1 == 8) || (Card2 == 8))
            {
                if (CardDealer == 6)
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Stand;
                }
            }
            else if ((Card1 == 7) || (Card2 == 7))
            {
                if (CardDealer <= 6)
                {
                    Choice = Double;
                }
                else if (CardDealer <= 8)
                {
                    Choice = Stand;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if ((Card1 == 6) || (Card2 == 6))
            {
                if ((CardDealer >= 3) && (CardDealer <= 6))
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (((Card1 == 5) || (Card1 == 4)) || ((Card2 == 5) || (Card2 == 4)))
            {
                if ((CardDealer >= 4) && (CardDealer <= 6))
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (((Card1 == 3) || (Card1 == 2)) || ((Card2 == 3) || (Card2 == 2)))
            {
                if ((CardDealer >= 5) && (CardDealer <= 6))
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else // nine or larger
            {
                Choice = Stand;
            }
        }
        else // Hard total table
        {
            CardSum = Card1 + Card2;
            if (CardSum >= 17)
            {
                Choice = Stand;
            }
            else if (CardSum >= 13)
            {
                if (CardDealer < 7)
                {
                    Choice = Stand;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (CardSum >= 12)
            {
                if ((CardDealer >= 4) || (CardDealer <= 6))
                {
                    Choice = Stand;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (CardSum == 11)
            {
                Choice = Double;
            }
            else if (CardSum == 10)
            {
                if (CardDealer <= 9)
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (CardSum == 9)
            {
                if ((CardDealer >= 3) || (CardDealer <= 6))
                {
                    Choice = Double;
                }
                else
                {
                    Choice = Hit;
                }
            }
            else if (CardSum <= 8)
            {
                Choice = Hit;
            }
        }
    }
    switch (Choice)
    {
    case (Stand):
        printf("Stand");
        break;

    case (Hit):
        printf("Hit");
        break;

    case (Double):
        printf("Double");
        break;

    default:
        break;
    }

    return (EXIT_SUCCESS);
}

int generateCards(int *Card1, int *Card2, int *CardDealer)
{
    // const enum VALUES { ACE = 1,
    //                     TWO,
    //                     THREE,
    //                     FOUR,
    //                     FIVE,
    //                     SIX,
    //                     SEVEN,
    //                     EIGHT,
    //                     NINE,
    //                     TEN };
    srand((unsigned int)time(NULL));
    *Card1 = (rand() % 10) + 2;
    *Card2 = (rand() % 10) + 2;
    *CardDealer = (rand() % 10) + 2;

    return (EXIT_SUCCESS);
}