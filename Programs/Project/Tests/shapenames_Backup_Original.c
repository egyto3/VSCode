#include <stdio.h>
#include <stdlib.h>

struct PenStrokeData
{
  int xPosition;
  int yPosition;
  int PenStatus;
};

struct ShapeData
{
  char ShapeName[30];
  int NumberLinesOfShape;
  struct PenStrokeData;
};

int main()
{
  FILE *fptr;
  fptr = fopen("ShapeStrokeData.txt", "r");

  if (fptr == NULL)
  {
    printf("Error opening input file");
    exit(0);
  }

  int Numshapes;
  fscanf(fptr, "%*s %d", &Numshapes); // "%*s" Indicates skipping first string. Only reads value of Numshapes
  printf("%d\n", Numshapes);

  int i;
  for (i = 0; i < Numshapes; i++)
  {
    // Read first line. Get shape name and the number of lines required to read
    struct ShapeData Shape[Numshapes];
    fscanf(fptr, "%s %d", Shape[i].ShapeName, &Shape[i].NumberLinesOfShape);
    printf("%s %d\n", Shape[i].ShapeName, Shape[i].NumberLinesOfShape);

    struct PenStrokeData Shape1Data[Shape[i].NumberLinesOfShape];
    int j;
    for (j = 0; j < Shape[i].NumberLinesOfShape; j++)
    {
      fscanf(fptr, "%d %d %d", &Shape1Data[j].xPosition, &Shape1Data[j].yPosition, &Shape1Data[j].PenStatus);
      printf("%d %d %d\n", Shape1Data[j].xPosition, Shape1Data[j].yPosition, Shape1Data[j].PenStatus);
    }
  }

  fclose(fptr);
}