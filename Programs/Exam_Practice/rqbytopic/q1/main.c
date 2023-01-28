#include <stdio.h>
#include <stdlib.h>

int main()
{
    float voltage = 0;
    float current = 0;
    float resistance1 = 0;
    float resistance2 = 0;

    printf("Current = \n");
    scanf("%f", &current);
    printf("Resistance1 = \n");
    scanf("%f", &resistance1);
    printf("Resistance2 = \n");
    scanf("%f", &resistance2);

    voltage = current * (resistance1 + resistance2);
    printf("%f",voltage);
    return (EXIT_SUCCESS);
}