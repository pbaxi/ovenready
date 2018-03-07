/*
 * Interrupt service routine for timer.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ovenready.h"

// LDR reading above which ready light is off
#define OFF_THRESHOLD 127

// LDR reading below which means the switch is closed
#define SWITCH_THRESHOLD 2

// number of times to detect oven light off before done
#define NSAMPLES 10

extern enum STATE state;
static uint8_t donecount;

ISR(TIM0_OVF_vect)
{
	uint8_t ldrval;

	TCNT0 = 255-99;		// reset timer overflow after 100 ticks

	switch(state)
	{
		case SETUP:
			ldrval = readldr();

			// if no light
			if(ldrval > OFF_THRESHOLD) LEDOFF;

			// if light on
			else if(ldrval > SWITCH_THRESHOLD) LEDON;

			// switch pressed
			else
			{
				LEDOFF;
				state = RUN;
			}
			break;

		case RUN:
			ledflash();
			ldrval = readldr();

			if(ldrval > OFF_THRESHOLD)
				donecount += 1;
			else donecount = 0;

			if(donecount == NSAMPLES)
				state = ALARM;
			break;

		case ALARM:
			alarmsound();
			break;
	}
}
