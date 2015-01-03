/* 
 * File:   xlcd.h
 * Author: Bandi
 *
 * Created on 2012. október 26., 14:44
 */

#ifndef XLCD_H
#define	XLCD_H

#include <htc.h>           /* Global Header File */

#ifdef	__cplusplus
extern "C" {
#endif

/* defines general XLCD symbols for     */

//#define CLOCK_FREQ   .15000000
//#define XLCDINTERFACE   8
#define XLCDLINE        1
#define XLCDFONT        0
//#define XLCDNIBBLESEL   0
#define XLCDDATATRIS    TRISD
#define XLCDDATAPORT    PORTD
#define LCDSetData(x)   XLCDDATAPORT = x
#define LCDReadStatus() XLCDDATAPORT

#define XLCDRSPORT      PORTEbits.RE0
#define XLCDRSTRIS      TRISEbits.TRISE0
#define LCDData()       XLCDRSPORT = 1
#define LCDInstruction()    XLCDRSPORT = 0
#define XLCDENTRIS      TRISEbits.TRISE2
#define XLCDENPORT      PORTEbits.RE2
#define LCDEnable()     XLCDENPORT = 1
#define LCDDisable()    XLCDENPORT = 0
#define XLCDRWTRIS      TRISEbits.TRISE1
#define XLCDRWPORT      PORTEbits.RE1
#define LCDSetWrite()   XLCDRWPORT = 0
#define LCDSetRead()    XLCDRWPORT = 1
#define XLCDBLOCKING    1
#define XLCDMODE        1
#define XLCDDELAY 	.250
#define XLCDDISPLAYON   1
#define XLCDCURSORON    1
#define XLCDBLINKON     1
#define XLCDENTRYID     1
#define XLCDENTRYSHIFT  0

/* Function set 0 0 0 0 1 DL N ? ? Sets interface data length 37 ?s     */
/* DL = 1: 8 bits, DL = 0: 4 bits   N = 1: 2 lines, N = 0: 1 lines*/
/*F = 1: 5 × 10 dots, F = 0: 5 × 8 dots*/

#define CLEAR_DISPLAY   0b00000001      /* clear display instruction. */

#define CURSOR_HOME     0b00000010      /* Go to cursor home. */

#define ENTRY_MODE      0b00000100      /* Entry mode set. */
    #define INCR_CURSOR_POS 0b00000010      /* Increment cursor position. */

#define DISPLAY_CONTROL 0b00001000      /* Display On/Off control */
    #define DISPLAY_ON      0b00000100      /* All entire display ON. */
    #define CURSOR_ON       0b00000010      /* Cursor ON */
    #define CURSOR_BLINKY   0b00000001      /* Blink the cursor. */

#define CURSOR_SHIFT_DISP   0b00010000      /* Cursor move / shift display. */
    #define SHIFT_DISPLAY   0b00001000      /* Shift display. */
    #define SHIFT_RIGHT     0b00000100  /* Shift right/ left.*/

#define FUNCTION_SET    0b00100000      /* FUNCTIONR SET MASK*/
    #define DATA_LENGTH_8   0b00010000      /* 8 bits data length*/
    #define CHAR_LINES_2    0b00001000      /* 2 lines  */
    #define CHAR_DOTS_5x10  0b00000100      /* Char dots 5 x 10 */

#define SET_CGRAM_ADDR  0b01000000      /* Set CGRAM address in lower 6 bits.*/

#define SET_DDRAM_ADDR  0b10000000      /* Set DDRAM address in lower 6 bits.*/
    
#define BUSY_FLAG       0b10000000      /* busy flag. (in operation). */


    int  LCDInit();
    void LCDPut(unsigned char data);
    void LCDClear();
    void CursorHome();
    void LCDWrite(const char*);
    void SetDDRAMAddr(int newaddr);

#ifdef	__cplusplus
}
#endif

#endif	/* XLCD_H */

