/*
 * Pin assignments
 *
 * LDRIN_SW is light sensor and switch input.
 * LED is LED output.
 * LDRPWR is power out for LDR.
 * SOUNDER1 is sounder output 1
 * SOUNDER2 is sounder output 2
 *
 * The LDRIN_SW pin is connected to ADC1 input.
 * The switch is also connected from this pin to GND.
 * So a voltage close to 0 should be regarded as switch pressed.
 *
 * Power for LDR PB0 (pin 5)
 * LED PB1 (pin 6)
 * LDR/Switch PB2/ADC1 (pin 7)
 * Sounder PB3 to PB4 (OC1B, !OC1B) (pin 2, pin 3)
*/

#ifndef OVENREADY_INCL
#define OVENREADY_INCL

#define LDRIN_SW PB2
#define LED PB1
#define LDRPWR PB0
#define SOUNDER1 PB3
#define SOUNDER2 PB4

#define LEDON PORTB |= (1<<LED)
#define LEDOFF PORTB &= ~(1<<LED)
#define LEDTOGGLE PORTB ^= (1<<LED)


// states
enum STATE {
	SETUP,
	RUN,
	ALARM
};


// function prototypes
void ioinit(void);		// i/o setup
uint8_t readldr(void);	// return LDR value
void alarmsound(void);		// sound the alarm
void ledflash(void);		// flash the LED

#endif
