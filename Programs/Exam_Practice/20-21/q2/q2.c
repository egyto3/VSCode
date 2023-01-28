#include <stdio.h>
#include <stdlib.h>

struct persondata
{
    char Firstname[30];
    char Surname[30];
    float Mark;
};

int main()
{
    FILE *fptr;
    fptr = fopen("Results.txt", "r");
    if (fptr == NULL) // Error check
    {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    struct persondata person[30];
    int i = 0;
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %s %f", person[i].Firstname, person[i].Surname, &person[i].Mark); // Read line of data

        if (person[i].Mark >= 70)
        {
            printf("%s %s: First class degree\n", person[i].Firstname, person[i].Surname);
        }
        else if (person[i].Mark >= 60)
        {
            printf("%s %s: Upper Second class degree\n", person[i].Firstname, person[i].Surname);
        }
        else if (person[i].Mark >= 50)
        {
            printf("%s %s: Lower Second class degree\n", person[i].Firstname, person[i].Surname);
        }
        else if (person[i].Mark >= 40)
        {
            printf("%s %s: Third class degree\n", person[i].Firstname, person[i].Surname);
        }
        else if ((person[i].Mark < 40) && (person[i].Mark >= 0))
        {
            printf("%s %s: Fail\n", person[i].Firstname, person[i].Surname);
        }
        else
        {
            printf("%s %s: Invalid mark as it is more than 100\n", person[i].Firstname, person[i].Surname);
        }
        i++;
    }
    fclose(fptr);
    return (EXIT_SUCCESS);
}