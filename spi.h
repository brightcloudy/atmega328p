#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include "init.h"

void initSPIMaster(void) {
	DDRB |= (1 << 5) | (1 << 3) | (1 << 2);
	DDRB &= ~(1 << 4);
	PORTB |= (1 << 2);
	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X);
}

void initSPISlave(void) {
	DDRB &= ~((1 << 5) | (1 << 3) | (1 << 2));
	DDRB |= (1 << 4);
	PORTB |= (1 << 2);
	SPCR |= (1 << SPE);
}

void send(uint8_t data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF))) { };
}

void sendCommand(uint8_t data) {
	initSPIMaster();
	PORTB &= ~(1 << 2);
	send(data);
	PORTB |= (1 << 2);
}

void sendCommand16(uint16_t data) {
	initSPIMaster();
	PORTB &= ~(1 << 2);
	send((uint8_t)(data >> 8));
	send((uint8_t)(data & 0xFF));
	PORTB |= (1 << 2);
}

uint8_t readReply() {
	while (!(SPSR & (1 << SPIF))) { };
	return SPDR;
}
