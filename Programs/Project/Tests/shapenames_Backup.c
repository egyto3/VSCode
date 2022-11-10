#include <stdio.h>
#include <stdlib.h>


struct ShapeData
{
  char ShapeName[30];
  int NumberLinesOfShape;

  struct PenStrokeData
  {
    int xPosition;
    int yPosition;
    int PenStatus;
  } Shape1Data[20];

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
  fscanf(fptr, "%*s %d", &Numshapes);
  printf("%d\n", Numshapes);

  int i;
  for (i = 0; i < Numshapes; i++)
  {
    // Read first line. Get shape name and the number of lines required to read

    struct ShapeData Shape[Numshapes];
    fscanf(fptr, "%s %d", Shape[i].ShapeName, &Shape[i].NumberLinesOfShape);
    printf("%s %d\n", Shape[i].ShapeName, Shape[i].NumberLinesOfShape);

    //struct PenStrokeData Shape1Data[Shape[i].NumberLinesOfShape];

    int j;
    for (j = 0; j < Shape[i].NumberLinesOfShape; j++)
    {
      fscanf(fptr, "%d %d %d", &Shape[i].Shape1Data[j].xPosition, &Shape[i].Shape1Data[j].yPosition, &Shape[i].Shape1Data[j].PenStatus);
      printf("%d %d %d\n", Shape[i].Shape1Data[j].xPosition, Shape[i].Shape1Data[j].yPosition, Shape[i].Shape1Data[j].PenStatus);
    }
  }

  fclose(fptr);
}