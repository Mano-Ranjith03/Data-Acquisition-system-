/*mcp3204_driver.c
  ext slave driver
*/
#include <LPC21xx.H>
#include "header.c"
#define CS0 (1<<7)
#define u32 unsigned int
 #define u8 unsigned char



u32 mcp3204_read(u8 ch_num)
{
    u32 res=0;
    u8 byteH=0,byteL=0;
    ch_num<<=6;
    IOCLR0=CS0;//CS0=0
		spi0(0x06);//Start bit,SGL mode,D2
		byteH=spi0(ch_num);
		byteL=spi0(0x00);
	IOSET0=CS0;//CS0
    byteH=byteH&0x0f;
    res=(byteH<<8)|byteL;
    return res;
}



