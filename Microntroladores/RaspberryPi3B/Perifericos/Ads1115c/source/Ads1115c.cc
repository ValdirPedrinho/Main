#include "Ads1115c.h"

Ads1115cChannel::Ads1115cChannel(void)
: regGain(ADC_FS_6V144), avgValue(0), errorReg(ADC_CHANNEL_IS_FINE)
{}

Ads1115c::Ads1115c(int address, ADC_TYPE_t adcType)
: i2c_address(address)
{
	i2cStart();

	numSamples = 10;

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
			return useconds_t(1000*1000/7);
		case ADC_DSR_16SPS:
			return useconds_t(1000*1000/15);
		case ADC_DSR_32SPS:
			return useconds_t(1000*1000/30);
		case ADC_DSR_64SPS:
			return useconds_t(1000*1000/60);
		case ADC_DSR_128SPS:
			return useconds_t(1000*1000/125);
		case ADC_DSR_250SPS:
			return useconds_t(1000*1000/245);
		case ADC_DSR_475SPS:
			return useconds_t(1000*1000/470);
		case ADC_DSR_860SPS:
			return useconds_t(1000*1000/850);
		default:
			return useconds_t(1000*1000*5);
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

	settedChannel = ADC_MUX_INVALID;
}

void Ads1115c::setNumSamplesPerRead(uint8_t samples)
{
    numSamples = (samples > 100)? 100 : samples;
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

void Ads1115c::set2ReadADC(ADC_MUX_e channel)
{
	adcMutex.lock();

	settedChannel = channel;

	// try reconnect
	if(errorReg != ADC_IS_FINE) {
		i2cStart();
	}

	// abort
	if(errorReg != ADC_IS_FINE) {
		adcMutex.unlock();
		return;
	}

	writeBuf[0] = 1; // config to access write register
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

	if(write(i2c_fd, writeBuf, 3) < 0) {
		cout << "Error: Couldn't write to register select and/or read/writer register of ADC" << endl;
		errorReg = ADC_I2C_COULDNT_WRITE;
		i2cClose();
		adcMutex.unlock();
		return;
	}	

	usleep(useconds_t(50*1000));

	adcMutex.unlock();
}

void Ads1115c::readADC(void)
{
	adcMutex.lock();

	if(settedChannel == ADC_MUX_INVALID)
	{
		cout << "Error: No channel selected" << endl;
		return;
	}
	ADC_MUX_e channel = settedChannel;

	if(errorReg != ADC_IS_FINE) {
		set2ReadADC(channel);
	}

	channels[int (channel)].sum = 0;

	useconds_t delay = defineDelay();
	uint8_t samples = numSamples;

	for(int j = 0; j < samples; j++)
	{

		// config to access read register
		readBuf[0] = 0;
		if(write(i2c_fd, readBuf, 1) < 0) {
			cout << "Error: Couldn't write register select of ADC" << endl;
			errorReg = ADC_I2C_COULDNT_WRITE;
			i2cClose();
			adcMutex.unlock();
			return;
		}

		// read conversion register
		if(read(i2c_fd, readBuf, 2) < 0) {
			cout << "Error: Couldn't read ADC conversion" << endl;
			errorReg = ADC_I2C_COULDNT_READ;
			i2cClose();
			adcMutex.unlock();
			return;
		}

		channels[int (channel)].samplesArray[j] = int16_t (readBuf[0] << 8 | readBuf[1]);
		channels[int (channel)].sum += int32_t (channels[int (channel)].samplesArray[j]);

		usleep(delay);

	} // end for

	channels[int (channel)].errorReg = ADC_CHANNEL_IS_FINE;
	channels[int (channel)].avgValue = int16_t (channels[int (channel)].sum/samples);	

	// check if there are errors

	if(channels[int (channel)].avgValue < int16_t (UNDER_ZERO_LIMIT)) {
		channels[int (channel)].avgValue = uint16_t (ADC_INVALID_VALUE);
		channels[int (channel)].errorReg = ADC_CHANNEL_UNDER_ZERO;
	}
	else if(channels[int (channel)].avgValue < 0) {
		channels[int (channel)].avgValue = 0;
	}

	int32_t sumAux = 0;
	for(int j = 0; j < samples; j++) {
		channels[int (channel)].samplesArray[j] -= channels[int (channel)].avgValue;
		channels[int (channel)].samplesArray[j] = (channels[int (channel)].samplesArray[j])*(channels[int (channel)].samplesArray[j]);
		sumAux += channels[int (channel)].samplesArray[j];
	}

	float stdDeviation = sqrt(sumAux/(samples-1));

	if(stdDeviation >= MAX_STD_DEVIATION) {
		channels[int (channel)].avgValue = uint16_t (ADC_INVALID_VALUE);
		channels[int (channel)].errorReg = ADC_CHANNEL_OVER_MAX_STD_DEVIATION;
	}

	adcMutex.unlock();
}

float Ads1115c::readVoltage(void)
{
	ADC_MUX_e channel = settedChannel;

	readADC();

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		cout << "readVoltage error" << endl;
		return float (ADC_INVALID_VALUE);
	}

	return float (channels[int (channel)].avgValue * ((getGainValue(channel))/32768.0));
}

float Ads1115c::readVoltageSensor(float minVoltage, float minValue, float maxVoltage, float maxValue, float offset)
{
	ADC_MUX_e channel = settedChannel;

	float voltage = readVoltage();

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}
	float deltaValue = maxValue - minValue;
	float deltaVoltage = maxVoltage - minVoltage;
	float alpha = float (deltaValue/deltaVoltage);
	return float (alpha*(voltage - minVoltage) + minValue + offset);
}

float Ads1115c::read4to20mASignalConvertedToVotage(float resistor)
{
	ADC_MUX_e channel = settedChannel;

	readADC();

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

float Ads1115c::read4to20mASensor(float resistor, float minValue, float maxValue, float offset)
{
	ADC_MUX_e channel = settedChannel;

	float current = read4to20mASignalConvertedToVotage(resistor);

	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}
	float delta = maxValue - minValue;
	float alpha = float (delta/16.0);
	return float (alpha*(current - 4.0) + minValue + offset);
}

float Ads1115c::readWheatstone(ADC_MUX_e reference, ADC_MUX_e channel, float resistors)
{
	set2ReadADC(channel);
	float e0 = readVoltage();
	if(getChannelError(channel) != ADC_CHANNEL_IS_FINE) {
		return float (ADC_INVALID_VALUE);
	}

	set2ReadADC(reference);
	float vcc = readVoltage();
	if((vcc <= 0) || (getChannelError(channel) != ADC_CHANNEL_IS_FINE)) {
		return float (ADC_INVALID_VALUE);
	}

	float epsilon = e0/(2*vcc);
	return float (resistors*(0.5+epsilon)/(0.5-epsilon));
}
