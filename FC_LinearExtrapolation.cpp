// 
// 
// 
/*
    Name:       FC_LinearExtrapolation_example.ino
    Created:	17/02/2020 22:35:13
    Author:     Jan Wielgus
*/


#include <FC_LinearExtrapolation.h>


FC_LinearExtrapolation::FC_LinearExtrapolation()
{
    reset();
}


void FC_LinearExtrapolation::addNewMeasuredValue(float newValue)
{
    addNewMeasuredValue(newValue, (uint32_t)micros());
}


void FC_LinearExtrapolation::addNewMeasuredValue(float newValue, uint32_t time)
{
    // Always choose two newest values


    // Older than the newest
    if (time < dataArray[Newer].time)
    {
        // Newest remain unchanged
        // Oldest changes
        dataArray[Older].measurement = newValue;
        dataArray[Older].time = time;
    }

    // The same time as the newest
    else if (time == dataArray[Newer].time)
    {
        dataArray[Newer].measurement = newValue;
        dataArray[Newer].time = time;
    }

    // Newer than the newest
    else
    {
        dataArray[Older] = dataArray[Newer];

        dataArray[Newer].time = time;
        dataArray[Newer].measurement = newValue;
    }


    calculateNewLinearFactors();
}


float FC_LinearExtrapolation::getCurrentEstimation()
{
    // f(t) = a*t + b
    lastEstimationValue = (linearFactors.a * micros()) + linearFactors.b;
    return lastEstimationValue;
}


float FC_LinearExtrapolation::getEstimation(uint32_t time)
{
    // f(t) = a*t + b
    lastEstimationValue = (linearFactors.a * time) + linearFactors.b;
    return lastEstimationValue;
}


float FC_LinearExtrapolation::getLastEstimation()
{
    return lastEstimationValue;
}


void FC_LinearExtrapolation::reset()
{
    for (int i = 0; i < 2; i++)
    {
        dataArray[i].measurement = 1;
        dataArray[i].time = micros() + (i-1) * 1000000;
    }

    calculateNewLinearFactors();
}


void FC_LinearExtrapolation::calculateNewLinearFactors()
{
    // a = (yb - ya) / (xb - xa)
    linearFactors.a = (dataArray[Newer].measurement - dataArray[Older].measurement) / (dataArray[Newer].time - dataArray[Older].time);

    // b = f(t) - a*t
    linearFactors.b = dataArray[Newer].measurement - (linearFactors.a * dataArray[Newer].time);
}




