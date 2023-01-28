#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

    int i;
    float rms;
    int sum = 0;
    for (i = 1; i <= 5; i++)
    {
        sum += i * i;
        
    }
    rms = (float)sqrt(sum/5);
    printf("RMS = %.3f",rms);
    return (EXIT_SUCCESS);
}