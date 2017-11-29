#include <wiringPiSPI.h>
#include <iostream>
#include <thread>

#include "TimerInterruptHandler.h"
#include "Ads1115c.h"
#include "LibCtrEqDiff.h"

#define ADC_CHANNEL ADC_MUX_AIN0_GND

using namespace std;

static const int SPI_CHANNEL = 0;

const double CTR_MAX_OUTPUT         = 180.0;
const double CTR_MIN_OUTPUT         = 0.0;
const double CTR_K                  = 0.5;
const double CTR_TAU                = 300*mili_const;
const double CTR_FREQ_SAMPLING  	= 5.0;

bool endConfigFlag			= false;
float sensorGain			= 0.0;
float initialVoltage		= 0.0;
float voltage 				= 0.0;
intMAX_t deltaPosition 		= 0.0;
unsigned char position[1];

CtrPI ctrPI;
Ads1115c_t adc;

void* readAdc2Config(void*);

int main(void)
{
    cout << "\nInitializing Servo Controller" << endl ;

	// =========================================================================
	// Configuração do ADC (860SPS)
	// =========================================================================

	adc.set2ReadADC(ADC_MUX_AIN0_GND);

	// =========================================================================
	// Configuração da posição inicial
	// =========================================================================

	position[0] = 90;

	// =========================================================================
	// Configuração do ganho do sensor
	// =========================================================================

	char confirmConfig = ' ';
	pthread_t readAdc2ConfigThread;
	int val = pthread_create(&readAdc2ConfigThread, NULL, &readAdc2Config, NULL);
	if(val) cout << "Error: can't create readAdc2ConfigThread" << endl;
	while(confirmConfig != 'i')
	{
		cin >> confirmConfig;
	}
	endConfigFlag = true;
	pthread_join(readAdc2ConfigThread, NULL);
	sensorGain = initialVoltage/10.0;
	cout << "Sensor Gain: " << sensorGain << endl;

	// =========================================================================
	// Inicializa o controlador
	// =========================================================================

	createPIHandler(&ctrPI, NULL, NULL, CTR_K, CTR_TAU, CTR_FREQ_SAMPLING, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);

	// =========================================================================
	// SPI Setup
	// =========================================================================
	
    int fd = wiringPiSPISetup(SPI_CHANNEL, 500000);
    if(fd < 0)
    {
	    cout << "SPI error";
	    return -1;
    }
	
	// =========================================================================
	// Configura a interrupção
	// =========================================================================

	setInterruptPeriod(200000);

	// =========================================================================
	// Loop Infinito
	// =========================================================================

	for(;;)
	{
		// toda a computação é feita no tratamento da interrupção
	}

    return 0;
}

void* readAdc2Config(void*)
{
	while(!endConfigFlag)
	{
		initialVoltage = adc.readVoltage();
		cout << "Tensao: " << initialVoltage << endl;
		usleep(500000);
	}
	return NULL;
}

void interrupt(void)
{
	voltage = adc.readVoltage();
	deltaPosition = _round((double) ((voltage-initialVoltage)/sensorGain));
	cout << "Tensao: " << voltage << "\t";
	cout << "Delta Position: " << deltaPosition << endl;
	double aux;
	aux = runPI(&ctrPI, (double) (position[0]-deltaPosition), (double) position[0]);
	position[0] = (unsigned char) _round(aux);
	int fd = wiringPiSPIDataRW(SPI_CHANNEL, position, 1);
    if(fd < 0)
    {
	    cout << "SPI error";
    }
}

/*

    int fd;
    unsigned char buffer[100];
	int pos = 90;


    
 	createPIHandler(&ctrPI, NULL, NULL, CTR_K, CTR_TAU, CTR_FREQ_SAMPLING, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);


    ADC2Ctr adc2Ctr;
    Ctr2PWM ctr2PWM;
    CtrPI ctrPI;

    createADC2CtrHandler(&adc2Ctr, ADC_BITS_RESOLUTION, SENSOR_GAIN, MIN_SENSOR_INPUT, MAX_SENSOR_INPUT);
    createCtr2PWMHandler(&ctr2PWM, PWM_MAX_VALUE, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);
    createPIHandler(&ctrPI, &adc2Ctr, &ctr2PWM, CTR_K, CTR_TAU, FREQ_SAMPLING, CTR_MIN_OUTPUT, CTR_MAX_OUTPUT);

    while(true)
    {

        buffer[0] = runPIfromADC2PWM(&ctrPI, 5.0, (uintMAX_t) adc.getAvgValue(ADC_CHANNEL));

		float value = adc.readVoltage(ADC_CHANNEL);
		for(int i=0; i<5; i++) {
			if( value < 1.0) {
				pos+=1;
			}
			if( value > 1.0) {
				pos-=1;
			}
			if(pos > 200) {pos = 200;}
			if(pos < 20) {pos = 20;}
			cout << value << endl;
		}
		buffer[0] = pos + 20;
        fd = wiringPiSPIDataRW(SPI_CHANNEL, buffer, 1);
        if(fd < 0)
        {
	   	 	cout << "SPI error";
	    	return -1;
        }

    }
*/

