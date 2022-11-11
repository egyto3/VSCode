#include <stdio.h>
#include <stdlib.h>

#define ScalingAmount 20/16

int ScaleValues(float *x,float *y);

struct ShapeData
{
  char ShapeName[30];
  int NumberLinesOfShape;
  //int *pSize;

  struct PenStrokeData
  {
    float xPosition;
    float yPosition;
    float PenStatus;
  } Shape1Data[20]; // wasted space

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

    //Shape[i].Shape1Data[i].Shape1DataSize = &Shape[i].NumberLinesOfShape;
    //struct PenStrokeData Shape1Data[Shape[i].NumberLinesOfShape];
    //Shape1Data = (struct PenStrokeData*) malloc(Shape[i].NumberLinesOfShape*sizeof(struct PenStrokeData));

    int j;
    for (j = 0; j < Shape[i].NumberLinesOfShape; j++)
    {
      fscanf(fptr, "%f %f %f", &Shape[i].Shape1Data[j].xPosition, &Shape[i].Shape1Data[j].yPosition, &Shape[i].Shape1Data[j].PenStatus);
      ScaleValues(&Shape[i].Shape1Data[j].xPosition, &Shape[i].Shape1Data[j].yPosition);
      printf("%f %f %f\n", Shape[i].Shape1Data[j].xPosition, Shape[i].Shape1Data[j].yPosition, Shape[i].Shape1Data[j].PenStatus);
    }
  }

  fclose(fptr);
}

int ScaleValues(float *x,float *y)
{
  *x=*x*ScalingAmount;
  *y=*y*ScalingAmount;
  return 0;
}