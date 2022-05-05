#include <xc.h>
#include "font.h"
#include "ssd1306.h"

void drawChar(unsigned char x, unsigned char y, unsigned char letter) {
    for (int i=0; i<5; i++) {
        if (ASCII[letter][i]) {
            ssd1306_drawPixel(x,y,1);
        } else {
            ssd1306_drawPixel(x,y,0);
        }
    }
}

void drawString(unsigned char x, unsigned char y, unsigned char word) {
    
}