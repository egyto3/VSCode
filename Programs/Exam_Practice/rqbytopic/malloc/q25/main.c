#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array_size;
    int *array;
    printf("Enter array size: ");
    scanf("%d", &array_size);

    array = (int *)malloc(sizeof(int) * array_size);
    if (array == NULL)
    {
        return (EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < array_size; i++)
    {
        array[i] = i * i;
    }
    for (i = 0; i < array_size; i++)
    {
        printf("%d\n", array[i]);
    }

    free(array);

    return (EXIT_SUCCESS);
}