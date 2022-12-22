#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Cardstruct
{
    // int Card1;
    // int Card2;
    // int CardDealer;
    enum Options
    {
        Stand,
        Hit,
        Double
    } Choice;
    enum VALUES
    {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        ACE
    } Card1,
        Card2, CardDealer;
};

int generateCards(struct Cardstruct *Cards);
int calculateDecision(struct Cardstruct *Cards);

int main(void)
{

    // int TrueCount = 0;

    struct Cardstruct Cards;

    generateCards(&Cards);
    printf("%d %d %d \n", Cards.Card1, Cards.Card2, Cards.CardDealer);
    switch (Cards.Card1)
    {
    case (TWO):
        printf("TWO\n");
        break;
    case (THREE):
        printf("THREE\n");
        break;
    case (FOUR):
        printf("FOUR\n");
        break;
    case (FIVE):
        printf("FIVE\n");
        break;
    case (SIX):
        printf("SIX\n");
        break;
    case (SEVEN):
        printf("SEVEN\n");
        break;
    case (EIGHT):
        printf("EIGHT\n");
        break;
    case (NINE):
        printf("NINE\n");
        break;
    case (TEN):
        printf("TEN\n");
        break;
    case (ACE):
        printf("ACE\n");
        break;
    default:
        break;
    }

    calculateDecision(&Cards);

    switch (Cards.Choice)
    {
    case (Stand):
        printf("Stand\n");
        break;

    case (Hit):
        printf("Hit\n");
        break;

    case (Double):
        printf("Double\n");
        break;

    default:
        break;
    }

    return (EXIT_SUCCESS);
}

int generateCards(struct Cardstruct *Cards)
{

    srand((unsigned int)time(NULL));
    Cards->Card1 = (rand() % 10) + 2; // Random number 2-11
    Cards->Card2 = (rand() % 10) + 2;
    Cards->CardDealer = (rand() % 10) + 2;

    return (EXIT_SUCCESS);
}

int calculateDecision(struct Cardstruct *Cards)
{
    int CardSum = 0;

    if ((Cards->Card1 == Cards->Card2)) // Split table
    {
    }
    else
    {
        if ((Cards->Card1 == 11) || (Cards->Card2 == 11)) // Soft total table
        {
            if ((Cards->Card1 == 8) || (Cards->Card2 == 8))
            {
                if (Cards->CardDealer == 6)
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Stand;
                }
            }
            else if ((Cards->Card1 == 7) || (Cards->Card2 == 7))
            {
                if (Cards->CardDealer <= 6)
                {
                    Cards->Choice = Double;
                }
                else if (Cards->CardDealer <= 8)
                {
                    Cards->Choice = Stand;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if ((Cards->Card1 == 6) || (Cards->Card2 == 6))
            {
                if ((Cards->CardDealer >= 3) && (Cards->CardDealer <= 6))
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (((Cards->Card1 == 5) || (Cards->Card1 == 4)) || ((Cards->Card2 == 5) || (Cards->Card2 == 4)))
            {
                if ((Cards->CardDealer >= 4) && (Cards->CardDealer <= 6))
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (((Cards->Card1 == 3) || (Cards->Card1 == 2)) || ((Cards->Card2 == 3) || (Cards->Card2 == 2)))
            {
                if ((Cards->CardDealer >= 5) && (Cards->CardDealer <= 6))
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else // nine or larger
            {
                Cards->Choice = Stand;
            }
        }
        else // Hard total table
        {
            CardSum = (int)Cards->Card1 + (int)Cards->Card2;
            if (CardSum >= 17)
            {
                Cards->Choice = Stand;
            }
            else if (CardSum >= 13)
            {
                if (Cards->CardDealer < 7)
                {
                    Cards->Choice = Stand;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (CardSum >= 12)
            {
                if ((Cards->CardDealer >= 4) || (Cards->CardDealer <= 6))
                {
                    Cards->Choice = Stand;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (CardSum == 11)
            {
                Cards->Choice = Double;
            }
            else if (CardSum == 10)
            {
                if (Cards->CardDealer <= 9)
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (CardSum == 9)
            {
                if ((Cards->CardDealer >= 3) || (Cards->CardDealer <= 6))
                {
                    Cards->Choice = Double;
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if (CardSum <= 8)
            {
                Cards->Choice = Hit;
            }
        }
    }

    return (EXIT_SUCCESS);
}