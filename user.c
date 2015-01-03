/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "xlcd.h"
#include "user.h"


static double PRECISION = 0.00000000000001;
static int MAX_NUMBER_STRING_SIZE = 32;

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

char temp[20];

/* <Initialize variables in user.h and insert code for user algorithms.> */

char* PrintBin(char* buffer, unsigned char data)
{ int i; int ccode;
  for (i = 0; i < 8; i++)
  {
    if (data & 0x080) ccode = 1;
    else ccode = 0;
    buffer[i] = 0b00110000 + ccode;// + ((data && 0x80) >> 8);
    data <<= 1;
  }
  buffer [i+1] = '\0';
  return buffer;
}

char* PrintDec(char buffer[], unsigned int data, int width)
{ int fills;
  utoa(temp, data, 10);
  fills = width - strlen(temp);
  memset(buffer, ' ', fills);
  strcpy((buffer + fills), (const char*)temp);
  return buffer;
}

/*
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}*/

void InitApp(void)
{
  /* TODO Initialize User Ports/Peripherals/Project here */
  /* Setup analog functionality and port direction */

//    ADCON1bits.PCFG = 0b0110;
  ADCON1bits.PCFG = 0b0010;

  /* Initialize peripherals */

 // TRISAbits.TRISA4 = 0;
  TRISAbits.TRISA5 = 0;

  /* PORTB 4-5 as inputs */

  TRISBbits.TRISB4 = 1;
  TRISBbits.TRISB5 = 1;

  /* RB3 is output for init signal. */
  TRISBbits.TRISB3 = 0;
  TRISBbits.TRISB0 = 0;

  PORTBbits.RB3 = 1;  // clear PORTB 3 LED.
  PORTBbits.RB0 = 1;  // clear PORTB 0 LED.

  /* rising edge of RB pin have been generate the RB interrupt...*/

//    EnableRBPORTINT();      /* Enable RB port interrupt on change */

  /* TMR 1 setting
   * Crystal frequency is 15MHz, FOSC/4 = 3,75 MHz
   */

  T1CONbits.TMR1CS = 0;       // internal oscillator
  /* Prescaler setting 1:8 */
  T1PRESCALER(0x03);

  /* Prescale TMR2 = 1*/
  T2PRESCALER(0x00);
  /* Postscale TMR2 = 1*/
  T2POSTSCALER(0x00);
  LoadTMR1(TMR1_LOAD_DATA);
  EnableTMR1INT();            // enable TMR 1 interrupt...
  Timer1ON();                 // Start TMR1 timer

  ADCON1bits.ADFM = 1;
  ADCON0bits.ADON = 1;
  PIR1bits.ADIF = 0;

  ADCON0bits.CHS = 0x02;

  ADCON0bits.ADCS = 0b10;   /* 32TOSC */

  EnableADINT();

  EnablePERINT();         // Enable periphelial interrupt...

  LCDInit();

  ADCON0bits.GO_DONE = 1;
  
  /* Enable interrupts */
}

