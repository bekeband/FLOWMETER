/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <string.h>
#include "user.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

int AD_DATA[MAX_AD_COUNT];
unsigned long AD_BUFFER[MAX_AD_COUNT];
int AD_COUNTER = 0;
int AD_AVERAGE_FACTOR = DEFAULT_AD_AVERAGE_FACTOR;
int AD_AVERAGE_COUNTER;

interrupt_options_t INTERRUPT_OPTIONS;

void interrupt isr(void)
{ int i;
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */


    /* Determine which flag generated the interrupts */
    if(INTCONbits.RBIF) // If RB port changed ...
    {
//        int_counter++;
      INTCONbits.RBIF = 0; /* Clear RB port changed interrupt flag. */
    }
    if (PIR1bits.TMR1IF)   // TMR 1 interrupt ?
    {
      PIR1bits.TMR1IF = 0;
      LoadTMR1(TMR1_LOAD_DATA);        //reload tmr1
      int_counter++;
      ADCON0bits.GO_DONE = 1;
//      TIMER_EVENT_ON = 1;
    };
    if (PIR1bits.ADIF)
    {
      PIR1bits.ADIF = 0;
      if (AD_AVERAGE_COUNTER == (AD_AVERAGE_FACTOR))
      {
        AD_DATA[AD_COUNTER] = (AD_BUFFER[AD_COUNTER] >>= 5);
        AD_BUFFER[AD_COUNTER] = 0;
        AD_AVERAGE_COUNTER = 0;
        /* Next AD data... */
        if (++AD_COUNTER == MAX_AD_COUNT)
        {
          INTERRUPT_OPTIONS.NEW_AD_DATA = 1;
          AD_COUNTER = 0;
        };
        ADCON0bits.CHS = AD_COUNTER;
      }
      AD_AVERAGE_COUNTER++;
      /* Select AD channel. */
      AD_BUFFER[AD_COUNTER] += (ADRESH * 256) + ADRESL;
    }
    //PORTBbits.RB3 = 0;  // Signal the unhandled interrupt.
        /* Unhandled interrupts */
}
