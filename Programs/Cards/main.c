#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FirstCard 0
#define SecondCard 1
#define DealerCard 2

struct Cardstruct
{
    enum Options
    {
        Stand,
        Hit,
        Double,
        Split,
        Surrender
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
    } Card[DealerCard];
    int TrueCount;
};

int generateCards(struct Cardstruct *Cards);
int calculateDecision(struct Cardstruct *Cards);
int calculateHardTable(struct Cardstruct *Cards);
int calculateSoftTable(struct Cardstruct *Cards);
int calculateSplitTable(struct Cardstruct *Cards);
int printData(struct Cardstruct *Cards);

int main(void)
{

    struct Cardstruct Cards;

    generateCards(&Cards);
    calculateDecision(&Cards);
    printData(&Cards);

    return (EXIT_SUCCESS);
}

int generateCards(struct Cardstruct *Cards)
{

    srand((unsigned int)time(NULL));
    Cards->Card[FirstCard] = (rand() % 10) + 2; // Random number 2-11
    Cards->Card[SecondCard] = (rand() % 10) + 2;
    Cards->Card[DealerCard] = (rand() % 10) + 2;

    return (EXIT_SUCCESS);
}

int calculateDecision(struct Cardstruct *Cards)
{
    if ((Cards->Card[FirstCard] == Cards->Card[SecondCard])) // Split table
    {
        calculateSplitTable(Cards);
    }
    else
    {
        if ((Cards->Card[FirstCard] == 11) || (Cards->Card[SecondCard] == 11)) // Soft total table
        {
            calculateSoftTable(Cards);
        }
        else // Hard total table
        {
            calculateHardTable(Cards);
        }
    }

    return (EXIT_SUCCESS);
}

int calculateHardTable(struct Cardstruct *Cards)
{
    int CardSum = 0;
    CardSum = (int)Cards->Card[FirstCard] + (int)Cards->Card[SecondCard];
    if (CardSum >= 17)
    {
        Cards->Choice = Stand;
    }
    else if (CardSum == 16)
    {
        if (Cards->Card[DealerCard] >= 9)
        {
            Cards->Choice = Surrender;
        }
        else
        {
            if (Cards->Card[DealerCard] <= 6)
            {
                Cards->Choice = Stand;
            }
            else
            {
                Cards->Choice = Hit;
            }
        }
    }
    else if (CardSum == 15)
    {
        if (Cards->Card[DealerCard] == 10)
        {
            Cards->Choice = Surrender;
        }
        else
        {
            if (Cards->Card[DealerCard] <= 6)
            {
                Cards->Choice = Stand;
            }
            else
            {
                Cards->Choice = Hit;
            }
        }
    }
    else if (CardSum >= 13)
    {
        if ((CardSum == 13) && (Cards->Card[DealerCard] == 2) && (Cards->TrueCount <= -1))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if (Cards->Card[DealerCard] <= 6)
            {
                Cards->Choice = Stand;
            }
            else
            {
                Cards->Choice = Hit;
            }
        }
    }
    else if (CardSum == 12)
    {
        if (((Cards->Card[DealerCard] == 2) && (Cards->TrueCount >= 3)) || ((Cards->Card[DealerCard] == 3) && (Cards->TrueCount >= 2)))
        {
            Cards->Choice = Stand;
        }
        else if ((Cards->Card[DealerCard] == 4) && (Cards->TrueCount < 0))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[DealerCard] >= 4) && (Cards->Card[DealerCard] <= 6))
            {
                Cards->Choice = Stand;
            }
            else
            {
                Cards->Choice = Hit;
            }
        }
    }
    else if (CardSum == 11)
    {
        Cards->Choice = Double;
    }
    else if (CardSum == 10)
    {
        if (Cards->Card[DealerCard] <= 9)
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
        if ((Cards->Card[DealerCard] >= 3) && (Cards->Card[DealerCard] <= 6))
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
    return (EXIT_SUCCESS);
}

int calculateSoftTable(struct Cardstruct *Cards)
{
    if ((Cards->Card[FirstCard] == 8) || (Cards->Card[SecondCard] == 8))
    {
        if (Cards->Card[DealerCard] == 6)
        {
            Cards->Choice = Double;
        }
        else
        {
            Cards->Choice = Stand;
        }
    }
    else if ((Cards->Card[FirstCard] == 7) || (Cards->Card[SecondCard] == 7))
    {
        if (Cards->Card[DealerCard] <= 6)
        {
            Cards->Choice = Double;
        }
        else if (Cards->Card[DealerCard] <= 8)
        {
            Cards->Choice = Stand;
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if ((Cards->Card[FirstCard] == 6) || (Cards->Card[SecondCard] == 6))
    {
        if ((Cards->Card[DealerCard] >= 3) && (Cards->Card[DealerCard] <= 6))
        {
            Cards->Choice = Double;
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if (((Cards->Card[FirstCard] == 5) || (Cards->Card[FirstCard] == 4)) || ((Cards->Card[SecondCard] == 5) || (Cards->Card[SecondCard] == 4)))
    {
        if ((Cards->Card[DealerCard] >= 4) && (Cards->Card[DealerCard] <= 6))
        {
            Cards->Choice = Double;
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if (((Cards->Card[FirstCard] == 3) || (Cards->Card[FirstCard] == 2)) || ((Cards->Card[SecondCard] == 3) || (Cards->Card[SecondCard] == 2)))
    {
        if ((Cards->Card[DealerCard] >= 5) && (Cards->Card[DealerCard] <= 6))
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

    return (EXIT_SUCCESS);
}

int calculateSplitTable(struct Cardstruct *Cards)
{
    if (Cards->Card[FirstCard] == 11)
    {
        Cards->Choice = Split;
    }
    else if (Cards->Card[FirstCard] == 10)
    {
        calculateHardTable(Cards);
    }
    else if (Cards->Card[FirstCard] == 9)
    {
        if ((Cards->Card[DealerCard] == 7) || (Cards->Card[DealerCard] == 10) || (Cards->Card[DealerCard] == 11))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[FirstCard] == 8)
    {
        Cards->Choice = Split;
    }
    else if (Cards->Card[FirstCard] == 7)
    {
        if ((Cards->Card[DealerCard] >= 8))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[FirstCard] == 6)
    {
        if ((Cards->Card[DealerCard] >= 7))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[FirstCard] == 5)
    {
        calculateHardTable(Cards);
    }
    else if (Cards->Card[FirstCard] == 4)
    {
        if ((Cards->Card[DealerCard] == 5) || (Cards->Card[DealerCard] == 6))
        {
            Cards->Choice = Split;
        }
        else
        {
            calculateHardTable(Cards);
        }
    }
    else // Pair of 3 or 2
    {
        if ((Cards->Card[DealerCard] >= 8))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }

    return (EXIT_SUCCESS);
}

int printData(struct Cardstruct *Cards)
{
    int i;
    for (i = 0; i <= DealerCard; i++)
    {
        switch (i)
        {
        case (FirstCard):
            printf("FirstCard = ");
            break;
        case (SecondCard):
            printf("SecondCard = ");
            break;
        case (DealerCard):
            printf("DealerCard = ");
            break;
        }
        switch (Cards->Card[i])
        {
        case (TWO):
            printf("TWO (%d)\n", TWO);
            break;
        case (THREE):
            printf("THREE (%d)\n", THREE);
            break;
        case (FOUR):
            printf("FOUR (%d)\n", FOUR);
            break;
        case (FIVE):
            printf("FIVE (%d)\n", FIVE);
            break;
        case (SIX):
            printf("SIX (%d)\n", SIX);
            break;
        case (SEVEN):
            printf("SEVEN (%d)\n", SEVEN);
            break;
        case (EIGHT):
            printf("EIGHT (%d)\n", EIGHT);
            break;
        case (NINE):
            printf("NINE (%d)\n", NINE);
            break;
        case (TEN):
            printf("TEN (%d)\n", TEN);
            break;
        case (ACE):
            printf("ACE (%d)\n", ACE);
            break;
        default:
            break;
        }
    }

    switch (Cards->Choice)
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

    case (Split):
        printf("Split\n");
        break;

    case (Surrender):
        printf("Surrender\n");
        break;

    default:
        break;
    }

    return (EXIT_SUCCESS);
}