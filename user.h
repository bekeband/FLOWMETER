/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#include "system.h"

/* TODO Application specific user parameters used in user.c may go here */

#define	BUTTON_UP	3
#define BUTTON_DOWN	2
#define BUTTON_ENTER	0
#define BUTTON_EXIT	7
#define BUTTON_MENU	6
#define BUTTON_START_STOP	5

#define INIT_OUTPUT         PORTBbits.RB3
#define START_STOP_INPUT_01 PORTBbits.RB4
#define START_STOP_INPUT_02 PORTBbits.RB5

/* TIMER 1 defines. */

#define Timer1OFF()           T1CONbits.TMR1ON = 0
#define Timer1ON()            T1CONbits.TMR1ON = 1

#define EnableTMR1INT()       PIE1bits.TMR1IE = 1
#define DisableTMR1INT()      PIE1bits.TMR1IE = 0

#define EnableADINT()         PIE1bits.ADIE = 1
#define DisableADINT()        PIE1bits.ADIE = 0

#define EnablePERINT()        INTCONbits.PEIE = 1
#define DisablePERINT()       INTCONbits.PEIE = 0

#define EnableRBPORTINT()     INTCONbits.RBIE = 1
#define DisableRBPORTINT()    INTCONbits.RBIE = 0

#define ADMICROSEC    30
#define TMR1LOADDATA ((1000000l / FCY) * ADMICROSEC)

#define LoadTMR1(data)        TMR1 = data

/* TIMER 2 defines. */

#define Timer2OFF()     T2CONbits.TMR2ON = 0
#define Timer2ON()      T2CONbits.TMR2ON = 1

/* pre_code = 0 1:1, 1 1:2, 2 1:4, 3 1:8 */
#define T1PRESCALER(pre_code)   T1CONbits.T1CKPS = pre_code;
/* pre_code = 0 1:1, 1 1:4, 2 1:16 */
#define T2PRESCALER(pre_code)   T2CONbits.T2CKPS = pre_code;
/* post code = 0- 15 1:1 to 1:16 divorces. */
#define T2POSTSCALER(post_code) T2CONbits.TOUTPS = post_code;

#define LoadTMR2(data)          TMR2 = data
#define LoadPR2(data)           PR2 = data

#define TMR1_LOAD_DATA        65424

typedef union {
  struct {
    unsigned	S407                : 1;
    unsigned	S406                : 1;
    unsigned	S405                : 1;
    unsigned	S404                : 1;
    unsigned	S403                : 1;
    unsigned	S402                : 1;
    unsigned	S401                : 1;
    unsigned	S400                : 1;
  };
  struct {
    unsigned	EXIT                : 1;
    unsigned	MENU                : 1;
    unsigned	START_STOP          : 1;
    unsigned  EXTRA1              : 1;
    unsigned	UP                  : 1;
    unsigned	DOWN                : 1;
    unsigned  EXTRA2              : 1;
    unsigned	ENTER               : 1;
  };
} buttons_t;

typedef union {
  struct {
    unsigned TIMER_EVENT_ON :1;
    unsigned NEW_AD_DATA    :1;
  };
} interrupt_options_t;

typedef buttons_t* buttons_p;

#define MAX_AD_COUNT 4
#define DEFAULT_AD_AVERAGE_FACTOR 1024

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
/* Print byte value to binary character buffer to print the display. */
char* PrintBin(char* buffer, unsigned char data);
char* PrintDec(char buffer[], unsigned int data, int width);
char* PrintFloat(float n, char* res, int afterpoint);
char* floatToString(char* str, float num);

extern int int_counter;
extern int AD_DATA[];
extern interrupt_options_t INTERRUPT_OPTIONS;
extern int AD_AVERAGE_FACTOR;