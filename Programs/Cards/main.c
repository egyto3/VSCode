#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FirstCard 1
#define SecondCard 2
#define DealerCard 0

#define Deviations 0
#define Surrendering 1
#define Doubling 1
#define DoubleAfterSplit 1
#define DeckNumber 1

struct Cardstruct
{
    int deck[52];
    int CardsDrawn;
    int arrayPostitionSwitchtoDealer;
    int CardSum;
    int DealerCardSum;
    int TrueCount;
    enum Options
    {
        Stand,
        Hit,
        Double,
        Split,
        Surrender
    } Choice,
        UserChoice;
    enum VALUES
    {
        ONE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        ACE
    } Card[52];
};

int generateCards(struct Cardstruct *Cards);
int calculateDecision(struct Cardstruct *Cards);
int calculateHardTable(struct Cardstruct *Cards);
int calculateSoftTable(struct Cardstruct *Cards);
int calculateSplitTable(struct Cardstruct *Cards);
int printData(struct Cardstruct *Cards);
int compareUserChoice(struct Cardstruct *Cards);

int main(void)
{

    struct Cardstruct Cards;
    Cards.TrueCount = 1;
    Cards.CardsDrawn = 0;

    generateCards(&Cards);
    Cards.CardsDrawn = 2;
    compareUserChoice(&Cards);

    return (EXIT_SUCCESS);
}

int generateCards(struct Cardstruct *Cards)
{

    // srand((unsigned int)time(NULL));
    //  Cards->Card[FirstCard] = (rand() % 10) + 2; // Random number 2-11
    //  Cards->Card[SecondCard] = (rand() % 10) + 2;
    //  Cards->Card[DealerCard] = (rand() % 10) + 2;
    //  Cards->Card[FirstCard] = 6;
    //  Cards->Card[SecondCard] = 9;
    //  Cards->Card[DealerCard] = 9;
    srand((unsigned int)time(NULL));
    int temp, Value1, Value2, suit, cardNumber;
    int i;
    for (i = 0; i < 52 * DeckNumber; i++)
    {
        Cards->deck[i] = i;
    }
    // shuffle deck
    for (i = 0; i < 1000; i++)
    {
        Value1 = (rand() % 52);
        Value2 = (rand() % 52);
        // swap cards
        temp = Cards->deck[Value1];
        Cards->deck[Value1] = Cards->deck[Value2];
        Cards->deck[Value2] = temp;
    }
    for (i = 0; i < 52 * DeckNumber; i++)
    {
        suit = Cards->deck[i] % 4;
        cardNumber = (Cards->deck[i] % 13) + 1;
        if (cardNumber >= 10)
        {
            Cards->Card[i] = TEN;
        }
        else if (cardNumber == 1)
        {
            Cards->Card[i] = ACE;
        }
        else
        {
            Cards->Card[i] = cardNumber;
        }
        printf("%d ", Cards->Card[i]);
    }
    printf("\n");
    return (EXIT_SUCCESS);
}

int calculateDecision(struct Cardstruct *Cards)
{
    int i;
    Cards->CardSum = 0;
    for (i = 1; i <= Cards->CardsDrawn; i++)
    {
        Cards->CardSum += (int)Cards->Card[i];
    }
    int j;

    if ((Cards->Card[FirstCard] == Cards->Card[SecondCard])) // Split table
    {
        calculateSplitTable(Cards);
    }
    else
    {
        for (j = 1; j <= Cards->CardsDrawn; j++)
        {
            if (Cards->Card[j] == 11) // Soft total table
            {
                calculateSoftTable(Cards);
                return (EXIT_SUCCESS);
            }
        }
        // Hard total table
        calculateHardTable(Cards);
    }

    return (EXIT_SUCCESS);
}

int calculateHardTable(struct Cardstruct *Cards)
{
    if (Cards->CardSum >= 17)
    {
        Cards->Choice = Stand;
    }
    else if (Cards->CardSum == 16)
    {
        if ((((Cards->Card[DealerCard] == 9) && (Cards->TrueCount >= 4)) || ((Cards->Card[DealerCard] == 10) && (Cards->TrueCount > 0)) || ((Cards->Card[DealerCard] == 11) && (Cards->TrueCount >= 3))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if (((Cards->Card[DealerCard] == 8) && (Cards->TrueCount >= 4)) && (Deviations && Surrendering) && (Cards->CardsDrawn == 2))
        {
            Cards->Choice = Surrender;
        }
        else if ((Cards->Card[DealerCard] == 9) && (Cards->TrueCount <= -1))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[DealerCard] >= 9) && Surrendering && (Cards->CardsDrawn == 2))
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
    }
    else if (Cards->CardSum == 15)
    {
        if ((((Cards->Card[DealerCard] == 10) && (Cards->TrueCount >= 4)) || ((Cards->Card[DealerCard] == 11) && (Cards->TrueCount >= 5))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if ((((Cards->Card[DealerCard] == 9) && (Cards->TrueCount >= 2)) || ((Cards->Card[DealerCard] == 11) && (Cards->TrueCount >= -1))) && (Deviations && Surrendering) && (Cards->CardsDrawn == 2))
        {
            Cards->Choice = Surrender;
        }
        else if ((Cards->Card[DealerCard] == 10) && (Cards->TrueCount < 0))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[DealerCard] == 10) && Surrendering && (Cards->CardsDrawn == 2))
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
    }
    else if (Cards->CardSum >= 13)
    {
        if ((Cards->CardSum == 13) && (Cards->Card[DealerCard] == 2) && (Cards->TrueCount <= -1) && Deviations)
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
    else if (Cards->CardSum == 12)
    {
        if ((((Cards->Card[DealerCard] == 2) && (Cards->TrueCount >= 3)) || ((Cards->Card[DealerCard] == 3) && (Cards->TrueCount >= 2))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if ((Cards->Card[DealerCard] == 4) && (Cards->TrueCount < 0) && Deviations)
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
    else if (Cards->CardSum == 11)
    {
        if (Doubling)
        {
            Cards->Choice = Double;
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if (Cards->CardSum == 10)
    {
        if (Doubling)
        {
            if ((((Cards->Card[DealerCard] == 10) && (Cards->TrueCount >= 4)) || ((Cards->Card[DealerCard] == 11) && (Cards->TrueCount >= 3))) && Deviations)
            {
                Cards->Choice = Double;
            }
            else
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
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if (Cards->CardSum == 9)
    {
        if (Doubling)
        {
            if ((((Cards->Card[DealerCard] == 2) && (Cards->TrueCount >= 1)) || ((Cards->Card[DealerCard] == 7) && (Cards->TrueCount >= 3))) && Deviations)
            {
                Cards->Choice = Double;
            }
            else
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
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else // if (CardSum <= 8)
    {
        if (Doubling)
        {
            if (((Cards->Card[DealerCard] == 6) && (Cards->TrueCount >= 2)) && Deviations)
            {
                Cards->Choice = Double;
            }
            else
            {
                Cards->Choice = Hit;
            }
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    return (EXIT_SUCCESS);
}

int calculateSoftTable(struct Cardstruct *Cards)
{
    int i;
    for (i = 1; i <= Cards->CardsDrawn; i++)
    {
        if (Cards->Card[i] == 11)
        {
        }
        else
        {
            if (Cards->Card[i] == 8)
            {
                if ((((Cards->Card[DealerCard] == 4) && (Cards->TrueCount >= 3)) || ((Cards->Card[DealerCard] == 5) && (Cards->TrueCount >= 1))) && Deviations && Doubling)
                {
                    Cards->Choice = Double;
                }
                else if (((Cards->Card[DealerCard] == 6) && (Cards->TrueCount < 0)) && Deviations)
                {
                    Cards->Choice = Stand;
                }
                else
                {
                    if (Cards->Card[DealerCard] == 6)
                    {
                        if (Doubling)
                        {
                            Cards->Choice = Double;
                        }
                        else
                        {
                            Cards->Choice = Stand;
                        }
                    }
                    else
                    {
                        Cards->Choice = Stand;
                    }
                }
            }
            else if (Cards->Card[i] == 7)
            {
                if (Cards->Card[DealerCard] <= 6)
                {
                    if (Doubling)
                    {
                        Cards->Choice = Double;
                    }
                    else
                    {
                        Cards->Choice = Stand;
                    }
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
            else if (Cards->Card[i] == 6)
            {
                if ((Cards->Card[DealerCard] == 2) && (Cards->TrueCount >= 1) && Deviations && Doubling)
                {
                    Cards->Choice = Double;
                }
                else
                {
                    if ((Cards->Card[DealerCard] >= 3) && (Cards->Card[DealerCard] <= 6))
                    {
                        if (Doubling)
                        {
                            Cards->Choice = Double;
                        }
                        else
                        {
                            Cards->Choice = Hit;
                        }
                    }
                    else
                    {
                        Cards->Choice = Hit;
                    }
                }
            }
            else if ((Cards->Card[i] == 5) || (Cards->Card[i] == 4))
            {
                if ((Cards->Card[DealerCard] >= 4) && (Cards->Card[DealerCard] <= 6))
                {
                    if (Doubling)
                    {
                        Cards->Choice = Double;
                    }
                    else
                    {
                        Cards->Choice = Hit;
                    }
                }
                else
                {
                    Cards->Choice = Hit;
                }
            }
            else if ((Cards->Card[i] == 3) || (Cards->Card[i] == 2))
            {
                if ((Cards->Card[DealerCard] >= 5) && (Cards->Card[DealerCard] <= 6))
                {
                    if (Doubling)
                    {
                        Cards->Choice = Double;
                    }
                    else
                    {
                        Cards->Choice = Hit;
                    }
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
        if ((((Cards->Card[DealerCard] == 4) && (Cards->TrueCount >= 6)) || ((Cards->Card[DealerCard] == 5) && (Cards->TrueCount >= 5)) || ((Cards->Card[DealerCard] == 6) && (Cards->TrueCount >= 4))) && Deviations)
        {
            Cards->Choice = Split;
        }
        else
        {
            calculateHardTable(Cards);
        }
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
        if ((Cards->Card[DealerCard] >= 7) || ((Cards->Card[DealerCard] == 2) && (!DoubleAfterSplit)))
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
        if (((Cards->Card[DealerCard] == 5) || (Cards->Card[DealerCard] == 6)) && (DoubleAfterSplit))
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
        if ((Cards->Card[DealerCard] >= 8) || ((Cards->Card[DealerCard] <= 3) && (!DoubleAfterSplit)))
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
    int j = 1;
    printf("\n");
    for (i = 0; i <= Cards->CardsDrawn; i++)
    {
        if ((i == 0) || ((Cards->arrayPostitionSwitchtoDealer) && (i > Cards->arrayPostitionSwitchtoDealer)))
        {
            printf("Dealer Card %d = ", j);
            j++;
        }
        else
        {
            printf("Card %d = ", i);
        }

        switch (Cards->Card[i])
        {
        case (ONE):
            printf("ACE (%d)\n", ONE);
            break;
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

    return (EXIT_SUCCESS);
}

int compareUserChoice(struct Cardstruct *Cards)
{
    char UserInput[10];
    char ComputedResult[10];
    int score = 0;
    Cards->arrayPostitionSwitchtoDealer = 0;

    calculateDecision(Cards);

    if (Cards->CardSum > 21)
    {
        int i;
        for (i = 1; i <= Cards->CardsDrawn; i++)
        {
            if (Cards->Card[i] == ACE)
            {
                Cards->Card[i] = 1;
                compareUserChoice(Cards);
            }
        }
        printData(Cards);
        printf("Bust! Total = %d\n", Cards->CardSum);
    }
    else if (Cards->CardSum == 21)
    {
        printData(Cards);
        printf("Blackjack!\n");
    }
    else
    {
        printData(Cards);
        printf("What should you do?\n");
        scanf("%s", UserInput);
        printf("Your choice: %s\n", UserInput);

        switch (Cards->Choice)
        {
        case (Stand):
            strcpy(ComputedResult, "Stand");
            break;

        case (Hit):
            strcpy(ComputedResult, "Hit");
            break;

        case (Double):
            strcpy(ComputedResult, "Double");
            break;

        case (Split):
            strcpy(ComputedResult, "Split");
            break;

        case (Surrender):
            strcpy(ComputedResult, "Surrender");
            break;

        default:
            break;
        }

        if (!strcmp(UserInput, ComputedResult))
        {
            score += 1;
            printf("Correct! ");
        }
        else
        {
            printf("Incorrect! ");
        }
        printf("You should: %s\nScore = %d\n", ComputedResult, score);

        if (!strcmp(UserInput, "Stand"))
        {
            // next hand
            Cards->DealerCardSum = Cards->Card[DealerCard];
            Cards->arrayPostitionSwitchtoDealer = Cards->CardsDrawn;
            while (Cards->DealerCardSum <= 17) // hit // TODO soft 17
            {
                Cards->CardsDrawn += 1;
                Cards->DealerCardSum += (int)Cards->Card[Cards->CardsDrawn];
                printData(Cards);

                if (Cards->DealerCardSum > 21)
                {
                    int j;
                    for (j = 0; j <= Cards->CardsDrawn; j++)
                    {
                        if (Cards->Card[j] == ACE && ((j == 0) || (j > Cards->arrayPostitionSwitchtoDealer)))
                        {
                            Cards->Card[j] = 1;
                            Cards->DealerCardSum -= 10;
                            break;
                        }
                    }
                }
            }
            if (Cards->DealerCardSum > 21)
            {
                printf("Dealer bust (%d). You win!\n", Cards->DealerCardSum);
            }
            else if (Cards->CardSum > Cards->DealerCardSum)
            {
                printf("You scored higher than the dealer %d>%d. You win!\n", Cards->CardSum, Cards->DealerCardSum);
            }
            else if (Cards->CardSum == Cards->DealerCardSum)
            {
                printf("Draw\n");
            }
            else
            {
                printf("You scored lower than the dealer %d<%d. You lose!\n", Cards->CardSum, Cards->DealerCardSum);
            }
            return (EXIT_SUCCESS);
        }
        else
        {
            Cards->CardsDrawn += 1;
            compareUserChoice(Cards);
        }
    }
    return (EXIT_SUCCESS);
}