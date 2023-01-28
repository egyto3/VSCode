#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculate_volume_and_surfacearea(float height, float radius, float *volume, float *surfacearea);

int main()
{
    float radius = 0;
    float height = 0;
    float volume = 0;
    float surfacearea = 0;

    printf("Enter a height: ");
    scanf("%f", &height);
    printf("Enter a radius: ");
    scanf("%f", &radius);
    if (!calculate_volume_and_surfacearea(height, radius, &volume, &surfacearea)) // Call function and check if volume or surface area is valid
    {
        printf("Volume = %.3f\n", volume);
        printf("Surface area = %.3f\n", surfacearea);
    }

    return (EXIT_SUCCESS);
}

int calculate_volume_and_surfacearea(float height, float radius, float *volume, float *surfacearea)
{
    *volume = M_PI * radius * radius * height / 3;
    *surfacearea = M_PI * radius * (radius + sqrt((radius * radius) + (height * height)));
    if (*volume < 0)
    {
        printf("Invalid value for volume\n");
        return (-1);
    }
    if (*surfacearea < 0)
    {
        printf("Invalid value for surface area\n");
        return (-1);
    }

    return (0);
}