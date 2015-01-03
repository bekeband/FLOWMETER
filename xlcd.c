

#include "dtime.h"
#include "xlcd.h"
#include <string.h>


void LCDPut(unsigned char data)
{
    LCDDisable();
    LCDData();
    LCDSetWrite();
    LCDSetData(data);
    LCDEnable();
    Delay(2);
    LCDDisable();
}

void LCDCommand(unsigned char cdata)
{   
    LCDDisable();
    LCDInstruction();
    LCDSetWrite();
    LCDSetData(cdata);
    LCDEnable();
    Delay(30);
    LCDDisable();
}

void LCDClear()
{
    LCDCommand(CLEAR_DISPLAY);
}

void CursorHome()
{
    LCDCommand(CURSOR_HOME);
}

int LCDInit()
{
    #if (XLCDBLOCKING == 0)            //;non blocking
        #if (XLCDMODE == 1)            //;delay
        #warning "Mode cannot be delay if NONBLOCKING in MpAM option"
        #endif
    #endif
    #if (XLCDRWPIN == 10)             // ;grounded
        #if (XLCDMODE == 0)         //;Read BF
        #warning "Read BF mode not possible(No read is possible with RW pin grounded) "
        #endif
    #endif
    Delay(15);                      /* 15 msec delay */

/************************************************************************/
/*  DATA port initialization                                            */
/************************************************************************/
                                //  only lower nibble can be selected
//    BANKSEL TRISA
//    movlw   0x00
    XLCDDATATRIS = 0;           //;make port output

/************************************************************************/
/*  Control port initialization                                         */
/************************************************************************/
//        BANKSEL TRISA
    XLCDRSTRIS = 0;
    XLCDENTRIS = 0;
//        bcf     XLCDRSPORT,XLCDRSPIN    ;TRIS of RSpin made output
//        bcf     XLCDENPORT,XLCDENPIN    ;TRIS of Enpin made output
    #ifndef XLCDRWPINGND        //;need not select if this pin in LCD is grounded
        XLCDRWTRIS = 0;
//        bcf     XLCDRWPORT,XLCDRWPIN    ;TRIS of RWpin made output
    #endif

//        BANKSEL XLCDRSPORT
//    XLCDRSPORT = 0;
//    LCDInstruction();
//    LCDDisable();
//    XLCDENPORT = 0;
//        bcf     XLCDRSPORT,XLCDRSPIN
//        bcf	    XLCDENPORT,XLCDENPIN
    #ifndef XLCDRWPINGND            // ;if RW pin LCD grounded
//      bcf     XLCDRWPORT,XLCDRWPIN
//        LCDSetWrite();
//        XLCDRWPORT = 0;
    #endif
    LCDCommand(FUNCTION_SET | DATA_LENGTH_8 | CHAR_LINES_2);
    Delay(5);               //  5 msec
    LCDCommand(FUNCTION_SET | DATA_LENGTH_8 | CHAR_LINES_2);
    Delay(1);
//    Delay10uSec(10);        // 10usec as user guide
    LCDCommand(FUNCTION_SET | DATA_LENGTH_8 | CHAR_LINES_2);
    Delay(5);               //  5 msec

    LCDCommand(DISPLAY_CONTROL | DISPLAY_ON);
    LCDCommand(CLEAR_DISPLAY);
};


void SetDDRAMAddr(int newaddr)
{
    LCDCommand(SET_DDRAM_ADDR | newaddr);
}

/* LCDWrite */
void LCDWrite(const char* c)
{ int i = 0;
  while (c[i])
  {
    LCDPut(c[i++]);
  }
}