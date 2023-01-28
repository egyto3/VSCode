#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int count = 0;

    while (getch() != 'q')
    {
        printf("repeated message\n");
        count++;
    }
    printf("count = %d", count);

    return (EXIT_SUCCESS);
}