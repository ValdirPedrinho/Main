/*
           Vo        0.5*Vcc              3
  G(s) = ----- = --------------- = ---------------
           d      1 + 0.5*R*C*s     1 + (50E-3)*s
           
  d: duty cycle of PWM
  Vo: output voltage
  Vcc: input voltage
  R: resistance
  C: capacitance
                           1
  PI(s) = 6.3333 + ---------------
                    (911.85E-6)*s
                    
  Time constant of closed loop: 5ms
  Percentage of overshoot of closed loop:: 2%

  Microcontroller: Texas Instruments C2000 Piccolo MCU F28027 LaunchPad Development Kit
  IDE: Energia (Similar to Arduino IDE)  
*/ 

#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/LibCtrEqDiff.h"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/TransferFunctions/TF1stOrdEqDiff.c"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/TransferFunctions/TF2ndOrdEqDiff.c"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/Utilities/utilities.c"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/Converters/ADCCtrDAC.c"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/Filters/Butterworth2nd.c"
#include "/home/valdir/ti/Energia_Projects/CtrRC/LibCtrCEqDiff/source/Controllers/CtrPIEqDiff.c"

const int analogInPin = 6;	// Change the numbering depending on the microcontroller
const int pwmPin = 40;		// Change the numbering depending on the microcontroller

const int     ADC_Bit  = 12;
const double  ADC_SG   = 1.0;
const double  ADC_Min  = 0.0;
const double  ADC_Max  = 3.3;
const int_t   PWM_Max  = 255;
const double  CTR_K    = 6.3333333;
const double  CTR_Tau  = 911.85*micro_const;
const int     CTR_Fs   = 1000;
const double  CTR_Min  = 0.0;
const double  CTR_Max  = 1.0;
const double  BTW_fc   = 500.0;

CtrPI ctrPI;
RefFilterPI refFilter;
ADC2Ctr adc2ctr;
Ctr2PWM ctr2PWM;
Butterworth2nd fbFilter;

const int SAMPLES = 50;
const int CYCLES  = CTR_Fs/2;
int_t fb = 0;
double ref = 2.0; 

void setup()
{
  pinMode(pwmPin, OUTPUT);
  createADC2CtrHandler(&adc2ctr, ADC_Bit, ADC_SG, ADC_Min, ADC_Max);
  createCtr2PWMHandler(&ctr2PWM, PWM_Max, CTR_Min, CTR_Max);
  createRefFilterPI(&refFilter, CTR_K, CTR_Tau, CTR_Fs);
  createButterworth2nd(&fbFilter, (double) BTW_fc, CTR_Fs);
  createPIHandler(&ctrPI, &refFilter, NULL, &adc2ctr, &ctr2PWM, CTR_K, CTR_Tau, CTR_Fs, CTR_Min, CTR_Max);
}

void loop()
{
  for(int j=0; j<CYCLES; j++)
  {
    fb = 0;
    for(int i=0; i<SAMPLES; i++)
    {
      fb += analogRead(analogInPin);
    }
    fb /= SAMPLES;
    analogWrite(pwmPin, runPI2PWM(&ctrPI, ref, (double) fb));
    delayMicroseconds(1000000/CTR_Fs-10);
  }
  ref = (ref >= 2.0) ? 1.0 : 2.0;
}


