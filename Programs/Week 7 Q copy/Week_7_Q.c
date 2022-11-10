#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

    //char ShapeName[10];
    //int c;
    //int NumberLinesOfShape = 4;

    FILE *fptr;
    fptr = fopen("SingleShape.txt","r");

    if ( fptr == NULL )
    {
     printf ("\nError opening input file - aborting ");
        exit (0);
    }
    char LineData[60];

    //fread(&LineData,10, 1, fptr);
    while (!feof(fptr))
    {
    fgets(LineData, 60, fptr);
    printf("%s\n", LineData);
    }


    fclose(fptr);
}
