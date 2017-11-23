#include "Ads1115c.h"

Ads1115cChannel::Ads1115cChannel(void)
: regGain(ADC_FS_6V144), avgValue(0), errorReg(ADC_CHANNEL_IS_FINE)
{}

Ads1115c::Ads1115c(int address, ADC_TYPE_t adcType)
: i2c_address(address)
{
	i2cStart();

	config();

	if(adcType == ADC_4to20mA) {
		for(int i = 0; i <  8; i++) {	
			channels[i].regGain = ADC_FS_2V048;		
		}
	}
}


Ads1115c::~Ads1115c(void)
{
	// power down ASD1115
	writeBuf[0] = 0x1;    		// config register is 1
	writeBuf[1] = 0x63;		 	// bit 15-8 0xC3 single shot on
	writeBuf[2] = 0x85;		 	// bits 7-0  0x85
	if(write(i2c_fd, writeBuf, 3) < 0) {
		cout << "Error: Couldn't write to register select and/or read/writer register of ADC" << endl;
		errorReg = ADC_I2C_COULDNT_WRITE;
		return;
	}

	i2cClose();
}

void Ads1115c::i2cStart(void)
{
	//cout << "ADC.start, adress: " << i2c_address << endl;
	// open device on /dev/i2c-1 the default on Raspberry Pi
	if((i2c_fd = open("/dev/i2c-1", O_RDWR)) < 0) {
		cout << "Error: Couldn't open ADC device!" << i2c_fd << endl;
		errorReg = ADC_I2C_COULDNT_OPEN;
		i2cClose();
		return;
	}

	// connect to ADS1115 as i2c slave
	if((ioctl(i2c_fd, I2C_SLAVE, i2c_address)) < 0) {
		cout << "Error: Couldn't find ADC device on address!" << endl;
		errorReg = ADC_I2C_COULDNT_CONNECT;
		i2cClose();
		return;
	}	

	readBuf[0] = 0x00;
	
	if(read(i2c_fd, readBuf, 2) < 0) {			
		cout << "ADC Error: Couldn't communicate" << endl;
		errorReg = ADC_I2C_COULDNT_READ;
		i2cClose();
		return;
	}
	
	errorReg = ADC_IS_FINE;
}

void Ads1115c::i2cClose(void)
{
	if(i2c_fd) { 				//If handle is open
		close(i2c_fd);
	}
	i2c_fd = 0;	
}

useconds_t Ads1115c::defineDelay(void) 
{
	switch(regDataSampleRate) {
		case ADC_DSR_8SPS:
			return useconds_t(1000*1000/1);
		case ADC_DSR_16SPS:
			return useconds_t(1000*1000/2);
		case ADC_DSR_32SPS:
			return useconds_t(1000*1000/2);
		case ADC_DSR_64SPS:
			return useconds_t(1000*1000/4);
		case ADC_DSR_128SPS:
			return useconds_t(1000*1000/9);
		case ADC_DSR_250SPS:
			return useconds_t(1000*1000/14);
		case ADC_DSR_475SPS:
			return useconds_t(1000*1000/19);
		case ADC_DSR_860SPS:
			return useconds_t(1000*1000/24);
		default:
			return useconds_t(1000*1000*5);
	}
}

uint8_t Ads1115c::defineSamples(void)
{
	switch(regDataSampleRate) {
		case ADC_DSR_8SPS: // 8Hz
			return 1;
		case ADC_DSR_16SPS: // 5Hz
			return 3;
		case ADC_DSR_32SPS: // 10Hz
			return 3;
		case ADC_DSR_64SPS: // 12Hz
			return 5;
		case ADC_DSR_128SPS: // 12Hz
			return 10;
		case ADC_DSR_250SPS: // 16Hz
			return 15;
		case ADC_DSR_475SPS: // 20Hz
			return 20;
		case ADC_DSR_860SPS: // 30Hz
			return 25;
		default:
			return 0;
	}
}

void Ads1115c::config (ADC_OS_e os, ADC_MODE_e mode, ADC_DSR_e sampleRate, ADC_COMP_MODE_e compMode, ADC_COMP_POL_e compPol, ADC_COMP_LAT_e compLat, ADC_COMP_QUE_e compQueue)
{
	regOS = os;
	regMode = mode;
	regDataSampleRate = sampleRate;
	regComparatorMode = compMode;
	regComparatorPolarity = compPol;
	regLatchingComparator = compLat;
	regComparatorQueue = compQueue;
	for(int i = 0; i < 8; i++) {
		channels[i].regGain = ADC_FS_6V144;
		channels[i].avgValue = 0;
		channels[i].sum = 0;
	}
}

void Ads1115c::setGain(ADC_MUX_e channel, ADC_FS_e gain)
{
	channels[int(channel)].regGain = gain;
}

float Ads1115c::getGainValue(ADC_MUX_e channel)
{
	switch(channels[int (channel)].regGain) {
		case ADC_FS_6V144:
			return float (6.144);
		case ADC_FS_4V096:
			return float (4.096);
		case ADC_FS_2V048:
			return float (2.048);
		case ADC_FS_1V024:
			return float (1.024);
		case ADC_FS_0V512:
			return float (0.512);
		case ADC_FS_0V256:
			return float (0.256);
		default:
			return float (ADC_INVALID_VALUE);
	}	
}

int16_t Ads1115c::getAvgValue(ADC_MUX_e channel) {
	return channels[int (channel)].avgValue;
}

ADC_ERROR_t Ads1115c::getError(void) {
	return errorReg;
}

ADC_CHANNEL_ERROR_t  Ads1115c::getChannelError(ADC_MUX_e channel) {
	return channels[int (channel)].errorReg;
}

void Ads1115c::readADC(ADC_MUX_e channel) 
{
	adcMutex.lock();	
	
	// try connect
	if(errorReg != ADC_IS_FINE) {
		i2cStart();
	}
	
	// abort
	if(errorReg != ADC_IS_FINE) {		
		channels[int (channel)].avgValue = uint16_t (ADC_INVALID_VALUE);
		adcMutex.unlock();
		return;
	}	
	
	writeBuf[0] = 1; // config to access write register

	uint8_t samples = defineSamples();	
																			// read/write register bit
	writeBuf[1] = regOS;													// Bit[15]
	writeBuf[1] = (writeBuf[1] << 3) | int (channel);						// Bit[14:12]
	writeBuf[1] = (writeBuf[1] << 3) | channels[int (channel)].regGain;		// Bit[11:9]
	writeBuf[1] = (writeBuf[1] << 1) | regMode;								// Bit[8]

	writeBuf[2] = regDataSampleRate;										// Bit[7:5]
	writeBuf[2] = (writeBuf[2] << 1) | regComparatorMode;					// Bit[4]
	writeBuf[2] = (writeBuf[2] << 1) | regComparatorPolarity;				// Bit[3]
	writeBuf[2] = (writeBuf[2] << 1) | regLatchingComparator;				// Bit[2]
	writeBuf[2] = (writeBuf[2] << 2) | regComparatorQueue;					// Bit[1:0]

	// begin conversion
	if(write(i2c_fd, writeBuf, 3) < 0) {
		cout << "Error in First if: Couldn't write to register select and/or read/writer register of ADC" << endl;
		errorReg = ADC_I2C_COULDNT_WRITE;
		i2cClose();
		adcMutex.unlock();
		return;
	}

	useconds_t delay = defineDelay();

	usleep(2*delay);

	// config to access read register
	readBuf[0] = 0;
	if(write(i2c_fd, readBuf, 1) < 0) {
		cout << "Error in Second if: Couldn't write register select of ADC" << endl;
		errorReg = ADC_I2C_COULDNT_WRITE;
		i2cClose();
		adcMutex.unlock();
		return;
	}

	channels[int (channel)].sum = 0;			

	for(int j = 0; j < samples; j++) 
	{
		// read conversion register
		if(read(i2c_fd, readBuf, 2) < 0) {		
			cout << "Error in Third if: Couldn't read ADC conversion" << endl;
			errorReg = ADC_I2C_COULDNT_READ;
			i2cClose();
			adcMutex.unlock();
			return;
		}

		// to remove noise
//		readBuf[1] = readBuf[1] >> 2;
//		readBuf[1] = readBuf[1] << 2;

		channels[int (channel)].samplesArray[j] = int16_t (readBuf[0] << 8 | readBuf[1]);
		channels[int (channel)].sum += int32_t (channels[int (channel)].samplesArray[j]);

		usleep(delay);		

	} // end for

	channels[int (channel)].errorReg = ADC_CHANNEL_IS_FINE;

	channels[int (channel)].avgValue = int16_t (channels[int (channel)].sum/samples);
	int32_t sumAux = 0;

	for(int j = 0; j < samples; j++) {		
		channels[int (channel)].samplesArray[j] -= channels[int (channel)].avgValue;
		channels[int (channel)].samplesArray[j] = (channels[int (channel)].samplesArray[j])*(channels[int (channel)].samplesArray[j]);
		sumAux += channels[int (channel)].samplesArray[j];
	}

	float stdDeviation = sqrt(sumAux/(samples-1));

	if(channels[int (channel)].avgValue < int16_t (UNDER_ZERO_LIMIT)) {
		channels[int (channel)].avgValue = uint16_t (ADC_INVALID_VALUE);
		channels[int (channel)].errorReg = ADC_CHANNEL_UNDER_ZERO;
	}
	else if(channels[int (channel)].avgValue < 0) {
		channels[int (channel)].avgValue = 0;
	}
	
	if(stdDeviation >= MAX_STD_DEVIATION) {
		channels[int (channel)].avgValue = uint16_t (ADC_INVALID_VALUE);
		channels[int (channel)].errorReg = ADC_CHANNEL_OVER_MAX_STD_DEVIATION;
	}
	
	channels[int (channel)].errorReg = ADC_CHANNEL_IS_FINE;
	
	adcMutex.unlock();	
}

float Ads1115c::readVoltage(ADC_MUX_e channel)
{
	readADC(channel);

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		cout << "readVoltage error" << endl;
		return float (ADC_INVALID_VALUE);
	}

	return float (channels[int (channel)].avgValue * ((getGainValue(channel))/32768.0));
}

float Ads1115c::readVoltageSensor(ADC_MUX_e channel, float minVoltage, float minValue, float maxVoltage, float maxValue, float offset)
{
	float voltage = readVoltage(channel);

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}
	float deltaValue = maxValue - minValue;
	float deltaVoltage = maxVoltage - minVoltage;
	float alpha = float (deltaValue/deltaVoltage);
	return float (alpha*(voltage - minVoltage) + minValue + offset);
}

float Ads1115c::read4to20mASignalConvertedToVotage(ADC_MUX_e channel, float resistor) 
{
	readADC(channel);

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);	
	}

	float current = float (channels[int (channel)].avgValue * ((getGainValue(channel))/32768.0) * (1000.0 / resistor));

	if(current <= MIN_CURRENT_4to20mA) {
		if(channels[int (channel)].errorReg != ADC_CHANNEL_UNDER_ZERO) {
			channels[int (channel)].errorReg = ADC_CHANNEL_UNDER_MIN_LIMIT; 
		}		
		return float (ADC_INVALID_VALUE);
	}

	if(current >= MAX_CURRENT_4to20mA) {
		channels[int (channel)].errorReg = ADC_CHANNEL_OVER_MAX_LIMIT;
		return float (ADC_INVALID_VALUE);
	}
	
	return current;
}

float Ads1115c::read4to20mASensor(ADC_MUX_e channel, float resistor, float minValue, float maxValue, float offset)
{
	float current = read4to20mASignalConvertedToVotage(channel, resistor);

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}
	float delta = maxValue - minValue;
	float alpha = float (delta/16.0);
	return float (alpha*(current - 4.0) + minValue + offset);
}

float Ads1115c::readWheatstone(ADC_MUX_e reference, ADC_MUX_e channel, float resistors) 
{
	float e0 = readVoltage(channel);
	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}

	float vcc = readVoltage(reference);
	if((vcc <= 0) || (getChannelError(channel) != ADC_CHANNEL_IS_FINE)) {
		return float (ADC_INVALID_VALUE);
	}

	float epsilon = e0/(2*vcc);
	return float (resistors*(0.5+epsilon)/(0.5-epsilon));
}
