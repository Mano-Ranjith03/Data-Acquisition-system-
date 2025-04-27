
#include "header.c"
void adc_init(void)
{
    PINSEL1|=0X15400000;
    ADCR=0X00200400;
//    No ch
//    adc_init clk 3mhz
//    no power down
//    10 bit restrict;
//    ADCR stop
        
}
#define DONE ((ADDR>>31)&1)
unsigned int adc_read(unsigned char ch_num)
{
    unsigned int res=0;
    ADCR|=(1<<ch_num);//select ch num
    ADCR|=1<<24;//strt adc
    while(DONE==0);//wait to transmit
    ADCR^=1<<24;//stop adc
    ADCR^=(1<<ch_num);//diselect ch
    res=(ADDR>>6)&0X3FF;
    return res;
}
