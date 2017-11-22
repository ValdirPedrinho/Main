#include "Ads1115c.h"

#define TEST_CHANNEL ADC_MUX_AIN0_GND

int main(int argc, char ** argv)
{
	const char * timesStr = argv[1];
	int times = stoi(argv[1]);

	cout << "\n ADC TEMPERATURE AND PRESSURE TEST" << endl;

	Ads1115c_t adc;	

	cout << "\n ADC TEST" << endl;

	for(int i = 0; i < times; i++)
	{
		usleep(50000);

		cout << "Iteracao = " << i + 1 << endl;

		cout << "Channel avgValue: " << adc.getAvgValue(TEST_CHANNEL) << "\n";
		cout << "Channel read: " << adc.readVoltage(TEST_CHANNEL) << "V \n";
	}

	return 0;
}
