////#include<lpc21xx.h>
////#include"header.c"
////void lcd_cmd(unsigned char cmd)
////{
////unsigned int temp;
////IOCLR0=0xfe<<16;
////temp=(cmd&0xf0)<<16;
////IOSET0=temp;
////IOCLR0=1<<17;
////IOCLR0=1<<18;
////IOSET0=1<<19;
////delay_ms(2);
////IOCLR0=1<<19;
////IOCLR0=0xfe<<16;
////temp=(cmd&0x0f)<<20;
////IOSET0=temp;
////IOCLR0=1<<17;
////IOCLR0=1<<18;
////IOSET0=1<<19;
////delay_ms(2);
////IOCLR0=1<<19;

////}
////void lcd_data(unsigned char data)
////{
////unsigned int temp;
////IOCLR0=0xfe<<16;
////temp=(data&0xf0)<<16;
////IOSET0=temp;
////IOSET0=1<<17;
////IOCLR0=1<<18;
////IOSET0=1<<19;
////delay_ms(2);
////IOCLR0=1<<19;
////IOCLR0=0xfe<<16;
////temp=(data&0x0f)<<20;
////IOSET0=temp;
////IOSET0=1<<17;
////IOCLR0=1<<18;
////IOSET0=1<<19;
////delay_ms(2);
////IOCLR0=1<<19;
////}
////void lcd_init()
////{
////IODIR0=0Xfe<<16;
////PINSEL2=(0X0);
////lcd_cmd(0x03);
////lcd_cmd(0x02);
////lcd_cmd(0x28);
////lcd_cmd(0x0e);
////lcd_cmd(0x01);
////IOCLR0=1<<19;

////}
////void lcd_string(char *ptr)
////{
////    while(*ptr!=0)
////    {
////        lcd_data(*ptr);
////        ptr++;
////    }
////}

#include "header.c"

void lcd_cmd(unsigned char cmd)
{
    unsigned int temp;
    IOCLR1=0XFE<<16;
    temp=(cmd&0xf0)<<16;
    IOSET1=temp;
    IOCLR1=1<<17;
    IOCLR1=1<<18;
    IOSET1=1<<19;
    delay_ms(2);
    IOCLR1=1<<19;
    ///
    IOCLR1=0XFE<<16;
    temp=(cmd&0x0f)<<20;
    IOSET1=temp;
    IOCLR1=1<<17;
    IOCLR1=1<<18;
    IOSET1=1<<19;
    delay_ms(2);
    IOCLR1=1<<19;
}
void lcd_data(unsigned char data)
{
    unsigned int temp;
    IOCLR1=0XFE<<16;
    temp=(data&0xf0)<<16;
    IOSET1=temp;
    IOSET1=1<<17;
    IOCLR1=1<<18;
    IOSET1=1<<19;
    delay_ms(2);
    IOCLR1=1<<19;
    ////
      IOCLR1=0XFE<<16;
    temp=(data&0x0f)<<20;
    IOSET1=temp;
    IOSET1=1<<17;
    IOCLR1=1<<18;
    IOSET1=1<<19;
    delay_ms(2);
    IOCLR1=1<<19;
}
void lcd_init(void)
{
    IODIR1=0xfe<<16;
    PINSEL2=(0X0);
    lcd_cmd(0X02);
    lcd_cmd(0X03);
    lcd_cmd(0X28);
    lcd_cmd(0X0E);
    lcd_cmd(0X01);
}
void lcd_string(char *ptr)
{
    while(*ptr!=0)
    {
        lcd_data(*ptr);
        ptr++;
    }
}
void lcd_int(int num)
{
   int i=0,a[10];
    if(num==0)
        lcd_data('0');
    if(num<0)
    {
        num=-num;
        lcd_data('-');
    }
    if(num>0)
    {
   while(num)
   {
       a[i++]=num%10;
       num=num/10;
   }
   for(i=i-1;i>=0;i--)
   {
       lcd_data(a[i]+48);
   }
   }
}
void lcd_float(float num)
{
    int i;
    i=num;
    lcd_int(i);
    lcd_data('.');
    num=num-i;
    num=num*100;
    lcd_int(num);
}
void lcd_cgram(void)
{
    int i,a[8]={0X0A,0X0A,0X0A,0X0A,0X0A,0X0A,0X0A,0X00};
    lcd_cmd(0x40);
    for(i=0;i<8;i++)
    lcd_data(a[i]);
}
void lcd_hex(int val)
{
    char ascii[9];
    int i=0,r;
    if(val==0)
    {
        lcd_data('0');
        return;
    }
    while(val>0)
    {
      r=val%16;
      if(r<10)
          ascii[i++]='0'+r;
      else if(r>10)
          ascii[i++]='A'+(r-10);
      val/=16;
    }
    for(i-=1;i>=0;i--)
    lcd_data(ascii[i]);
}
