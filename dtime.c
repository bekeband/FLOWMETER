
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include "user.h"
#include "system.h"
#include "dtime.h"

/* delay may between 1usec - 70 usec*/

/*void Delayusec(int delay)
{ unsigned char PR2byte;
  PR2byte = (unsigned char)(delay * 3.5);
    Timer2OFF();    //Stop timer 2
    LoadTMR2(0);
    LoadPR2(PR2byte);
    Timer2ON();
    while (!PIR1bits.TMR2IF);
    PIR1bits.TMR2IF = 0;
}

void Delay10uSec(int usec10)
{   int i;
    for (i = 0; i < usec10; i++);
}*/

void DelayMs()
{   int i;
    for (i = 0; i < 165; i++);
}

void Delay(int msec)
{   int j;
    for (j = 0; j < msec; j++) DelayMs();
}

