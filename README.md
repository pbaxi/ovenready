My kitchen oven takes ages to warm up, so I go away and do something else whilst
waiting. It would be nice if it sounded an alarm when the oven was up to
temperature so I would know when it was ready. As it is, the red light goes
off when it reaches the set temperature.

This little project uses a cheap LDR to detect when the red light goes off
(ie the oven is up to temperature) and sounds an alarm when that happens.
It uses an ATtiny85 (8 pin DIL AVR microcontroller). You could probably do
something similar using a 555 timer, but this is more fun.

Timer 0 is used to generate an interrupt about every 100ms. All processing
is done in the interrupt service routine. The system has 3
possible states: SETUP, RUN and ALARM.

In the SETUP state (the initial state on power up) on each interrupt the
state of the oven light is determined (on/off) and an LED used to simply
mirror it. The idea is to help you position the unit correctly over the oven
light. When a button is pressed the system moves to the RUN state.

In the RUN state the oven light is checked. When it's detected to be off on
a number of consecutive interrupts the system moves to the ALARM state. When
in the RUN state the LED is flashed occasionally so you know the system is
alive.

In the ALARM state a piezo sounder is activated. The system remains in this
state until power is removed.

Various efforts are made to save power. Outside interrupts the CPU idles.
The LDR is powered from a gpio output that is only turned on when the state
of the oven light is being checked. The aim is to power it all from a 3V
coin cell.

Peter Baxendale
7th March 2018

