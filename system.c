/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>           /* HiTech General Includes */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

int int_counter;

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}
