#include "init.h"
#include "spi.h"

int main(void) {
	sendCommand16(0b0000000100000000);
	sendCommand16(0b0001000000000000);
	sendCommand16(0b0010000000110101);
	while (1) { };
}
