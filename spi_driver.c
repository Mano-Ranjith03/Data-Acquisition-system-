#include <LPC21xx.H>
#include "header.c"
void spi0_init(void)
{
    PINSEL0|=0x1500;
    IODIR0|=(1<<7);
    IOSET0|=(1<<7);
    S0SPCR=0x20;
    S0SPCCR=15;
}
#define SPIF (( S0SPSR>>7)&1)
unsigned char spi0(unsigned char data)
{
    S0SPDR=data;
    while(SPIF==0);
    return S0SPDR;
}
main()
{
    unsigned int temp;
    uart0_init(9600);
    spi0_init();
    while(1)
    {
        temp=mcp3204_read(1);
        uart0_tx_integer(temp);
        uart0_tx_string("\n\r");
    }
}
