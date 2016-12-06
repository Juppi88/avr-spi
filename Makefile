TARGET = libavr-spi
MCU = atmega328p
MCU_PROGRAMMER = m328p
F_CPU = 16000000

CFLAGS = -std=c99 -DF_CPU=$(F_CPU)L -mmcu=$(MCU) -Wall -Os

compile:
	# Compile the source for the library.
	avr-gcc $(CFLAGS) -c spi.c

	# Create the static library.
	ar rcs $(TARGET).a spi.o

asm:
	avr-gcc -S $(CFLAGS) -c spi.c

clean:
	rm -f *.o *.a

all:
	compile
