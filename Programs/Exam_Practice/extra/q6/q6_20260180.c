// Thomas Oczadly 20260180
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *score;
    int readvalue[50];

    // allocate memory
    score = (int *)malloc(sizeof(int) * 20);
    // check if memory is allocated correctly
    if (score == NULL)
    {
        printf("Failed to allocate space");
        return (EXIT_FAILURE);
    }

    // loop for input
    int i;
    for (i = 0; i < 20; i++)
    {
        score[i] = i * 5;
    }

    // open file in write and read mode
    FILE *fptr;
    fptr = fopen("score.txt", "w+");
    int j;

    // write to file
    for (j = 0; j < 20; j++)
    {
        fprintf(fptr, "%d\n", score[j]);
    }

    int k = 0;
    fseek(fptr, 0, SEEK_SET); // start from beginning of file
    // read file
    while (!feof(fptr))
    {
        fscanf(fptr, "%d", &readvalue[k]);
        k++;
    }

    // print outputs
    for (j = 0; j < 20; j++)
    {
        printf("%d\n", readvalue[j]);
    }
    fclose(fptr);

    int *value = &score[3];
    printf("\n\n%d", *value);

    free(score);
    return (EXIT_SUCCESS);
}