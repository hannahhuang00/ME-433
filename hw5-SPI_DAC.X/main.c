#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include<stdio.h>
#include <math.h>
#include"spi.h"

// DEVCFG0
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = FRCPLL // use fast frc oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = OFF // primary osc disabled
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt value
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz fast rc internal oscillator
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#define PI 3.14159265
#define PERIOD 12000000

int main() {

    __builtin_disable_interrupts(); // disable interrupts while initializing things
    
    initSPI();
    
    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    __builtin_enable_interrupts();
    
    unsigned short p;
    unsigned char sine_v;
    unsigned char tria_v;
    _CP0_SET_COUNT(0);
    while (1) {
        // CS low
        if (_CP0_GET_COUNT() >= PERIOD*2) {_CP0_SET_COUNT(0);}
        LATAbits.LATA0 = 0;
        // calculate sine as signed float between -255/2 to +255/2, then shift centerline up by 255/2
        sine_v = (unsigned int) (255/2 + 255/2 * sin(2*PI * _CP0_GET_COUNT()/PERIOD));
        p = make16(0,sine_v);
        spi_io(p >> 8);
        spi_io(p & 0xFF);
        // CS high
        LATAbits.LATA0 = 1;
        
        LATAbits.LATA0 = 0;
        // make triangle wave
        if (_CP0_GET_COUNT() <= PERIOD) {
            tria_v = (255 * _CP0_GET_COUNT()/(PERIOD));
        } else {
            tria_v = (unsigned int) (255 - 255 * (_CP0_GET_COUNT()-PERIOD)/(PERIOD));
        }
        
        p = make16(1,tria_v);
        spi_io(p >> 8);
        spi_io(p & 0xFF);
        // CS high
        LATAbits.LATA0 = 1;
    } 
}
