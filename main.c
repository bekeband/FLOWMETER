/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "xlcd.h"
#include "dtime.h"

#define SERIAL      0b00000001
#define KEYBOARD    0b00000010
#define TIMER       0b00000100
#define ADDATA      0b00001000
#define EXT         0b00010000

typedef struct {
  float PMIN;
  float PMAX;
  float VMIN;
  float VMAX;
} dslope_t;

typedef struct {
  unsigned char type;
  unsigned int param1;
  unsigned int param2;
} event_type;

typedef int (*message_handler)(event_type*);

message_handler Still_Message_Handler;

typedef struct {
  unsigned int param1;
  unsigned int param2;
  message_handler handle;
} menu_t;

/* Saved inbutton state for edge detection. */
int old_inbutton = 0xFF;

dslope_t AD_SLOPES[MAX_AD_COUNT];

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

unsigned char InButton()
{   unsigned char OLD_TRISD, OLD_PORTD;
    unsigned char result_high, result_low;
    OLD_TRISD = TRISD;
    OLD_PORTD = PORTD;
    TRISD = 0b11001111;
    PORTDbits.RD4 = 1;
    PORTDbits.RD5 = 0;
    result_high = (PORTD & 0x0F) << 4;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 1;
    result_low = PORTD & 0x0F;
    PORTD = OLD_PORTD;
    TRISD = OLD_TRISD;
    return (result_high | result_low);
};

void ClearEvent(event_type* event)
{
  event->type = 0;
}

int GetStandardEvent(event_type* event)
{ unsigned int inbutton;
  inbutton = InButton();
  if (inbutton != old_inbutton)
  { /* Event keyboard setting... */
    event->type = KEYBOARD;
    event->param1 = inbutton;
    old_inbutton = inbutton;
    return 1;
  } 
  if (INTERRUPT_OPTIONS.TIMER_EVENT_ON)
  {
    event->type = TIMER;
    event->param1 = 0;
    INTERRUPT_OPTIONS.TIMER_EVENT_ON = 0;
    return 1;
  }
  if (INTERRUPT_OPTIONS.NEW_AD_DATA)
  {
    event->type = ADDATA;
    event->param1 = 0;
    INTERRUPT_OPTIONS.NEW_AD_DATA = 0;
    return 1;
  }
  return 0;
}

unsigned char bbuffer[18];
float Vmin = 20;
float Vmax = 60;
float Pmin = -20;
float Pmax = 100;
float f;
int AD_INT;

int Main_Message_Handler(event_type* event)
{
  if (event->type == KEYBOARD)
  {
    CursorHome();
    sprintf(bbuffer, "CNT:%4d", event->param1);
    LCDWrite(bbuffer);
  }
  if (event->type == ADDATA)
  {
//        CalculateDatas();
    f = (AD_DATA[2] / 327.36);
    sprintf(bbuffer, "V %% = %7.3f", f);
    CursorHome();
    LCDWrite(bbuffer);
    SetDDRAMAddr(40);
//    f = Vmin + ((AD_DATA[2] - ))
    f /= 100;
    f *= (Vmax - Vmin);
    f += Vmin;
    sprintf(bbuffer, "VAL = %7.3f", f);
    SetDDRAMAddr(40);
    LCDWrite(bbuffer);
    INTERRUPT_OPTIONS.NEW_AD_DATA = 0;
  };
  ClearEvent(event);
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

uint8_t main(void)
{ 
  event_type next_event_type;


  /* Initialize I/O and Peripherals for application */
  InitApp();
  LCDClear();
  /* Global interrupt enabled */

  INTCONbits.GIE = 1;

  LCDWrite("Initialize ");
  Delay(500);
  LCDWrite(" OK ");
  Delay(500);
  LCDClear();
  Still_Message_Handler = Main_Message_Handler;
  
    /* main program loop... */
  while(1)
  {
    GetStandardEvent(&next_event_type);
    Still_Message_Handler(&next_event_type);

  }
  return 0;
}

