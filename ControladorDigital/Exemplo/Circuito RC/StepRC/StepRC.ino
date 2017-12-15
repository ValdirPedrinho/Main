/*
           Vo        0.5*Vcc              3
  G(s) = ----- = --------------- = ---------------
           d      1 + 0.5*R*C*s     1 + (50E-3)*s
           
  d: duty cycle of PWM
  Vo: output voltage
  Vcc: input voltage
  R: resistance
  C: capacitance

  Microcontroller: Texas Instruments C2000 Piccolo MCU F28027 LaunchPad Development Kit
  IDE: Energia (Similar to Arduino IDE)
*/ 

const int pwmPin = 40;	// Change the numbering depending on the microcontroller

int duty = 85; //1.0V or 170 -> 2.0V

void setup()
{
  pinMode(pwmPin, OUTPUT);
}

void loop()
{
  delay(500);
  duty = (duty >= 170) ? 85 : 170;
  analogWrite(pwmPin, duty);
}


