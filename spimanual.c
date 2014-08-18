#include "init.h"

int main(void) {
	
	DDRB |= (1 << 5) | (1 << 3) | (1 << 2);
	DDRB &= ~(1 << 4);
	PORTB |= (1 << 2);
	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X);
	PORTB &= ~(1 << 2);
	SPDR = 0b10100101;
	while (!(SPSR & (1 << SPIF))) {};
	PORTB |= (1 << 2);
	SPSR &= ~(1 << SPIF);
	while (1) { };
}
