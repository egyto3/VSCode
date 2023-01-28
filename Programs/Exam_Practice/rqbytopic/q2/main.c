#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculate_real_and_imaginary(float voltage_input, float phase_angle, float *voltage_real, float *voltage_imaginary);

int main()
{
    float voltage_input = 0;
    float phase_angle = 0;
    float voltage_real = 0;
    float voltage_imaginary = 0;
    printf("Voltage:\n");
    scanf("%f", &voltage_input);
    printf("Phase angle:\n");
    scanf("%f", &phase_angle);
    calculate_real_and_imaginary(voltage_input, phase_angle, &voltage_real, &voltage_imaginary);
    printf("vreal = %.2f\nvimaginary = %.2f\n", voltage_real, voltage_imaginary);

    return (EXIT_SUCCESS);
}

int calculate_real_and_imaginary(float voltage_input, float phase_angle, float *voltage_real, float *voltage_imaginary)
{
    *voltage_real = voltage_input * cosf(phase_angle);
    *voltage_imaginary = voltage_input * sinf(phase_angle);
    return (EXIT_SUCCESS);
}