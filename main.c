/*
 * Oven ready detection.
 *
*/

#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "ovenready.h"

enum STATE state;

int main()
{
	state = SETUP;

	ioinit();	// set up i/o
	sei();		// enable interrupts

	while(1)
	{
		sleep_mode();
	}

	return 0;
}
