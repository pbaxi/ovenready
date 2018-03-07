
# these are the C source files
sources = main.c ioinit.c timerinterrupt.c ldr.c sounder.c ledflash.c

# this is a list of corresponding object files
cobjs = $(sources:.c=.o)

#this is the root name for the executable
prog = main

# these define where the compiler is and what it's called
CC = avr-gcc
AS = avr-as

# objcopy used to generate hex from elf file
OBJCOPY = avr-objcopy

# flags for C compiler
CFLAGS = -Wall -Os
# attiny85 running at 1MHz
CFLAGS += -DF_CPU=1000000 -mmcu=attiny85

# sort out dependencies
CPPFLAGS += -MD -MP

# how to make hex file from an elf file
%.hex : %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

# main target: hex file for input to programmer
$(prog).hex: $(prog).elf

# elf file for main target
$(prog).elf : $(cobjs)
	$(CC) $(CFLAGS) $(cobjs) -o $@

# include dependencies
-include $(sources:%.c=%.d)

# program the flash
.PHONY : program
program: $(prog).hex
	avrdude -c usbasp -p ATtiny85 -U flash:w:$(prog).hex:i

# make clean
.PHONY : clean
clean:
	rm -f $(cobjs) $(prog).elf $(prog).hex *.d

