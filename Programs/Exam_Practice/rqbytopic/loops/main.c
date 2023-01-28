#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double i;

    for (i = 0.1; i <= 10.1; i += 0.5)
    {
        printf("%.2f ", i);
    }
    printf("\n");

    int j;
    float value;
    for (j = 1; j <= 101; j += 5)
    {
        value = (float)j / 10;
        printf("%.2f ", value);
    }
    printf("\n");

    int k;
    int sum = 0;
    for (k = 1; k <= 10; k++)
    {
        sum += k;
    }
    printf("%d", sum);
    printf("\n");

    int l;
    char letter;
    for (l = 97; l < 97 + 26; l++)
    {
        letter = (char)l;
        printf("%c", letter);
    }
    printf("\n");

    int m;
    char letter2;
    for (m = 65; m < 65 + 26; m++)
    {
        letter2 = (char)(65 + 90 - m);
        printf("%c", letter2);
    }
    printf("\n");

    int n;
    int sum_odd = 0;
    for (n = 1; n < 19; n++)
    {
        if (!(n % 2))
        {
            sum_odd += n;
        }
    }
    printf("sum = %d", sum_odd);
    printf("\n");
    printf("--------------------------------");
    printf("\n");

    float money_count;
    double moneyindollars = 0;
    double moneyinpounds = 0;
    float exchange_rate;
    float increment;
    printf("Enter exchange rate: ");
    scanf("%f", &exchange_rate);
    printf("Enter increment: ");
    scanf("%f", &increment);
    for (money_count = 100; money_count <= 500; money_count += increment)
    {
        moneyinpounds = (double)money_count / 100;
        moneyindollars = moneyinpounds * exchange_rate;
        printf("%.2f pounds = $%.2f\n", moneyinpounds, moneyindollars);
    }
    printf("\n");

    return (EXIT_SUCCESS);
}