#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define text 1

int main()
{
    int score;
    char name[30];
#ifdef text
    FILE *filein;
    filein = fopen("golf.txt", "r+");
    if (filein == NULL)
    {
        return (EXIT_FAILURE);
    }
    while (!feof(filein))
    {
        fscanf(filein, "%s %d", name, &score);
        printf("%s %d\n", name, score);
    }
    // fseek(filein,0,SEEK_END);
    fprintf(filein, "\n%s %d", name, score);
#else
    FILE *filein;
    filein = fopen("golf.bin", "rb");
    while (!feof(filein))
    {
        fread(&score, sizeof(int), 1, filein);
        printf("%d\n", score);
    }
    fgetc(filein);
    // fseek(filein,0,SEEK_END);
    // fprintf(filein, "\n%s %d", name, score);
    fclose(filein);
#endif
    fclose(filein);

    return (EXIT_SUCCESS);
}