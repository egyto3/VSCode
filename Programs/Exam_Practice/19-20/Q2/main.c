#include <stdio.h>
#include <stdlib.h>

int main()
{
    int value[100];
    char FirstName[20];
    char Surname[20];
    int i = 0;
    int min, max, mean;
    int total = 0;
    FILE *fptr;
    fptr = fopen("data.dat", "rb");
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %s %d", FirstName, Surname, &value[i]);
        printf("%d\n", value[i]);
        i++;
    }

    max = value[0];
    min = value[0];

    int j;
    for (j = 1; j < i; j++)
    {
        total += value[j];
        if (value[j] > max)
        {
            max = value[j];
        }
        else if (value[j] < min)
        {
            min = value[j];
        }
    }
    mean = total/(i-1);
    printf("minimum = %d\n", min);
    printf("maximum = %d\n", max);
    printf("mean = %d\n", mean);
    return (EXIT_SUCCESS);
}
