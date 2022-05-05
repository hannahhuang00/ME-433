#ifndef UART_MASTER
#define UART_MASTER

#include <xc.h>

#define DELAY_TICKS 12000000
#define NU32_SYS_FREQ 48000000
#define NU32_DESIRED_BAUD 230400

void UART1_Startup(void);
void ReadUART1(char * message, int maxLength);
void WriteUART1(const char * string);

#endif