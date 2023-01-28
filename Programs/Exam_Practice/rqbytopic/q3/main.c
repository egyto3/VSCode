#include <stdio.h>
#include <stdlib.h>

int main()
{
    float number = 0;
    printf("Enter a real number: ");
    scanf("%f", &number);
    if (number > 0)
    {
        printf("The number is positive\n");
    }
    else if (number < 0)
    {
        printf("The number is negative\n");
    }
    return (EXIT_SUCCESS);
}
