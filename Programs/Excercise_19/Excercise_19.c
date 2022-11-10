#include <stdio.h>
#include <stdlib.h>

struct data
{
    int age;
    char forename[30];
    char surname[50];
};

int PrintData(struct data *struct1)
{

    printf("Age: %d\nName: %s %s\n", struct1->age, &struct1->forename[0], &struct1->surname[0]);
    return(0);
}

int main(void)
{
    struct data struct1;
 
    printf("Please enter your age:\n");
    scanf("%d", &struct1.age);
    printf("Please enter your forename:\n");
    scanf("%s", &struct1.forename[0]);
    printf("Please enter your surname:\n");
    scanf("%s", &struct1.surname[0]);
    PrintData(&struct1);

}


