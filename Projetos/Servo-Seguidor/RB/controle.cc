#include <wiringPiSPI.h>
#include <iostream>
#include <unistd.h>
#include "Ads1115c.h"
#include "LibCtrEqDiff.h"

#define ADC_CHANNEL ADC_MUX_AIN0_GND

using namespace std;

static const int SPI_CHANNEL = 0;

void spi_error(void)
{
    cout << "SPI error";
    return -1;
}

const uint8_t ADC_BITS_RESOLUTION   = 15;
const double SENSOR_GAIN            = 0.1;
const double MIN_SENSOR_INPUT       = 0.2;
const double MAX_SENSOR_INPUT       = 2.0;
const uintMAX_t PWM_MAX_VALUE       = 360;
const double CTR_MAX_OUTPUT         = 100.0;
const double CTR_MIN_OUTPUT         = 0.0;
const double CTR_K                  = 1.5;
const double CTR_TAU                = 1000*micro_const;
const double FREQ_SAMPLING          = 10.0;

int main(void)
{
    cout << "\nInitializing Servo Controller" << endl ;

    int fd;
    unsigned char buffer[100];

    fd = wiringPiSPISetup(SPI_CHANNEL, 500000);
    if(fd < 0)
    {
        spi_error();
    }

    Ads1115c_t adc;

    ADC2Ctr adc2Ctr;
    Ctr2PWM ctr2PWM;
    CtrPI ctrPI;

    createADC2CtrHandler(&adc2Ctr, ADC_BITS_RESOLUTION, SENSOR_GAIN, MIN_SENSOR_INPUT, MAX_SENSOR_INPUT);
    createCtr2PWMHandler(&ctr2PWM, PWM_MAX_VALUE, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);
    createPIHandler(&ctrPI, &adc2Ctr, &ctr2PWM, CTR_K, CTR_TAU, FREQ_SAMPLING, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);

    while(true)
    {
        buffer[0] = runPIfromADC2PWM(&ctrPI, 5.0, adc.getAvgValue(ADC_CHANNEL)) - 180;
        fd = wiringPiSPIDataRW(SPI_CHANNEL, buffer, 1);
        if(fd < 0)
        {
            spi_error();
        }

        usleep(5*1000);
    }

    return 0;
}
