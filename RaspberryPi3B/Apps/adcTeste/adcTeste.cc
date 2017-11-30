#include "Ads1115c.h"

#define TEST_CHANNEL ADC_MUX_AIN0_GND

int main(int argc, char ** argv)
{
	const char * timesStr = argv[1];
	int times = stoi(argv[1]);

	cout << "\n ADC TEST" << endl;

	Ads1115c_t adc;
	adc.set2ReadADC(ADC_MUX_AIN0_GND);

	for(int i = 0; i < times; i++)
	{
		cout << "Iteracao = " << i + 1 << endl;
		cout << "Channel read: " << adc.readVoltage() << "V \n";
	}

	return 0;
}
