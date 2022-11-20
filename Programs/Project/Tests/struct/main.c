#include <stdio.h>
#include <stdlib.h>

int getname();


struct person
{
    int age;
    float weight;
    char name[30];
};

int main()
{
    int i;


    struct person *ptr;
    //struct person temp;
    //ptr = &temp;

    getname(ptr);

    printf("Displaying Information:\n");
    i = 1;
    printf("Name: %s\tAge: %d\n", (ptr + i)->name, (ptr + i)->age);

    return 0;
}

int getname(struct person *ptr)
{
    int i;


    // allocating memory for n numbers of struct person
    //printf("Enter the number of persons: ");
   // scanf("%d", &n);
    //ptr = (struct person *)malloc(n * sizeof(struct person));


    for (i = 0; i < 3; ++i)
    {
        printf("Enter first name and age respectively: ");

        // To access members of 1st struct person,
        // ptr->name and ptr->age is used

        // To access members of 2nd struct person,
        // (ptr+1)->name and (ptr+1)->age is used
        scanf("%s %d", (ptr + i)->name, &(ptr + i)->age);
    }

    return 0;
}