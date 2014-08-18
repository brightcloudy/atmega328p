#include "init.h"

int main(void) {
	PORTC |= (1 << 5) | (1 << 4);
	PORTC &= ~(1 << 3);
	DDRC |= (1 << 5) | (1 << 4) | (1 << 3);
	TWBR = 0b10101010;
	TWCR |= (1 << TWEN);
	TWCR |= (1 << TWINT) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT))) { };
	if ((TWSR & (0xF8)) != 0x08) { PORTC |= (1 << 3); };
	TWDR = 0b10101010;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
	TWDR = 0b00111100;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
	TWCR |= (1 << TWINT) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT))) { };
	TWDR = 0b10101011;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	TWCR |= (1 << TWINT);
	while (1) { };
}
