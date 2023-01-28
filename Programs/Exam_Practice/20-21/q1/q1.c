#include <stdio.h>
#include <stdlib.h>

int main()
{
    int height = 0;
    printf("Enter the height: ");
    scanf("%d", &height);
    if ((height < 1) || (height > 10))
    {
        printf("Hight must be between 1 and 10");
    }
    int i, k;
    for (i = 0; i <= height; i++)
    {
        for (k = 0; k <= i; k++)
        {
            printf(" ");
        }
        printf("##########\n");
    }
    return (EXIT_SUCCESS);
}