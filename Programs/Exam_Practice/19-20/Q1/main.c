#include <stdio.h>
#include <stdlib.h>

int main()
{
    int width = 0;
    printf("Enter the value of the base width of the triangle: ");

    if (scanf("%d", &width) != 1) // Error checking, scanf returns 1 for valid input
    {
        printf("Invalid input");
        exit(EXIT_FAILURE);
    }
    if (width > 10)
    {
        printf("Value too large");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 0; i < width; i++) // loop through height
    {
        for (j = 0; j <= i; j++) // loop number of asterisks
        {
            printf("*");
        }
        printf("\n");
    }
    return (EXIT_SUCCESS);
}
