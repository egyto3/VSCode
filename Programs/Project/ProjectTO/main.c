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
#define GridStartPositionOffset 5
#define MaxShapeNameSize 30

struct ShapeData
{
    char ShapeName[MaxShapeNameSize];
    int NumberLinesOfShape;

    struct PenStrokeData
    {
        float xPosition;
        float yPosition;
        int PenStatus;
    } * ShapePositionData;
};

struct InstructionData
{
    int DrawGridValue;

    struct GridData
    {
        int ShapeGridPosition_x;
        int ShapeGridPosition_y;
        char InstructionsShapeName[MaxShapeNameSize];
    } * ShapestoDraw;
};

void SendCommands(char *buffer);
int ReadShapeInformation(struct ShapeData *Shape, FILE *fptrShapeInstructions, int *Numshapes);
int ReadInstructions(struct InstructionData *Instructions, int *NumInstructions);
int ConverttoGCode(char *buffer, struct InstructionData *Instructions, struct ShapeData *Shape, int *Numshapes, int *NumInstructions);
int CreateGrid(char *buffer);

int main()
{
    char buffer[100];
    int Numshapes = 0;
    int NumInstructions = 0;

    FILE *fptrShapeInstructions;
    fptrShapeInstructions = fopen("ShapeStrokeData.txt", "r");

    if (fptrShapeInstructions == NULL)
    {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(fptrShapeInstructions, "%*s %d", &Numshapes); // "%*s" Indicates skipping first string. Only reads value of Numshapes

    struct ShapeData *Shape;
    Shape = malloc(sizeof(*Shape) * (long long unsigned)Numshapes); // Acts as array of size Numshapes
    if (Shape == NULL)
    {
        printf("Failed to allocate space for Shape\n");
        exit(EXIT_FAILURE);
    }

    struct InstructionData Instructions;

    ReadShapeInformation(Shape, fptrShapeInstructions, &Numshapes);
    ReadInstructions(&Instructions, &NumInstructions);

    // If we cannot open the port then give up immediatly
    if (CanRS232PortBeOpened() == -1)
    {
        printf("\nUnable to open the COM port (specified in serial.h) ");
        exit(EXIT_FAILURE);
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
    ConverttoGCode(buffer, &Instructions, Shape, &Numshapes, &NumInstructions);

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    free(Shape->ShapePositionData);
    free(Shape);
    free(Instructions.ShapestoDraw);

    return (EXIT_SUCCESS);
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

int ReadShapeInformation(struct ShapeData *Shape, FILE *fptrShapeInstructions, int *Numshapes)
{
    int i;
    for (i = 0; i < *Numshapes; i++)
    {
        // Read first line. Get shape name and the number of lines required to read
        fscanf(fptrShapeInstructions, "%s %d", Shape[i].ShapeName, &Shape[i].NumberLinesOfShape);

        Shape[i].ShapePositionData = malloc(sizeof(*Shape->ShapePositionData) * (long long unsigned)Shape[i].NumberLinesOfShape); // ShapePositionData acts as array of size NumberLinesOfShape
        if (Shape[i].ShapePositionData == NULL)
        {
            printf("Failed to allocate space for Shape[i].ShapePositionData\n");
            exit(EXIT_FAILURE);
        }

        int j;
        for (j = 0; j < Shape[i].NumberLinesOfShape; j++)
        {
            fscanf(fptrShapeInstructions, "%f %f %d", &Shape[i].ShapePositionData[j].xPosition, &Shape[i].ShapePositionData[j].yPosition, &Shape[i].ShapePositionData[j].PenStatus);

            // Scale values
            Shape[i].ShapePositionData[j].xPosition = Shape[i].ShapePositionData[j].xPosition * ScalingAmount;
            Shape[i].ShapePositionData[j].yPosition = Shape[i].ShapePositionData[j].yPosition * ScalingAmount;
        }
    }

    fclose(fptrShapeInstructions);
    return (EXIT_SUCCESS);
}

int ReadInstructions(struct InstructionData *Instructions, int *NumInstructions)
{
    char FileName[20];

    // Get text file name from user
    printf("Please enter the file name (Exclude '.txt'):\n");
    scanf("%s", FileName);
    strcat(FileName, ".txt");

    if (strlen(FileName) > 20)
    {
        printf("File name is too large\n");
        exit(EXIT_FAILURE);
    }

    // Open text file
    FILE *fptr;
    fptr = fopen(FileName, "r");

    if (fptr == NULL)
    {
        printf("Error opening file called: %s\n\n", FileName);
        ReadInstructions(Instructions, NumInstructions);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success! Opening file called: %s\n", FileName);
    }

    // Get number of lines in file
    char NewLineIdentifier;
    int LineCount = 0;
    while ((NewLineIdentifier = (char)fgetc(fptr)) != EOF)
    {
        if (NewLineIdentifier == '\n')
        {
            printf("%c", NewLineIdentifier);
            LineCount++;
            /*  Note that the true number of lines in file will be 1 more as there is no \n at end of file.
                First line is determining whether to draw grid so useful lines are true linecount-1.
                Therefore useful number of lines = LineCount */
        }
    }
    rewind(fptr);

    *NumInstructions = LineCount;

    fscanf(fptr, "%*s %d", &Instructions->DrawGridValue); // Read value of Draw_Grid (0 or 1) and store it

    Instructions->ShapestoDraw = malloc(sizeof(*Instructions->ShapestoDraw) * (long long unsigned)LineCount); // Acts as array of size LineCount
    if (Instructions->ShapestoDraw == NULL)
    {
        printf("Failed to allocate space for Instructions->ShapestoDraw\n");
        exit(EXIT_FAILURE);
    }

    // Read and store data to draw line by line
    int i;
    for (i = 0; i < *NumInstructions; i++)
    {
        fscanf(fptr, "%d %d %s", &Instructions->ShapestoDraw[i].ShapeGridPosition_x, &Instructions->ShapestoDraw[i].ShapeGridPosition_y, Instructions->ShapestoDraw[i].InstructionsShapeName);
    }

    fclose(fptr);
    return (EXIT_SUCCESS);
}

int ConverttoGCode(char *buffer, struct InstructionData *Instructions, struct ShapeData *Shape, int *Numshapes, int *NumInstructions)
{
    if (Instructions->DrawGridValue == 1)
    {
        printf("Drawing Grid\n");
        CreateGrid(buffer);
    }

    float StartPos_x = 0;
    float StartPos_y = 0;
    float TempPos_x = 0;
    float TempPos_y = 0;

    int i, j, k;

    for (i = 0; i < *NumInstructions; i++) // Loop through instructions
    {
        for (j = 0; j < *Numshapes; j++) // Loop through shapes
        {
            if (!strcmp(Instructions->ShapestoDraw[i].InstructionsShapeName, Shape[j].ShapeName)) // strcmp returns 0 if strings are equal
            {
                printf("Drawing %s\n",Shape[j].ShapeName);

                // Origin is top left while gridposition 1,1 is bottom left
                StartPos_x = (((float)Instructions->ShapestoDraw[i].ShapeGridPosition_x - 1) * GridSpacing) + GridStartPositionOffset;  // Formula for distance to grid position. Eg for grid 2: distance = (2-1)*30 + 5 = 35
                StartPos_y = (-(4 - (float)Instructions->ShapestoDraw[i].ShapeGridPosition_y) * GridSpacing) + GridStartPositionOffset; // Formula for distance to grid position. Eg for grid 2: distance = -(4-2)*30 + 5 = -55

                sprintf(buffer, "S0\n");
                SendCommands(buffer);
                sprintf(buffer, "G0 X%f Y%f\n", StartPos_x, StartPos_y);
                SendCommands(buffer);

                for (k = 0; k < Shape[j].NumberLinesOfShape; k++) // Loop through lines of data in each shape (X,Y,PenStatus lines)
                {
                    TempPos_x = StartPos_x + Shape[j].ShapePositionData[k].xPosition;
                    TempPos_y = StartPos_y + Shape[j].ShapePositionData[k].yPosition;

                    // Checks if the penstatus changes. Change spindle speed to represent new value.
                    if (k == 0 || (Shape[j].ShapePositionData[k].PenStatus != Shape[j].ShapePositionData[k - 1].PenStatus)) // 'k == 0 ||' statement to assign initial spindle speed
                    {
                        if (Shape[j].ShapePositionData[k].PenStatus == 0)
                        {
                            sprintf(buffer, "S0\n");
                        }
                        else
                        {
                            sprintf(buffer, "S1000\n");
                        }
                        SendCommands(buffer);
                    }

                    sprintf(buffer, "G%d X%f Y%f\n", Shape[j].ShapePositionData[k].PenStatus, TempPos_x, TempPos_y);
                    SendCommands(buffer);
                }             
                break;  // ends j for loop so it doesnt look through rest of shapes (has already found the shape)
            }
            else if (j == *Numshapes - 1) // Check if j is the last possible value
            {
                printf("Shape '%s' not found in 'ShapeStrokeData.txt'\n", Instructions->ShapestoDraw[i].InstructionsShapeName);
            }
        }
    }

    // Return to start
    sprintf(buffer, "S0\n");
    SendCommands(buffer);
    sprintf(buffer, "G0 X0 Y0\n");
    SendCommands(buffer);
    sleep(2000);

    return (EXIT_SUCCESS);
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
    return (EXIT_SUCCESS);
}
