#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int main()
{

float radius = 2;
float volume = 0;
float surface_area = 0;

volume = (4*M_PI*radius*radius*radius)/3;
surface_area = 4*M_PI*radius*radius;

printf("The volume is %.2f \nThe surface area is %.2f", volume, surface_area);

return 0;

}