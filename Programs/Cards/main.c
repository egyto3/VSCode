#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define Deviations 1
#define Surrendering 1
#define Doubling 1
#define DoubleAfterSplit 1
#define DeckNumber 6
#define SplitLimit 2

struct Cardstruct
{
    int FirstCard, SecondCard, DealerCard;
    int deck[52];
    int CardsDrawn;
    int arrayPostitionSwitchtoDealer;
    int CardSum;
    int userDoubled;
    int NumberofGuesses, Score, Money;
    int DealerCardSum;
    int Count;
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
int performUserTurn(struct Cardstruct *Cards);
int calculateCount(struct Cardstruct *Cards);
int updateStatsFile(struct Cardstruct *Cards);
int performDealerTurn(struct Cardstruct *Cards);

int main(void)
{
    int endShoe = 0;

    struct Cardstruct Cards;
    Cards.TrueCount = 1;
    Cards.CardsDrawn = 0;

    Cards.DealerCard = 0;
    Cards.FirstCard = 1;
    Cards.SecondCard = 2;

    generateCards(&Cards);
    Cards.CardsDrawn = 0;
    endShoe = (52 * DeckNumber) - 10; // Arbitrary currently

    int i = 1;
    while (Cards.CardsDrawn < endShoe)
    {
        printf("\n------------------ROUND %d------------------\n", i);
        Cards.CardsDrawn += 3;
        Cards.userDoubled = 0;
        performUserTurn(&Cards);
        // Next round
        Cards.DealerCard = Cards.CardsDrawn;
        Cards.FirstCard = Cards.CardsDrawn + 1;
        Cards.SecondCard = Cards.CardsDrawn + 2;
        i++;
    }
    printf("End of shoe");

    // free(Cards.Card);
    // free(Cards.deck);
    return (EXIT_SUCCESS);
}

int generateCards(struct Cardstruct *Cards)
{
    srand((unsigned int)time(NULL));
    int temp, Value1, Value2, cardNumber;
    // int suit;

    // Cards->deck = malloc(sizeof(Cards->deck) * DeckNumber);
    // if (Cards->deck == NULL)
    // {
    //     printf("Failed to allocate space for deck\n");
    //     exit(EXIT_FAILURE);
    // }

    // Cards->Card = malloc(sizeof(Cards->Card) * DeckNumber);
    // if (Cards->deck == NULL)
    // {
    //     printf("Failed to allocate space for card\n");
    //     exit(EXIT_FAILURE);
    // }

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
        // suit = Cards->deck[i] % 4;
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
    for (i = Cards->DealerCard + 1; i <= Cards->CardsDrawn - 1; i++)
    {
        Cards->CardSum += (int)Cards->Card[i];
    }

    if ((Cards->Card[Cards->FirstCard] == Cards->Card[Cards->SecondCard])) // Split table
    {
        calculateSplitTable(Cards);
    }
    else
    {
        for (i = Cards->DealerCard + 1; i <= Cards->CardsDrawn - 1; i++)
        {
            if (Cards->Card[i] == 11) // Soft total table
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
        if ((((Cards->Card[Cards->DealerCard] == 9) && (Cards->TrueCount >= 4)) || ((Cards->Card[Cards->DealerCard] == 10) && (Cards->TrueCount > 0)) || ((Cards->Card[Cards->DealerCard] == 11) && (Cards->TrueCount >= 3))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if (((Cards->Card[Cards->DealerCard] == 8) && (Cards->TrueCount >= 4)) && (Deviations && Surrendering) && ((Cards->CardsDrawn % 3) == 0))
        {
            Cards->Choice = Surrender;
        }
        else if ((Cards->Card[Cards->DealerCard] == 9) && (Cards->TrueCount <= -1))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[Cards->DealerCard] >= 9) && Surrendering && ((Cards->CardsDrawn % 3) == 0))
            {
                Cards->Choice = Surrender;
            }
            else
            {
                if (Cards->Card[Cards->DealerCard] <= 6)
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
        if ((((Cards->Card[Cards->DealerCard] == 10) && (Cards->TrueCount >= 4)) || ((Cards->Card[Cards->DealerCard] == 11) && (Cards->TrueCount >= 5))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if ((((Cards->Card[Cards->DealerCard] == 9) && (Cards->TrueCount >= 2)) || ((Cards->Card[Cards->DealerCard] == 11) && (Cards->TrueCount >= -1))) && (Deviations && Surrendering) && (Cards->CardsDrawn == 2))
        {
            Cards->Choice = Surrender;
        }
        else if ((Cards->Card[Cards->DealerCard] == 10) && (Cards->TrueCount < 0))
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[Cards->DealerCard] == 10) && Surrendering && ((Cards->CardsDrawn % 3) == 0))
            {
                Cards->Choice = Surrender;
            }
            else
            {
                if (Cards->Card[Cards->DealerCard] <= 6)
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
        if ((Cards->CardSum == 13) && (Cards->Card[Cards->DealerCard] == 2) && (Cards->TrueCount <= -1) && Deviations)
        {
            Cards->Choice = Hit;
        }
        else
        {
            if (Cards->Card[Cards->DealerCard] <= 6)
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
        if ((((Cards->Card[Cards->DealerCard] == 2) && (Cards->TrueCount >= 3)) || ((Cards->Card[Cards->DealerCard] == 3) && (Cards->TrueCount >= 2))) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else if ((Cards->Card[Cards->DealerCard] == 4) && (Cards->TrueCount < 0) && Deviations)
        {
            Cards->Choice = Hit;
        }
        else
        {
            if ((Cards->Card[Cards->DealerCard] >= 4) && (Cards->Card[Cards->DealerCard] <= 6))
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
            if ((((Cards->Card[Cards->DealerCard] == 10) && (Cards->TrueCount >= 4)) || ((Cards->Card[Cards->DealerCard] == 11) && (Cards->TrueCount >= 3))) && Deviations)
            {
                Cards->Choice = Double;
            }
            else
            {
                if (Cards->Card[Cards->DealerCard] <= 9)
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
            if ((((Cards->Card[Cards->DealerCard] == 2) && (Cards->TrueCount >= 1)) || ((Cards->Card[Cards->DealerCard] == 7) && (Cards->TrueCount >= 3))) && Deviations)
            {
                Cards->Choice = Double;
            }
            else
            {
                if ((Cards->Card[Cards->DealerCard] >= 3) && (Cards->Card[Cards->DealerCard] <= 6))
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
            if (((Cards->Card[Cards->DealerCard] == 6) && (Cards->TrueCount >= 2)) && Deviations)
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
    Cards->CardSum -= 11;
    if (Cards->CardSum == 8)
    {
        if ((((Cards->Card[Cards->DealerCard] == 4) && (Cards->TrueCount >= 3)) || ((Cards->Card[Cards->DealerCard] == 5) && (Cards->TrueCount >= 1))) && Deviations && Doubling)
        {
            Cards->Choice = Double;
        }
        else if (((Cards->Card[Cards->DealerCard] == 6) && (Cards->TrueCount < 0)) && Deviations)
        {
            Cards->Choice = Stand;
        }
        else
        {
            if (Cards->Card[Cards->DealerCard] == 6)
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
    else if (Cards->CardSum == 7)
    {
        if (Cards->Card[Cards->DealerCard] <= 6)
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
        else if (Cards->Card[Cards->DealerCard] <= 8)
        {
            Cards->Choice = Stand;
        }
        else
        {
            Cards->Choice = Hit;
        }
    }
    else if (Cards->CardSum == 6)
    {
        if ((Cards->Card[Cards->DealerCard] == 2) && (Cards->TrueCount >= 1) && Deviations && Doubling)
        {
            Cards->Choice = Double;
        }
        else
        {
            if ((Cards->Card[Cards->DealerCard] >= 3) && (Cards->Card[Cards->DealerCard] <= 6))
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
    else if ((Cards->CardSum == 5) || (Cards->CardSum == 4))
    {
        if ((Cards->Card[Cards->DealerCard] >= 4) && (Cards->Card[Cards->DealerCard] <= 6))
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
    else if ((Cards->CardSum == 3) || (Cards->CardSum == 2))
    {
        if ((Cards->Card[Cards->DealerCard] >= 5) && (Cards->Card[Cards->DealerCard] <= 6))
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

    Cards->CardSum += 11;
    return (EXIT_SUCCESS);
}

int calculateSplitTable(struct Cardstruct *Cards)
{
    if (Cards->Card[Cards->FirstCard] == 11)
    {
        Cards->Choice = Split;
    }
    else if (Cards->Card[Cards->FirstCard] == 10)
    {
        if ((((Cards->Card[Cards->DealerCard] == 4) && (Cards->TrueCount >= 6)) || ((Cards->Card[Cards->DealerCard] == 5) && (Cards->TrueCount >= 5)) || ((Cards->Card[Cards->DealerCard] == 6) && (Cards->TrueCount >= 4))) && Deviations)
        {
            Cards->Choice = Split;
        }
        else
        {
            calculateHardTable(Cards);
        }
    }
    else if (Cards->Card[Cards->FirstCard] == 9)
    {
        if ((Cards->Card[Cards->DealerCard] == 7) || (Cards->Card[Cards->DealerCard] == 10) || (Cards->Card[Cards->DealerCard] == 11))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[Cards->FirstCard] == 8)
    {
        Cards->Choice = Split;
    }
    else if (Cards->Card[Cards->FirstCard] == 7)
    {
        if ((Cards->Card[Cards->DealerCard] >= 8))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[Cards->FirstCard] == 6)
    {
        if ((Cards->Card[Cards->DealerCard] >= 7) || ((Cards->Card[Cards->DealerCard] == 2) && (!DoubleAfterSplit)))
            calculateHardTable(Cards);
        else
        {
            Cards->Choice = Split;
        }
    }
    else if (Cards->Card[Cards->FirstCard] == 5)
    {
        calculateHardTable(Cards);
    }
    else if (Cards->Card[Cards->FirstCard] == 4)
    {
        if (((Cards->Card[Cards->DealerCard] == 5) || (Cards->Card[Cards->DealerCard] == 6)) && (DoubleAfterSplit))
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
        if ((Cards->Card[Cards->DealerCard] >= 8) || ((Cards->Card[Cards->DealerCard] <= 3) && (!DoubleAfterSplit)))
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
    int k = 1;
    printf("\n");
    for (i = Cards->DealerCard; i <= Cards->CardsDrawn - 1; i++)
    {
        if ((i == Cards->DealerCard) || ((Cards->arrayPostitionSwitchtoDealer) && (i > Cards->arrayPostitionSwitchtoDealer)))
        {
            printf("Dealer Card %d = ", j);
            j++;
        }
        else
        {
            printf("Card %d = ", k);
            k += 1;
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
    printf("\n");

    return (EXIT_SUCCESS);
}

int performUserTurn(struct Cardstruct *Cards)
{
    char UserDecisionGuess[10];
    char buffer[10];
    int UserCountGuess = 0;
    int UserTrueCountGuess = 0;
    char ComputedResult[10];
    int i;
    char *end;
    Cards->arrayPostitionSwitchtoDealer = 0;
    Cards->Score = 0;
    Cards->NumberofGuesses = 0;

    calculateDecision(Cards);
    calculateCount(Cards);
    printData(Cards);

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
        printf("Error! Not a valid option\n");
        break;
    }

    // check if bust
    if (Cards->CardSum == 21)
    {
        printf("Blackjack!\n");
    }
    else if (Cards->CardSum > 21)
    {
        for (i = Cards->DealerCard + 1; i <= Cards->CardsDrawn - 1; i++)
        {
            if (Cards->Card[i] == ACE)
            {
                Cards->Card[i] = 1;
                performUserTurn(Cards);
                Cards->userDoubled = 0;
                return (EXIT_SUCCESS);
            }
        }
        printf("Bust! Total = %d\n", Cards->CardSum);
    }
    else if (Cards->CardSum == 21)
    {
        printf("Blackjack!\n");
    }
    else
    {

        // User input for count
        while (1)
        {
            printf("What is the count?\n");
            scanf("%9s", buffer);
            UserCountGuess = strtol(buffer, &end, 10);
            if (end == buffer)
            {
                printf("Not a valid number\n\n");
            }
            else
            {
                break;
            }
        }
        printf("Your choice: %d\n", UserCountGuess);
        printf("The actual count: %d\n", Cards->Count);

        // User input for true count
        if (DeckNumber != 1)
        {
            while (1)
            {
                printf("What is the true count?\n");
                scanf("%9s", buffer);
                UserTrueCountGuess = strtol(buffer, &end, 10);
                if (end == buffer)
                {
                    printf("Not a valid number\n\n");
                }
                else
                {
                    break;
                }
            }
            printf("Your choice: %d\n", UserTrueCountGuess);
            printf("The true count: %d\n", Cards->TrueCount);
        }

        if (!Cards->userDoubled)
        {
            // Strategy decision
            while (1)
            {
                printf("\nWhat should you do?\n");
                scanf("%s", UserDecisionGuess);
                printf("Your choice: %s\n", UserDecisionGuess);

                // Check if choice is possible
                if (strcmp(UserDecisionGuess, "Stand") && strcmp(UserDecisionGuess, "Hit") && strcmp(UserDecisionGuess, "Double") && strcmp(UserDecisionGuess, "Split") && strcmp(UserDecisionGuess, "Surrender"))
                {
                    printf("Not an option\n");
                }
                else if (!strcmp(UserDecisionGuess, "Split") && !(Cards->Card[Cards->FirstCard] == Cards->Card[Cards->SecondCard]))
                {
                    printf("You can't split\n");
                }
                else if (!strcmp(UserDecisionGuess, "Double") && ((Cards->CardsDrawn - Cards->DealerCard) % 3)) // Check if trying to Double after first turn
                {
                    printf("No longer first move - You can't double\n");
                }
                else
                {
                    break;
                }
            }
            Cards->NumberofGuesses++;

            if (!strcmp(UserDecisionGuess, ComputedResult))
            {
                Cards->Score += 1;
                printf("Correct! ");
            }
            else
            {
                printf("Incorrect! ");
            }
            printf("You should: %s\n", ComputedResult);
            updateStatsFile(Cards);
        }

        if (!strcmp(UserDecisionGuess, "Stand") || (Cards->userDoubled == 1))
        {
            performDealerTurn(Cards);
        }
        else
        {
            if (Cards->CardsDrawn >= (52 * DeckNumber))
            {
                printf("Can't draw more cards (deck is empty)");
                return (EXIT_FAILURE);
            }
            if (!strcmp(UserDecisionGuess, "Double"))
            {
                Cards->userDoubled = 1;
            }
            Cards->CardsDrawn += 1;
            performUserTurn(Cards);
        }
    }
    Cards->userDoubled = 0;

    return (EXIT_SUCCESS);
}

int performDealerTurn(struct Cardstruct *Cards)
{
    // Dealers turn
    Cards->DealerCardSum = Cards->Card[Cards->DealerCard];
    Cards->arrayPostitionSwitchtoDealer = Cards->CardsDrawn - 1;
    while (Cards->DealerCardSum < 17) // hit
    {
        if (Cards->CardsDrawn >= (52 * DeckNumber))
        {
            printf("Can't draw more cards (deck is empty)");
            return (EXIT_FAILURE);
        }
        Cards->CardsDrawn += 1;
        Cards->DealerCardSum += (int)Cards->Card[Cards->CardsDrawn - 1];
        calculateCount(Cards);
        printData(Cards);

        if ((Cards->DealerCardSum > 21) || (Cards->DealerCardSum == 17)) // Hit on soft 17
        {
            int j;
            for (j = Cards->DealerCard; j <= Cards->CardsDrawn - 1; j++)
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

int calculateCount(struct Cardstruct *Cards)
{
    Cards->Count = 0;
    int i;
    for (i = 0; i <= Cards->CardsDrawn - 1; i++)
    {
        if ((Cards->Card[i] >= 2) && (Cards->Card[i] <= 6))
        {
            Cards->Count += 1;
        }
        else if ((Cards->Card[i] >= 7) && (Cards->Card[i] <= 9))
        {
            // Do nothing //Cards->Count += 0;
        }
        else // Ace or 10
        {
            Cards->Count -= 1;
        }
    }
    Cards->TrueCount = Cards->Count / DeckNumber;

    return (EXIT_SUCCESS);
}

int updateStatsFile(struct Cardstruct *Cards)
{
    int tempNumberofGuesses = 0;
    int tempScore = 0;
    int tempMoney = 0;
    FILE *Statsfptr;

    if (access("Stats.txt", F_OK) == 0)
    {
        Statsfptr = fopen("C:\\Users\\Tom\\VSCode\\Programs\\Cards\\Stats.txt", "r+");
        if (Statsfptr == NULL)
        {
            printf("Error opening file!");
            exit(EXIT_FAILURE);
        }
        fscanf(Statsfptr, "%*s %d", &tempScore);
        fscanf(Statsfptr, "%*s %d", &tempNumberofGuesses);
        fscanf(Statsfptr, "%*s %d", &tempMoney);
        Cards->Score += tempScore;
        Cards->NumberofGuesses += tempNumberofGuesses;
        Cards->Money += tempMoney;
        fclose(Statsfptr);
    }
    else
    {
        Cards->Money = 10000;
    }

    Statsfptr = fopen("C:\\Users\\Tom\\VSCode\\Programs\\Cards\\Stats.txt", "w+");
    if (Statsfptr == NULL)
    {
        printf("Error opening file!");
        exit(EXIT_FAILURE);
    }

    fprintf(Statsfptr, "%s %d %s", "Score", Cards->Score, "\n");
    fprintf(Statsfptr, "%s %d %s", "Total_Guesses", Cards->NumberofGuesses, "\n");
    fprintf(Statsfptr, "%s %d", "Money", Cards->Money);
    fseek(Statsfptr, 0, SEEK_SET);
    fclose(Statsfptr);

    printf("Score = %.2f%%\n", ((float)Cards->Score / (float)Cards->NumberofGuesses) * 100);

    return (EXIT_SUCCESS);
}