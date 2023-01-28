#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int i;
    int num_array[100];
    for (i = 0; i < 100; i++)
    {
        num_array[i] = i * i;
    }
    for (i = 0; i < 100; i++)
    {
        printf("%d\n", num_array[i]);
    }
    printf("\n---------------------------------------------------------------------\n\n");

    float float_array[360];
    for (i = 0; i < (int)(sizeof(float_array) / sizeof(float)); i++)
    {
        float_array[i] = i * M_PI / 180;
    }
    for (i = 0; i < (int)(sizeof(float_array) / sizeof(float)); i++)
    {
        printf("%d deg = %f rad\n", i, float_array[i]);
    }

    return (EXIT_SUCCESS);
}