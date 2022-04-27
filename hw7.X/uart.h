#ifndef UART_MASTER
#define UART_MASTER

#include <xc.h>

#define DELAY_TICKS 12000000
#define NU32_SYS_FREQ 48000000
#define NU32_DESIRED_BAUD 230400

void initUART1(void);
void readUART1(char * message, int maxLength);
void writeUART1(const char * string);

#endif