/* Test program for reading of thermistor, thermocouple and LVDT.
   K-type thermocouple functions written by Arthur Jones using 
   official NIST polynomial data from
   https://srdata.nist.gov/its90/download/type_k.tab */

#include <math.h> /* needed for exp() and pow() */

/* It is good practice to define things like pins used at the start
   so that you avoid hard-coded values (magic numbers) in code */
#define TCpin A0
#define ThermistorPin A1

/* Similarly, define any constant values e.g. Vref, B, R0 here to avoid
  need for "magic numbers" in code */

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  /* Put your code here to read ADCs and convert ADC voltages to 
  temperatures */

// Define VRef
    double V_ref = 5;

    // Define Thermistor constants
    double T0 = 298.15;
    double R0 = 10000;
    double B = 3975;

    // User input for one pin value to test all outputs
        double Thermistor_ADC = 0;
        Thermistor_ADC = analogRead(TCpin);
        double Thermocouple_ADC = 0;
        Thermocouple_ADC = analogRead(ThermistorPin);

        //Test values
        //Thermistor_ADC = 256;
        //Thermocouple_ADC = 256;


    // Calculate thermistor temperature in degrees C ( Part b, i,ii,iii & v)

        // Call function to convert ADC value to voltage
        double V_ADC = 0;
        V_ADC = ADCToVoltage(V_ref, Thermistor_ADC);

        // Convert voltage to resistance (in ohms)
        double ThermisterResistance = 0;
        ThermisterResistance = (((10 * 3.3) / V_ADC) - 10) * 1000;

        // Convert resistance into temperature (in K)
        double Temperature_Kelvin = 0;
        double Resistance_Logarithm = 0;
        double Temperature_Expression = 0;
        
        Resistance_Logarithm = log(ThermisterResistance / R0);
        Temperature_Expression = (1 / T0) + (Resistance_Logarithm / B);
        Temperature_Kelvin = pow(Temperature_Expression, -1);

             

        // Convert temperature from Kelvin to Celcius
        double Temperature_Celcius = 0;
        Temperature_Celcius = KelvinToCelcius(Temperature_Kelvin);

    // Calculate thermocouple temperature in degrees C ( Part c, i - iv)

        // Convert ADC value to voltage


        V_ADC = ADCToVoltage(V_ref, Thermocouple_ADC);

        // Convert voltage to thermocouple voltage
        double ThermocoupleVoltage = 0;
        ThermocoupleVoltage = (V_ADC - 0.35) / 54.4;

        // Calculate compensation EMF (in millivolts)
        double EMF_Comp = 0;
        EMF_Comp = NISTdegCtoMilliVoltsKtype(Temperature_Celcius);

        // Calculate temeperature of thermocouple
        double ThermocoupleTemperature = 0;
        double EMF_Total = 0;
        EMF_Total = ThermocoupleVoltage * 1000 + (EMF_Comp);
        ThermocoupleTemperature = NISTmilliVoltsToDegCKtype(EMF_Total);

  /* Display results.  Don't use printf or formatting etc., they don't work on the Arduino. Just use 
     the serial print statements given here, inserting your own code as needed */

  Serial.print("Thermistor temperature (deg C): ");
  Serial.println(Temperature_Celcius);  
  Serial.print(" Thermocouple temperature with CJC (deg C): ");
  Serial.println(ThermocoupleTemperature);  
  Serial.println("\n");
  delay(1000);
}

/* Write a function to convert ADC value to 
   voltage: put it here and use it in your code above*/

double ADCToVoltage(double V_ref, double Thermocouple_ADC)
{       

        double V_ADC = 0;
        V_ADC =  V_ref * Thermocouple_ADC / 1024;
        return V_ADC;

}

/* Write a function to convert degrees K to degrees C
Call it from the main() function above */

double KelvinToCelcius(double Temp_K)
{
    double Temp_C = 0;
    Temp_C = Temp_K - 273.15;
    return (Temp_C);
}


/* Under no circumstances change any of the following code, it is fine as it is */
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
        milliVolts = 99E9;
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
           return 99E99;
       }

       for (i=0; i<=9; i++)
        {
            tempDegC += coeffs[i][j] * pow(tcEMFmV,i);
        }
    return tempDegC;
}
