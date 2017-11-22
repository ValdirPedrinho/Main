/* check ADS1115 datasheet */

#ifndef ADS1115C_REGISTERS_H
#define ADS1115C_REGISTERS_H

// ==============================================================================================================================
// 
// FIRST BYTE
//
// The first is a 8-bit "pointer" register that directs data to either the 16-bit read-only conversion register (0) or the 16-bit read/write config register (1).

typedef enum ADC_CHOOSE_REGISTER {
	ADC_READ_ONLY_REGISTER		= 0x00,
	ADC_READ_WRITE_REGISTER		= 0x01
} ADC_CHOOSE_REGISTER_e;

// ==============================================================================================================================
//
// SECOND BYTE (15 downto 8 - READ/WRITE REGISTER)
//
// Bit[15] : flag for operational status

typedef enum ADC_OS {
	ADC_OS_0 					= 0x00,
	ADC_OS_1					= 0x01
} ADC_OS_e;

// ==============================================================================================================================
//
// SECOND BYTE (15 downto 8 - READ/WRITE REGISTER)
//
// Bit[14:12] : input multiplexer configuration (select adc channel)

typedef enum ADC_MUX {
	ADC_MUX_AIN0_AIN1 			= 0x00,
	ADC_MUX_AIN0_AIN3 			= 0x01,
	ADC_MUX_AIN1_AIN3 			= 0x02,
	ADC_MUX_AIN2_AIN3 			= 0x03,
	ADC_MUX_AIN0_GND 			= 0x04,
	ADC_MUX_AIN1_GND 			= 0x05,
	ADC_MUX_AIN2_GND 			= 0x06,
	ADC_MUX_AIN3_GND 			= 0x07
} ADC_MUX_e;

// ==============================================================================================================================
//
// SECOND BYTE (15 downto 8 - READ/WRITE REGISTER)
//
// Bit[11:9] : programmable gain amplifier configuration

typedef enum ADC_FS {
	ADC_FS_6V144 				= 0x00,
	ADC_FS_4V096 				= 0x01,
	ADC_FS_2V048 				= 0x02,
	ADC_FS_1V024 				= 0x03,
	ADC_FS_0V512 				= 0x04,
	ADC_FS_0V256 				= 0x05
} ADC_FS_e;

// ==============================================================================================================================
//
// SECOND BYTE (15 downto 8 - READ/WRITE REGISTER)
//
// Bit[8] : device operating mode

typedef enum ADC_MODE {
	ADC_MODE_CONTINUOUS 		= 0x00,
	ADC_MODE_SINGLE_SHOT 		= 0x01
} ADC_MODE_e;

// ==============================================================================================================================
//
// THIRD BYTE (7 downto 0 - READ/WRITE REGISTER)
//
// Bit[7:5] : data sample rate

typedef enum ADC_DSR {
	ADC_DSR_8SPS		 		= 0x00,
	ADC_DSR_16SPS		 		= 0x01,
	ADC_DSR_32SPS		 		= 0x02,
	ADC_DSR_64SPS		 		= 0x03,
	ADC_DSR_128SPS		 		= 0x04,
	ADC_DSR_250SPS		 		= 0x05,
	ADC_DSR_475SPS		 		= 0x06,
	ADC_DSR_860SPS		 		= 0x07
} ADC_DSR_e;

// ==============================================================================================================================
//
// THIRD BYTE (7 downto 0 - READ/WRITE REGISTER)
//
// Bit[4] : comparator mode: traditional (0); window (1)

typedef enum ADC_COMP_MODE {
	ADC_COMP_MODE_T		 		= 0x00,
	ADC_COMP_MODE_W		 		= 0x01
} ADC_COMP_MODE_e;

// ==============================================================================================================================
//
// THIRD BYTE (7 downto 0 - READ/WRITE REGISTER)
//
// Bit[3] : comparator polarity: low (0); high (1)

typedef enum ADC_COMP_POL {
	ADC_COMP_POL_L		 		= 0x00,
	ADC_COMP_POL_H		 		= 0x01
} ADC_COMP_POL_e;

// ==============================================================================================================================
//
// THIRD BYTE (7 downto 0 - READ/WRITE REGISTER)
//
// Bit[2] : latching comparator : latching (0); non-latching (1)

typedef enum ADC_COMP_LAT {
	ADC_COMP_LAT_L		 		= 0x00,
	ADC_COMP_LAT_NL		 		= 0x01
} ADC_COMP_LAT_e;

// ==============================================================================================================================
//
// THIRD BYTE (7 downto 0 - READ/WRITE REGISTER)
//
// Bit[1:0] : comparator queue

typedef enum ADC_COMP_QUE {
	ADC_COMP_QUE_A_ONE	 		= 0x00,
	ADC_COMP_QUE_A_TWO	 		= 0x01,
	ADC_COMP_QUE_A_FOUR	 		= 0x02,
	ADC_COMP_QUE_DISABLE 		= 0x03
} ADC_COMP_QUE_e;

#endif

