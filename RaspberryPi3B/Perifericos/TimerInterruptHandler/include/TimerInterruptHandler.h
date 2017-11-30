#ifndef TIMER_INTERRUPT_HANDLER_H
#define TIMER_INTERRUPT_HANDLER_H

#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void setInterruptPeriod(useconds_t period);
void alarmWakeup(int sig_num);

// Esta função deve ser definida na aplicação
void interrupt(void);

#endif
