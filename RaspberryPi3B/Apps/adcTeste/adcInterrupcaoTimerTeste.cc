#include <iostream>

#include "TimerInterruptHandler.h"
#include "Ads1115c.h"

using namespace std;

Ads1115c_t adc;
volatile float adcValue;
volatile bool adcFlag;

int main(int argc, char *argv[])
{
//	const char * timesStr = argv[1];
//	int times = stoi(argv[1]);

	cout << "\n ADC INTERRUPT TEST" << endl;
	
	adc.set2ReadADC(ADC_MUX_AIN0_GND);
	adcFlag = false;
	setInterruptPeriod(200000);

	while(1) 
	{
		if(adcFlag)
		{
			adcFlag = false;			
			cout << "Channel read: " << adcValue << "V \n";	
		}	
	}

	return 0;
}

void interrupt(void)
{
	adcFlag = true;
	adcValue = adc.readVoltage();
}

