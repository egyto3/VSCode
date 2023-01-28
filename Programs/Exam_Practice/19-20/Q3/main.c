#include <stdio.h>
#include <stdlib.h>

int ConvertTime(int timeinSeconds, int *timeinHours, int *timeinMinutes, int *remainderTimeinSeconds);

int main()
{
    int timeinSeconds, timeinHours, timeinMinutes, remainderTimeinSeconds;
    printf("Enter a value for time in seconds: ");
    scanf("%d", &timeinSeconds);
    ConvertTime(timeinSeconds, &timeinHours, &timeinMinutes, &remainderTimeinSeconds);
    printf("Hours = %d\nMinutes = %d\nSeconds = %d\n",timeinHours,timeinMinutes,remainderTimeinSeconds);
    return (EXIT_SUCCESS);
}

int ConvertTime(int timeinSeconds, int *timeinHours, int *timeinMinutes, int *remainderTimeinSeconds)
{
    *timeinHours = timeinSeconds / 3600;
    *timeinMinutes = (timeinSeconds - (*timeinHours * 3600)) / 60;
    *remainderTimeinSeconds = timeinSeconds - ((*timeinHours * 3600) + (*timeinMinutes * 60));
    return (EXIT_SUCCESS);
}