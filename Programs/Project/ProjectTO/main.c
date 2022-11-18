#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "string.h"

#define bdrate 115200 /* 115200 baud */
#define ScalingAmount 20 / 16
#define GridSpacing 30

void SendCommands(char *buffer);
int ReadShapes();
int ScaleValues(float *x, float *y);
int ReadInstructions();
int ConverttoGCode();
int CreateGrid();

struct ShapeData
{
    char *ShapeName;
    int NumberLinesOfShape;

    struct PenStrokeData
    {
        float xPosition;
        float yPosition;
        float PenStatus;
    } * ShapePositonData;
};

struct Grid
{
    int DrawGridValue;

    struct GridData
    {
        int Grid_x;
        int Grid_y;
        char *GridShapeName;
    } * ShapestoDraw;
};

int main()
{
    char buffer[100];

    struct Grid DrawGrid;
    struct ShapeData *Shape;
    ReadShapes(&Shape);
    ReadInstructions(&DrawGrid);
    printf("%s\n",DrawGrid.ShapestoDraw[0].GridShapeName);
    printf("%d\n", Shape[0].NumberLinesOfShape);
    //printf("%s %d\n", Shape[0].ShapeName, Shape[0].NumberLinesOfShape);


    // If we cannot open the port then give up immediatly
    if (CanRS232PortBeOpened() == -1)
    {
        printf("\nUnable to open the COM port (specified in serial.h) ");
        exit(0);
    }

    // Time to wake up the robot
    printf("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf(buffer, "\n");
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer(&buffer[0]);
    Sleep(100);

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf("\nThe robot is now ready to draw\n");

    // These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    sprintf(buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf(buffer, "M3\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);

    // New commands
    ConverttoGCode(buffer, &DrawGrid, &Shape);

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    return (0);
}

/* Send the data to the robot - note in 'PC' mode you need to hit space twice
    as the dummy 'WaitForReply' has a getch() within the function.*/
void SendCommands(char *buffer)
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer(&buffer[0]);
    WaitForReply();
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
    // getch(); // Omit this once basic testing with emulator has taken place
}

int ReadShapes(struct ShapeData *Shape)
{
    FILE *fptr;
    fptr = fopen("ShapeStrokeData.txt", "r");

    if (fptr == NULL)
    {
        printf("Error opening file");
        exit(0);
    }

    int Numshapes;
    fscanf(fptr, "%*s %d", &Numshapes); // "%*s" Indicates skipping first string. Only reads value of Numshapes
    printf("%d\n", Numshapes);
    // struct ShapeData Shape[Numshapes];

    Shape = malloc(sizeof(*Shape) * Numshapes); // Acts as array of size Numshapes

    int i;
    for (i = 0; i < Numshapes; i++)
    {
        // Read first line. Get shape name and the number of lines required to read

        Shape[i].ShapeName = malloc(sizeof(*Shape->ShapeName)); // Acts as array of size ShapeName
        fscanf(fptr, "%s %d", Shape[i].ShapeName, &Shape[i].NumberLinesOfShape);
        printf("%s %d\n", Shape[i].ShapeName, Shape[i].NumberLinesOfShape);

        Shape[i].ShapePositonData = malloc(sizeof(*Shape->ShapePositonData) * Shape[i].NumberLinesOfShape); // ShapePositonData acts as array of size NumberLinesOfShape

        int j;
        for (j = 0; j < Shape[i].NumberLinesOfShape; j++)
        {
            fscanf(fptr, "%f %f %f", &Shape[i].ShapePositonData[j].xPosition, &Shape[i].ShapePositonData[j].yPosition, &Shape[i].ShapePositonData[j].PenStatus);
            ScaleValues(&Shape[i].ShapePositonData[j].xPosition, &Shape[i].ShapePositonData[j].yPosition);
            printf("%f %f %f\n", Shape[i].ShapePositonData[j].xPosition, Shape[i].ShapePositonData[j].yPosition, Shape[i].ShapePositonData[j].PenStatus);
        }
    }

    fclose(fptr);
    printf("%d\n", Shape[0].NumberLinesOfShape);
    return 0;
}

int ScaleValues(float *x, float *y)
{
    *x = *x * ScalingAmount;
    *y = *y * ScalingAmount;
    return 0;
}

int ReadInstructions(struct Grid *DrawGrid)
{
    char FileName[20];

    // Get text file name from user
    printf("Please enter the file name with format:\n");
    scanf("%s", FileName);

    // Open text file
    FILE *fptr;
    fptr = fopen(FileName, "r");

    if (fptr == NULL)
    {
        printf("Error opening file called: %s\n", FileName);
        exit(0);
    }

    // Get number of lines in file
    char EndLineIdentifier;
    int LineCount = 0;
    while ((EndLineIdentifier = fgetc(fptr)) != EOF)
    {
        if (EndLineIdentifier == '\n')
        {
            LineCount++;
            /*  Note that the true number of lines in file will be 1 more as there is no \n at end of file.
                First line is determining whether to draw grid so useful lines are true linecount-1.
                Therefore useful number of lines = LineCount */
        }
    }
    rewind(fptr);

    fscanf(fptr, "%*s %d", &DrawGrid->DrawGridValue); // Read value of Draw_Grid (0 or 1) and store it

    DrawGrid->ShapestoDraw = malloc(sizeof(*DrawGrid->ShapestoDraw) * LineCount); // Acts as array of size LineCount

    // Read and store data to draw line by line
    int i;
    for (i = 0; i < LineCount; i++)
    {
        DrawGrid->ShapestoDraw[i].GridShapeName = malloc(sizeof(*DrawGrid->ShapestoDraw[i].GridShapeName)); // Acts as array of size GridShapeName
        fscanf(fptr, "%d %d %s", &DrawGrid->ShapestoDraw[i].Grid_x, &DrawGrid->ShapestoDraw[i].Grid_y, DrawGrid->ShapestoDraw[i].GridShapeName);
        printf("%d %d %s\n", DrawGrid->ShapestoDraw[i].Grid_x, DrawGrid->ShapestoDraw[i].Grid_y, DrawGrid->ShapestoDraw[i].GridShapeName);
    }

    fclose(fptr);
    return 0;
}

int ConverttoGCode(char *buffer, struct Grid *DrawGrid, struct ShapeData *Shape)
{
    if (DrawGrid->DrawGridValue == 1)
    {
        CreateGrid(buffer);
    }

    //(DrawGrid->ShapestoDraw[0].Grid_x - 1)*GridSpacing + GridSpacing/2;  // Formula for distance to centre grid position. Eg for grid 2: distance = (2-1)*30 + 30/2 = 45
    //-((DrawGrid->ShapestoDraw[0].Grid_y - 1)*GridSpacing + GridSpacing/2);  // Same as above but for y coordinate which is negative (Origin is top left)
    float StartPos_x;
    float StartPos_y;
    char temp_command[20];
    StartPos_x = DrawGrid->ShapestoDraw[0].Grid_x * GridSpacing;
    StartPos_y = - (4 - DrawGrid->ShapestoDraw[0].Grid_y) * GridSpacing; // Origin is top left while 1,1 is bottom left

    printf("%s\n%s",DrawGrid->ShapestoDraw[0].GridShapeName,Shape[0].ShapeName);
    if (DrawGrid->ShapestoDraw[0].GridShapeName == Shape[1].ShapeName)
    {
        sprintf(temp_command,"G0 X%f Y%f",StartPos_x,StartPos_y);

        sprintf(buffer, "S0\n");
        SendCommands(buffer);
        sprintf(buffer, temp_command);
        SendCommands(buffer);
    }
    return 0;
}

int CreateGrid(char *buffer)
{
    sprintf(buffer, "S1000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X90 Y0.000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X90 Y-90\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X0 Y-90\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X0 Y0\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X30 Y0\n");
    SendCommands(buffer);
    sprintf(buffer, "S1000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X30 Y-90\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X60 Y-90\n");
    SendCommands(buffer);
    sprintf(buffer, "S1000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X60 Y0\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X90 Y-30\n");
    SendCommands(buffer);
    sprintf(buffer, "S1000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X0 Y-30\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X0 Y-60\n");
    SendCommands(buffer);
    sprintf(buffer, "S1000\n");
    SendCommands(buffer);
    sprintf(buffer, "G1 X90 Y-60\n");
    SendCommands(buffer);
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X0 Y0\n");
    SendCommands(buffer);
    return 0;
}