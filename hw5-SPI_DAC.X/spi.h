#ifndef SPI__H__
#define SPI__H__

void initSPI();
unsigned char spi_io(unsigned char o);
unsigned short make16(char channel, unsigned char v);

#endif // SPI__H__