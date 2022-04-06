#ifndef UART__H__
#define UART__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define NU32_LED1 LATFbits.LATF0    // LED1 on the NU32 board
#define NU32_LED2 LATFbits.LATF1    // LED2 on the NU32 board
#define NU32_USER PORTDbits.RD7     // USER button on the NU32 board
#define NU32_SYS_FREQ 48000000ul    // 48 million Hz

void UART_Startup(void);
void UART_ReadUART1(char * string, int maxLength);
void UART_WriteUART1(const char * string);

#endif // UART__H__