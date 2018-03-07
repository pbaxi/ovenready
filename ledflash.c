/*
 * Flash the LED
 * Called from timer0 interrupt
*/

#include <avr/io.h>
#include "ovenready.h"

#define ONTIME 1
#define OFFTIME 19

void ledflash(void)
{
	static uint8_t count;

	count += 1;
	if(count == OFFTIME) LEDON;
	else if(count == OFFTIME + ONTIME)
	{
		LEDOFF;
		count=0;
	}
}
