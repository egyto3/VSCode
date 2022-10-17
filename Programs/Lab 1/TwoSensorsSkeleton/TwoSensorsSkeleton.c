#include <stdio.h>
#include <math.h>

float NISTdegCtoMilliVoltsKtype(float tempDegC)
/* returns EMF in millivolts */
{
    int i;
    float milliVolts = 0;
    if(tempDegC >= -170 && tempDegC < 0)
    {
        const float coeffs[11] =
        {
            0.000000000000E+00,
            0.394501280250E-01,
            0.236223735980E-04,
            -0.328589067840E-06,
            -0.499048287770E-08,
            -0.675090591730E-10,
            -0.574103274280E-12,
            -0.310888728940E-14,
            -0.104516093650E-16,
            -0.198892668780E-19,
            -0.163226974860E-22
        };
        for (i=0; i<=10; i++)
        {
            milliVolts += coeffs[i] * pow(tempDegC,i);
        }
    }
    else if(tempDegC >= 0 && tempDegC <= 1372)
    {
        const float coeffs[10] =
        {
            -0.176004136860E-01,
            0.389212049750E-01,
            0.185587700320E-04,
            -0.994575928740E-07,
            0.318409457190E-09,
            -0.560728448890E-12,
            0.560750590590E-15,
            -0.320207200030E-18,
            0.971511471520E-22,
            -0.121047212750E-25
        };
        const float a0 =  0.118597600000E+00;
        const float a1 = -0.118343200000E-03;
        const float a2 =  0.126968600000E+03;

        for (i=0; i<=9; i++)
        {
            milliVolts += coeffs[i] * pow(tempDegC,i);
        }

        milliVolts += a0*exp(a1*(tempDegC - a2)*(tempDegC - a2));
    }
    else
    {
        milliVolts = 99E99;
    }
    return milliVolts;
}

float NISTmilliVoltsToDegCKtype(float tcEMFmV)
// returns temperature in deg C.
{

        int i, j;
        float tempDegC = 0;
        const float coeffs[11][3] =
        {
          {0.0000000E+00,  0.000000E+00, -1.318058E+02},
         {2.5173462E+01,  2.508355E+01,  4.830222E+01},
         {-1.1662878E+00,  7.860106E-02, -1.646031E+00},
         {-1.0833638E+00, -2.503131E-01,  5.464731E-02},
         {-8.9773540E-01,  8.315270E-02, -9.650715E-04},
         {-3.7342377E-01, -1.228034E-02,  8.802193E-06},
         {-8.6632643E-02,  9.804036E-04, -3.110810E-08},
         {-1.0450598E-02, -4.413030E-05,  0.000000E+00},
         {-5.1920577E-04,  1.057734E-06,  0.000000E+00},
         {0.0000000E+00, -1.052755E-08,  0.000000E+00}
       };
       if(tcEMFmV >=-5.891 && tcEMFmV <=0 )
       {
           j=0;
       }
       else if (tcEMFmV > 0 && tcEMFmV <=20.644  )
       {
           j=1;
       }
       else if (tcEMFmV > 20.644 && tcEMFmV <=54.886  )
       {
           j=2;
       }
       else
       {
           return 99E9;
       }

       for (i=0; i<=9; i++)
        {
            tempDegC += coeffs[i][j] * pow(tcEMFmV,i);
        }
    return tempDegC;
}

/* Write a function here to convert ADC value to voltages. (Part a, equation 1)
Call it from the main() function below */

float ADCToVoltage(float V_ref, float n_ADC)
{       

        float V_ADC = 0;
        V_ADC =  V_ref * n_ADC / 1024;
        return V_ADC;

}

/* Write a function to convert degrees K to degrees C  (Part b, (iv))
Call it from the main() function below */

float KelvinToCelcius(float Temp_K)
{
    float Temp_C = 0;
    Temp_C = Temp_K - 273;
    return (Temp_C);
}

int main()
{
    // Define VRef
    float V_ref = 5;

    // Define Thermistor constants
    double T0 = 298.15;
    double R0 = 10000;
    double B = 3975;

    // User input for one pin value to test all outputs
    float n_ADC = 256;

    // Calculate thermistor temperature in degrees C ( Part b, i,ii,iii & v)

        // Call function to convert ADC value to voltage
        float V_ADC = 0;
        V_ADC = ADCToVoltage(V_ref, n_ADC);

        // Convert voltage to resistance (in ohms)
        double ThermisterResistance = 0;
        ThermisterResistance = (((10 * 3.3) / (double)V_ADC) - 10) * 1000;

        // Convert resistance into temperature (in K)
        double Temperature_Kelvin = 0;
        double Resistance_Logarithm = 0;
        Resistance_Logarithm = log(ThermisterResistance / R0);
        Temperature_Kelvin = pow(((1/T0)+((1/B)*Resistance_Logarithm))), -1);
        // Temperature_Kelvin = pow(((1/T0)+((1/B)*(log(ThermisterResistance / R0)))), -1);

        // Convert temperature from Kelvin to Celcius
        double Temperature_Celcius = 0;
        Temperature_Celcius = KelvinToCelcius(Temperature_Kelvin);

    // Calculate thermocouple temperature in degrees C ( Part c, i - iv)

    // Output results
    printf("V_ADC = %f ThermisterResistance = %f \n", V_ADC, ThermisterResistance);
    printf("Thermistor temperature (deg C): %f \n", Temperature_Celcius);
    //printf("Thermocouple temperature with CJC (deg C): %f \n", ******);

    return 0;
}
