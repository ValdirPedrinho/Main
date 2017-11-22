#ifndef ADS1115C_H
#define ADS1115C_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>						
#include <unistd.h>
#include <linux/i2c-dev.h> 
#include <stdlib.h>	
#include <inttypes.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <cmath>
#include "Ads1115c_Registers.h"

using namespace std;

#define I2C_ADC_ADDR 					0x48
#define ADC_INVALID_VALUE 				0x7FFF
#define MIN_CURRENT_4to20mA 			3.5
#define MAX_CURRENT_4to20mA 			20.0
#define MAX_STD_DEVIATION 				1000
#define NUMBER_OF_SAMPLES 				75
#define UNDER_ZERO_LIMIT				-5

typedef class Ads1115cChannel Ads1115cChannel_t;
typedef class Ads1115c Ads1115c_t;

typedef enum ADC_TYPE
{
	ADC_0to5V,
	ADC_4to20mA
} ADC_TYPE_t;

typedef enum ADC_ERROR
{
	ADC_IS_FINE,
	ADC_I2C_COULDNT_CONNECT,
	ADC_I2C_COULDNT_OPEN,
	ADC_I2C_COULDNT_READ,
	ADC_I2C_COULDNT_WRITE
} ADC_ERROR_t;

typedef enum ADC_CHANNEL_ERROR
{
	ADC_CHANNEL_IS_FINE,
	ADC_CHANNEL_OVER_MAX_STD_DEVIATION,
	ADC_CHANNEL_UNDER_ZERO,
	ADC_CHANNEL_UNDER_MIN_LIMIT,
	ADC_CHANNEL_OVER_MAX_LIMIT	
} ADC_CHANNEL_ERROR_t;

class Ads1115cChannel
{
	public:

		Ads1115cChannel(void);

	public:

		ADC_FS_e regGain;
		int32_t sum;
		int16_t avgValue;
		int16_t samplesArray[NUMBER_OF_SAMPLES];
		ADC_CHANNEL_ERROR_t errorReg;
};

class Ads1115c
{
	public:

		Ads1115c(int address = I2C_ADC_ADDR, ADC_TYPE_t adcType = ADC_0to5V);

		~Ads1115c(void);

		void config (
															// read/write register bit
			ADC_OS_e os = ADC_OS_1,							// Bit[15]	1
															// Bit[14:12] MUX selection (channel)
															// Bit[11:9] PGA selection (gain)
			ADC_MODE_e mode = ADC_MODE_CONTINUOUS, 			// Bit[8]	0
			ADC_DSR_e sampleRate = ADC_DSR_860SPS, 			// Bit[7:5]	111
			ADC_COMP_MODE_e compMode = ADC_COMP_MODE_T,		// Bit[4]	0
			ADC_COMP_POL_e compPol = ADC_COMP_POL_L,		// Bit[3]	0
			ADC_COMP_LAT_e compLat = ADC_COMP_LAT_NL,		// Bit[2]	1 
			ADC_COMP_QUE_e compQueue = ADC_COMP_QUE_A_TWO	// Bit[1:0]	01		
		);

		void setGain(ADC_MUX_e channel, ADC_FS_e gain);
		
		float getGainValue(ADC_MUX_e channel);

		int16_t getAvgValue(ADC_MUX_e channel);
		
		ADC_ERROR_t getError(void);
		
		ADC_CHANNEL_ERROR_t getChannelError(ADC_MUX_e channel);	

		void readADC(ADC_MUX_e channel);

		float readVoltage(ADC_MUX_e channel);

		float readVoltageSensor(ADC_MUX_e channel, float minVoltage, float minValue, float maxVoltage, float maxValue, float offset);

		float read4to20mASignalConvertedToVotage(ADC_MUX_e channel, float resistor);		

		float read4to20mASensor(ADC_MUX_e channel, float resistor, float minValue, float maxValue, float offset);

		float readWheatstone(ADC_MUX_e reference, ADC_MUX_e channel, float resistors);

	private:

		void i2cStart(void);
		void i2cClose(void);
		useconds_t defineDelay(void);
		uint8_t defineSamples(void);

	private:

		int i2c_fd;
		int i2c_address;
		uint8_t writeBuf[3];
		uint8_t readBuf[2];
		float range;
		ADC_OS_e regOS;
		ADC_MODE_e regMode;
		ADC_DSR_e regDataSampleRate;
		ADC_COMP_MODE_e regComparatorMode;
		ADC_COMP_POL_e regComparatorPolarity;
		ADC_COMP_LAT_e regLatchingComparator;
		ADC_COMP_QUE_e regComparatorQueue;
		Ads1115cChannel_t channels[8];
		ADC_ERROR_t errorReg;
		std::mutex adcMutex;
};

#endif
