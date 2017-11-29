#include <SPI.h>
#include <Servo.h>

//----------------------------------------------
// SPI variables
//----------------------------------------------

int buf [1];        // spi digital buffer
//byte index;           // buffer index
boolean process_it;   // flag to process data

//----------------------------------------------
// Servo variables
//----------------------------------------------

#define SERVO 6

Servo s; // servo handler
int pos; // servo position

void setup (void)
{
//    Serial.begin (115200);   // debugging

    //----------------------------------------------
    // SPI Setup
    //----------------------------------------------

    // have to send on master in, *slave out*
    pinMode(MISO, OUTPUT);

    // turn on SPI in slave mode
    SPCR |= _BV(SPE);

    // get ready for an interrupt
//    index = 0;   // buffer empty
    process_it = false;

    // now turn on interrupts
    SPI.attachInterrupt();   
   
    //----------------------------------------------
    // Servo Setup
    //----------------------------------------------
    
    s.attach(SERVO);
    s.write(90);
	SPDR = 90;

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
    byte c = SPDR;  // grab byte from SPI Data Register

    // add to buffer if room
    if (index < sizeof buf)
    {
 //       buf [index++] = c;
        buf [0] = c;
        process_it = true;
    }  // end of room available
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
    if (process_it)
    {
        pos = buf[0];
        s.write(pos);
		SPDR =  pos;
//        index = 0;
        process_it = false;
    }  // end of flag set

} // end of loop
