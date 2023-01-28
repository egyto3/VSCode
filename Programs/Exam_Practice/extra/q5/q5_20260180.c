#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define text 1

int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s", argv[i]);
    }
    return (EXIT_SUCCESS);
}