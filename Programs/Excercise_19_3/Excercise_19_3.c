#include <stdio.h>
#include <stdlib.h>

struct data
{
    int age;
    char forename[30];
    char surname[50];
    int year_of_birth;
};

int PrintData(struct data *struct1)
{

    printf("Age: %d\nName: %s %s\nyear of birth: %d\n", struct1->age, &struct1->forename[0], &struct1->surname[0],struct1->year_of_birth);
    return(0);
}

int main(void)
{
    struct data struct1;
    char c;

    FILE *fptr;

    printf("Press 'e' to enter data or 'r' to read data\n");
    c = getchar();
    if (c=='e')
    {
        fptr = fopen ("strdata.dat","wb");
        if ( fptr == NULL )
        {
         printf ("\nError creating file - aborting ");
         exit (0);
        }
        fptr = fopen ("strdata.dat","wb");
        printf("Please enter your age:\n");
        scanf("%d", &struct1.age);
        //fwrite(&struct1.age, sizeof(struct data), 1, fptr);
        printf("Please enter your forename:\n");
        scanf("%s", &struct1.forename[0]);
        //fwrite(&struct1.forename[0], sizeof(struct data), 1, fptr);
        printf("Please enter your surname:\n");
        scanf("%s", &struct1.surname[0]);
        //fwrite(&struct1.surname[0], sizeof(struct data), 1, fptr);
        printf("Please enter your year of birth:\n");
        scanf("%d", &struct1.year_of_birth);
        //fwrite(&struct1.year_of_birth, sizeof(struct data), 1, fptr);

        fwrite(&struct1, sizeof(struct data), 1, fptr);

        fclose (fptr);
        PrintData(&struct1);
    }
    else if (c=='r')
    {
        fptr = fopen ("strdata.dat","rb");
        if ( fptr == NULL )
        {
         printf ("\nError opening input file - aborting ");
         exit (0);
        }
        
        fread(&struct1, sizeof(struct data), 1, fptr);

        fclose (fptr);
        PrintData(&struct1);
    }
    else
    {
        printf("Invalid Key\n");
    }

}


