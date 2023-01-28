#include <stdio.h>
#include <stdlib.h>

int main()
{
    int value = 0;
    printf("Enter an integer: ");
    scanf("%d", &value);
    switch (value)
    {
    case (1):
        printf("Hello\n");
        break;
    case (7):
        printf("Welcome\n");
        break;
    case (8):
        printf("Hi\n");
        break;
    case (9):
        printf("Cheers\n");
        break;
    case (11):
        printf("Goodbye & Cheers\n");
        break;
    case (12):
        printf("Goodnight\n");
        break;
    }
    return (EXIT_SUCCESS);
}
