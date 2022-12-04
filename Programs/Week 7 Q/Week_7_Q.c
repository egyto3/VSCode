#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ShapeData
{
    char ShapeName[10];
    int NumberLinesOfShape;

    struct PenStrokeData
    {
        float xPosition;
        float yPosition;
        int PenStatus;
    } * ShapePositionData;
};

int main()
{

    // char ShapeName[10];
    // int c;
    // int NumberLinesOfShape = 0;

    FILE *fptr;
    fptr = fopen("SingleShape.txt", "r");

    if (fptr == NULL)
    {
        printf("\nError opening input file - aborting ");
        exit(0);
    }

    // Read first line. Get shape name and the number of lines required to read
    struct ShapeData Shape1;
    fscanf(fptr, "%s %d", Shape1.ShapeName, &Shape1.NumberLinesOfShape);
    printf("%s %d\n", Shape1.ShapeName, Shape1.NumberLinesOfShape);

    struct PenStrokeData Shape1Data[Shape1.NumberLinesOfShape];
    int i;
    for (i = 0; i < Shape1.NumberLinesOfShape; i++)
    {
        fscanf(fptr, "%f %f %d", &Shape1[i].ShapePositionData[0].xPosition, &Shape1[i].ShapePositionData[0].yPosition, &Shape1[i].ShapePositionData[0].PenStatus);
        printf("%d %d %d\n", Shape1[i].ShapePositionData[0].xPosition, Shape1[i].ShapePositionData[0].yPosition, Shape1[i].ShapePositionData[0].PenStatus);
    }
    printf("%zu", sizeof(Shape1.ShapePositionData));

    fclose(fptr);
}
