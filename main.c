#include <LPC21xx.H>
#include "hdr.c"
#include<string.h>
#define TIME (H>>5)&1
void time(void);
char d[6][4];
unsigned char D,DA,dd,H,S,M;
unsigned int Light,litp;
main()
{
    strcpy(d[0],"Su");
    strcpy(d[1],"M");
    strcpy(d[2],"Tu");
    strcpy(d[3],"W");
    strcpy(d[4],"Th");
    strcpy(d[5],"F");
    strcpy(d[6],"Sa");
    H|=(1<<5)|(1<<6);
    H|=0x7;
    unsigned int temp=0,pot=0;
    float vout,amb,vout1,tmp;
    lcd_init();
    uart0_init(9600);
    adc_init();
    i2c_init();
    i2c_write(0xd0,0x2,H);
    i2c_write(0xd0,0x03,6);    
        while(1)
        {
            time();
            temp=adc_read(1);
            pot=adc_read(2);
            Light=adc_read(3);
            vout=(temp*3.3)/1023;
            amb=(vout-0.5)/0.01;
            vout1=(Light*5)/4095;
            litp=100-(Light*100)/4095;^M
            tmp=(vout1*100)/5;
            lcd_cmd(0x80);
            lcd_data('T');
            lcd_data(':');
            lcd_int(amb);
            lcd_data('C');
            Light=((float)Light/1023)*100;
            lcd_data(' ');
            lcd_data('L');
            lcd_data(':');
            lcd_int(Light);
            lcd_data(' ');
            lcd_data('P');
            lcd_int(pot);
            lcd_data('V');
            ///uart//
            uart0_tx_string("*********************\n\r");            
            uart0_tx_string("senosr outputs\n\r");
            uart0_tx_string("Temp:");
            uart0_tx_interger(amb);
            uart0_tx('C');
            uart0_tx_string("\n\rLight:");
            uart0_tx_interger(Light);
            uart0_tx_string("\n\rPot:");
            uart0_tx_interger(pot);
            uart0_tx_string("\n\r");
            delay_ms(999);
        }
}
void time()
{
    H=i2c_read(0xd0,0x2);
    D=i2c_read(0xd0,0x04);
    S=i2c_read(0xd0,0x0);
     M=i2c_read(0xd0,0x1);
    DA=i2c_read(0xd0,0x03);
            if(TIME ==0)
            {
                lcd_cmd(0xcd);
                lcd_string("AM");
            }
            else
            {
                lcd_cmd(0xcd);
                lcd_string("PM");
            }
            H=H&0X1F;
            lcd_cmd(0xc0);
            lcd_data((H/0x10)+48);
            lcd_data((H%0x10)+48);
            lcd_data(':');
            lcd_data((M/0x10)+48);
            lcd_data((M%0x10)+48);
            lcd_data(':');
            lcd_data((S/0x10)+48);
            lcd_data((S%0x10)+48);
            dd=((DA%0x10)+48);
            lcd_data(' ');
            lcd_string(d[dd-48]);
}
