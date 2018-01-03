#include "TimerInterruptHandler.h"

void setInterruptPeriod(useconds_t period)
{
	if(period > 200000)
	{
		period = 200000;
	}
    signal(SIGALRM, alarmWakeup);  
    ualarm(period, period);	
}

void alarmWakeup(int sig_num)
{
    if(sig_num == SIGALRM)
    {
		interrupt();
    }
}
