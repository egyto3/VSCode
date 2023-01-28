#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    char input;
    int total_count = 0;
    int even_count = 0;
    int odd_count = 0;

    while (1)
    {
        printf("Press numerical key. To exit press 'i'\n");
        input = (char)getch();

        if (input == 'i') // Check if program needs to end
        {
            break;
        }

        if ((input >= 48) && (input <= 57))
        {
            if (((int)input % 2) == 0) // remainder 0 is even
            {
                even_count++;
            }
            else if (((int)input % 2) == 1) // remainder 1 is odd
            {
                odd_count++;
            }
        }
        total_count++;
    }

    printf("Total keys pressed: %d\n", total_count);
    printf("Even keys pressed: %d\nPercentage = %f%%\n", even_count, ((float)even_count * 100 / (float)total_count));
    printf("Odd keys pressed: %d\nPercentage = %f%%\n", odd_count, ((float)odd_count * 100 / (float)total_count));
    return (EXIT_SUCCESS);
}