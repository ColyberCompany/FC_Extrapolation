/*
    Name:       FC_LinearExtrapolation_example.ino
    Created:	17/02/2020 22:35:13
    Author:     Jan Wielgus
*/

#include <FC_Extrapolation.h>
#include <FC_LinearExtrapolation.h>

// FC_Extrapolation is a abstract class that can contain different extrapolation methods
FC_Extrapolation& extrapolator = FC_LinearExtrapolation();


int temp = 3;


void setup()
{
    Serial.begin(115200);
    //Serial.println("Program has just started");
}

void loop()
{
    uint16_t measurement = analogRead(A0);

    // Add new measurement 
    if (temp >= 3)
    {
        extrapolator.addNewMeasuredValue(measurement);
        temp = 1;
    }
    else
        temp++;
    

    Serial.print("MeasuredValue:");
    Serial.print(measurement);
    Serial.print(" Estimation:");
    Serial.println(extrapolator.getCurrentEstimation());


    delay(20);
}
