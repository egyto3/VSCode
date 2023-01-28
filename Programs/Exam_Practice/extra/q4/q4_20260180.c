#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int number[10];
    FILE *fptr;
    fptr = fopen("numbers.bin", "wb+");
    if (fptr == NULL)
    {
        exit(0);
    }
    int i;
    for (i = 0; i < 10; i++)
    {
        fwrite(&i, sizeof(int), 1, fptr);
    }
    fseek(fptr, 0, SEEK_SET);
    int j = 0;
    while (!feof(fptr))
    {
        fread(&number[j], sizeof(int), 1, fptr);
        j++;
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", number[i]);
    }
    fclose(fptr);
    return (EXIT_SUCCESS);
}