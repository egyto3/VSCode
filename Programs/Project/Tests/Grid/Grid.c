#include <stdio.h>
#include <stdlib.h>

int main()
{
    char FileName[20];
    int DrawGrid;

    // Get text file name from user
    printf("Please enter the file name with format:\n");
    scanf("%s", FileName);
    printf("%s\n", FileName);

    // Open text file
    FILE *fptr;
    fptr = fopen(FileName, "r");

    
    fscanf(fptr, "%*s %d", &DrawGrid);  // Read value of DrawGrid and store it
    printf("%d\n", DrawGrid);

    fclose(fptr);
}