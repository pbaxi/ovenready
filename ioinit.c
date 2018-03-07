/*
 * Initialise I/O for ovenready.
 * Returns with LED off, LDR off,
 * timer0 will interrupt in just over 100ms.
 * ADC set up but disabled.
 *
*/

#include <avr/io.h>
#include "ovenready.h"

void ioinit(void)
{
	PRR = (1<<PRTIM1) | (1<<PRUSI); 	// shut down timer1 and usi
	ACSR = 1<<ACD;						// turn off comparator

	DDRB |= (1<<LED) | (1<<SOUNDER1) | (1<<SOUNDER2) | (1<<LDRPWR);	// gpio outputs


/*
 * ADC setup
 * use:
 *  VCC ref
 *  ADC1
 *  left adjust result (8 bit conversions)
 *  clock divide by 8
*/

	ADMUX = (1<<ADLAR) | (1<<MUX0);					// left adjust, channel 1
	ADCSRA = (1<<ADPS0) | (1<<ADPS1);				// divide clk by 8
	DIDR0 = (1<<ADC1D);								// disable channel 1 digital input
/*
 * set timer 0 to interrupt every 100ms
 * normal mode (count up)
 * clk divide by 1024 (ie about 1 ms)
*/
	TCCR0B = (1<<CS00) | (1<<CS02);		// clk divide by 1024
	TCNT0 = 255-99;						// overflow after 100 ticks
	TIMSK = (1<<TOIE0);					// enable overflow interrupt

}
