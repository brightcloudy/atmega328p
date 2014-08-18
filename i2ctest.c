#include "init.h"
#include "i2c.h"

int main(void) {
	initI2C();
	start();
	sendCommand(0b10101010);
	sendCommand(0b11000011);
	stop();
	while (1) { };
}
