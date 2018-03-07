/*
 * LDR control.
*/

#include <avr/io.h>
#include "ovenready.h"


uint8_t readldr(void)
{
	uint8_t val;

	PORTB |= (1<<LDRPWR);		// turn on LDR power

	// may need a delay here

	ADCSRA |= (1<<ADEN) | (1<<ADSC);	// enable and start conversion
	while(ADCSRA & (1<<ADSC));			// wait till done

	val = ADCH;

	PORTB &= ~(1<<LDRPWR);		// turn off LDR power
	ADCSRA &= ~(1<<ADEN);		// disable ADC

	return val;
}

