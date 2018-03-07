/*
 * Control of sounder.
 *
*/

#include <avr/io.h>
#include "ovenready.h"

/*
* Initialise.
*
* Uses timer1
* system clock
* prescalar T1CK/16
* outputs OC1B and inverted OC1B
* OCR1C set to period for sound
* OCR1B set to half that
* PWM B enabled
*/

// 4KHz sounder
#define ALARMPERIOD (250/2)

// on/off times in units of 100ms (timer0 interrupt)
#define ONTIME 5
#define OFFTIME 5

static void alarminit(void)
{
	static uint8_t initialised;

	if(initialised) return;

	PRR = (1<<PRUSI) | (1<<PRADC);	// turn on timer1, don't need adc any more

	OCR1C = ALARMPERIOD;		// determines alarm frequency
	OCR1B = ALARMPERIOD / 2;

	GTCCR |= (1<<PWM1B) | (1<<COM1B0);	// pwm mode, OC1B outputs toggled
	initialised = 1;
}

/*
 * Sound the alarm.
 * Called from timer0 interrupt.
 * The pwm is turned on for ONTIME timer0 interrupts,
 * then off for OFFTIME timer0 interrupts.
*/

void alarmsound(void)
{
	static uint8_t count;

	if(count == 0)
	{
		alarminit();
		TCCR1 = (1<<CS11);	// count, T1CK/2
		count += 1;
		return;
	}

	count += 1;

	if(count == ONTIME) TCCR1 = 0;		// stop counting
	else if(count == ONTIME + OFFTIME) count = 0;

}


