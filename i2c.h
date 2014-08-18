#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include "init.h"

void initI2C(void) {
	PORTC |= (1 << 5) | (1 << 4);
	PORTC &= ~(1 << 3);
	DDRC |= (1 << 5) | (1 << 4) | (1 << 3);
	TWBR = 0b10101010;
	TWCR |= (1 << TWEN);
}

void start(void) {
	TWCR |= (1 << TWINT) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT))) { };
	if ((TWSR & (0xF8)) != 0x08) { PORTC |= (1 << 3); };
}

void sendCommand(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
}

uint8_t readReply(void) {
	TWCR |= (1 << TWINT);
	while (!(TWCR & (1 << TWINT))) { };
	return TWDR;
}

void stop(void) {
	TWCR |= (1 << TWINT) | (1 << TWSTO);
}
