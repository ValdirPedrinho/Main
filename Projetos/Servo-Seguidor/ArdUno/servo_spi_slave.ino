#include <SPI.h>
#include <Servo.h>

//==============================================
// Variaveis da SPI
//==============================================

char buf [1];           // SPI buffer
boolean process_it;     // Flag para processar a interrupcao

//==============================================
// Variaveis do Servo Motor
//==============================================

#define SERVO 6

Servo s; // Objeto servo
int pos; // Posicao do servo

void setup (void)
{
    //==============================================
    // SPI Setup
    //==============================================

    pinMode(MISO, OUTPUT);   // Configura a porta MISO como saida (p/ usar como escravo)
    SPCR |= _BV(SPE);        // Configura o registrador SPCR para modo escravo
    process_it = false;
    SPI.attachInterrupt();   // Habilita a interrupcao
   
    //==============================================
    // Servo Setup
    //==============================================
    
    s.attach(SERVO);  // Especifica em que pino o canal PWM do servo esta
    s.write(90);      // Coloca na posicao inical de 90 (barra alinhada com o servo)
    SPDR = 90;        // Coloca no registrador de dados (buffer) da SPI a posicao atual
}

// Rotina de interrupcao
// Tratada quando chegam dados pela SPI
ISR (SPI_STC_vect)
{
    pos = SPDR;          // Atualiza a posicao para o solicitado pela SPI
    process_it = true;   // Habilita a flag para que o servo seja acionado
}

void loop (void)
{
    if (process_it)
    {
        s.write(pos);        // Aciona o servo para a nova posicao
        SPDR =  pos;         // Coloca no registrador de dados (buffer) da SPI a posicao atual 
        process_it = false;  // Desabilita a flag
    }

}
