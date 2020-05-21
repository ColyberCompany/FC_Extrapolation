// FC_Extrapolation.h
/*
    Name:       FC_LinearExtrapolation_example.ino
    Created:	18/02/2020
    Author:     Jan Wielgus
*/

#ifndef _FC_EXTRAPOLATION_h
#define _FC_EXTRAPOLATION_h

#include "arduino.h"



class FC_Extrapolation
{
protected:
	struct dataPair
	{
		float measurement; // measurement value
		uint32_t time; // time when the measurement was taken
	};


public:
	virtual ~FC_Extrapolation();
	virtual void addNewMeasuredValue(float newValue) = 0; // add the new value and save current time for it
	virtual void addNewMeasuredValue(float newValue, uint32_t time) = 0; // add the new value for a given time
	virtual float getCurrentEstimation() = 0; // return estimated value for current time based on the last two measurement values
	virtual float getEstimation(uint32_t time) = 0; // return extimation for a specific time stamp
	virtual float getLastEstimation() = 0; // return the same value as last execution of getCurrentEstimation() method
	virtual void reset() = 0;


protected:
	float lastEstimationValue = 0;
};



#endif

