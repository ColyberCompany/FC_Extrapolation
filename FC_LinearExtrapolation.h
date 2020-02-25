// FC_LinearExtrapolation.h
/*
	Name:       FC_LinearExtrapolation_example.ino
	Created:	17/02/2020 22:35:13
	Author:     Jan Wielgus
*/

#ifndef _FC_LINEAREXTRAPOLATION_h
#define _FC_LINEAREXTRAPOLATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FC_Extrapolation.h>


class FC_LinearExtrapolation : public FC_Extrapolation
{
private:
	enum Age { Newer = 0, Older = 1 };

	struct
	{
		float a;
		float b;
	} linearFactors; // linear function factors

public:
	FC_LinearExtrapolation();
	virtual void addNewMeasuredValue(float newValue); // add the new value and save current time for it
	virtual void addNewMeasuredValue(float newValue, uint32_t time); // add the new value for a given time
	virtual float getCurrentEstimation(); // return estimated value for current time based on the last two measurement values
	virtual float getEstimation(uint32_t time); // return extimation for a specific time stamp
	virtual float getLastEstimation(); // return the same value as last execution of getCurrentEstimation() method
	virtual void reset();

private:
	void calculateNewLinearFactors();


private:
	dataPair dataArray[2]; // array of two last measured values (at 0 is the newest)
};



#endif

