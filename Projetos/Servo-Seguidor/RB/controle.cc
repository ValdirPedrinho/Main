#include <wiringPiSPI.h>
#include <iostream>
#include <thread>

#include "TimerInterruptHandler.h"
#include "Ads1115c.h"
#include "LibCtrEqDiff.h"

using namespace std;

#define ADC_CHANNEL ADC_MUX_AIN0_GND	// Canal no ADS1115c utilizado (A0)
static const int SPI_CHANNEL = 0;		// Canal SPI do RBP 3 utilizado

// =========================================================================
// Constantes do controlador PI
// =========================================================================
const double CTR_K                  = 1.15;				// Ganho proporcional
const double CTR_TAU                = 50*mili_const;	// Constante de tempo 
const double CTR_FREQ_SAMPLING  	= 15.0;				// Frequência de amostragem

// =========================================================================
// Constantes do controlador PI
// =========================================================================
bool endConfigFlag			= false;	// Flag que indica o término da configuração do sensor
float sensorGain			= 0.0;		// Ganho do sensor [V/graus]
float initialVoltage		= 0.0;		// Tensão utilizada no cálculo do ganho (referência do PI)
float voltage 				= 0.0;		// Tensão a ser lida constantemente (feedback do PI)
intMAX_t deltaPosition 		= 0.0;		// Incremento/decremento da posição do servo
int position				= 90;		// Posição do servo
unsigned char buffer[1];				// Buffer para comunicação SPI

// =========================================================================
// Objeto/TDA para comunicar com o ADS1115c e implementar o PI
// =========================================================================
Ads1115c_t adc;
CtrPI ctrPI;

void* readAdc2Config(void*); // Thread para configurar o sensor

int main(void)
{
    cout << "\nInicializando Servo-Seguidor" << endl ;

	// =========================================================================
	// Configuração do ADC (850 SPS)
	// =========================================================================

	adc.set2ReadADC(ADC_MUX_AIN0_GND);
	adc.setNumSamplesPerRead(int (850/CTR_FREQ_SAMPLING));

	// =========================================================================
	// Configuração do ganho do sensor
	// =========================================================================

	// Chamada da Thread
	pthread_t readAdc2ConfigThread;
	int val = pthread_create(&readAdc2ConfigThread, NULL, &readAdc2Config, NULL);
	if(val) cout << "Error: can't create readAdc2ConfigThread" << endl;

	// Espera 'i' pelo terminal para encerrar o modo de configuração
	char confirmConfig = ' ';
	while(confirmConfig != 'i')
	{
		cin >> confirmConfig;
	}

	endConfigFlag = true; 							// Habilita a flag para encerrar a thread 
	pthread_join(readAdc2ConfigThread, NULL);		// Aguarda o encerramento da thread
	sensorGain = initialVoltage/15.0;				// Calcula o ganho do sensor
	cout << "Sensor Gain: " << sensorGain << endl;
	sleep(5);

	// =========================================================================
	// Inicializa o controlador
	// =========================================================================

	createPIHandler(&ctrPI, NULL, NULL, CTR_K, CTR_TAU, CTR_FREQ_SAMPLING, double (-initialVoltage/4), double (initialVoltage/4));

	// =========================================================================
	// Configura a SPI
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

	setInterruptPeriod(useconds_t (1000000/CTR_FREQ_SAMPLING));

	// =========================================================================
	// Loop Infinito
	// =========================================================================

	for(;;)
	{
		// Toda a computação é feita no tratamento da interrupção
	}

    return 0;
}

// =========================================================================
// Rotina de interrupção
// Tratada quando o Timer gera um alarme
// =========================================================================
void interrupt(void)
{
	// Lê a tensão do sensor
	voltage = adc.readVoltage();

	// Calcula incremento/decremento a partir da saída do PI
	deltaPosition = _round(double (runPI(&ctrPI, initialVoltage, voltage)/sensorGain));
	cout << "Delta Position: " << deltaPosition << endl;

	// Atualiza a posição
	position += deltaPosition;

	// Garante que a posição esteja ente 0 e 180 graus
	position = (position > 180) ? 180 : position;
	position = (position < 0) ? 0 : position;
	
	// Atualiza o buffer e evia a nova posição pela SPI
	buffer[0] = position;
	int fd = wiringPiSPIDataRW(SPI_CHANNEL, buffer, 1);
    if(fd < 0)
    {
	    cout << "SPI error";
    }
}

// =========================================================================
// Thread para configuração do sensor
// =========================================================================
void* readAdc2Config(void*)
{
	while(!endConfigFlag)
	{
		// Lê a tensão e imprime na tela a cada 0,5s
		initialVoltage = adc.readVoltage();
		cout << "Tensao: " << initialVoltage << endl;
		usleep(500000);
	}
	return NULL;
}
