#ifndef ECHO_H_
#define ECHO_H_

#include "Driver/UART/UARTDriver.h"
#include <string.h>

void echo(char* output) {

	SerialService uart = SerialService();
	uart.init();
	
	uart.write(std::strlen(output), &output);
}

#endif /*ECHO_H_*/