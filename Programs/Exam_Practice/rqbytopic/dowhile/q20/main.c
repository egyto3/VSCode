#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 0;
    int number_squared = 0;
    do
    {
        printf("Enter a number: ");
        scanf("%d", &number);
        number_squared = number * number;
        printf("number = %d number^2 = %d\n", number, number_squared);

    } while (number <= 99);

    return (EXIT_SUCCESS);
}