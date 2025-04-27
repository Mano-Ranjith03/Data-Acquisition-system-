#include "hdr.c"
#include <LPC21xx.H>

void uart0_init(unsigned int baud )
{
    int a[]={15,60,30,15,15};
    unsigned int result = 0;
    unsigned int PCLK;
    PCLK=a[VPBDIV]*1000000;
    result=PCLK/(baud*16);
    PINSEL0|=0x5;
    U0LCR=0x83;
    U0DLL=result & 0XFF;
    U0DLM=result>>8;
    U0LCR=0x03;
}
#define THRE ((U0LSR>>5 )&1 )
void uart0_tx(unsigned char c)
{
    U0THR=c;
    while(THRE ==0);  
}
void uart0_tx_string(char *ptr)
{
    while(*ptr!=0)
    {
        U0THR=*ptr;
        while(THRE==0);
        ptr++;
    }
}
void uart0_tx_interger(int num)
{
int i=0,a[10];
    if(num==0)
        uart0_tx('0');
    if(num<0)
    {
        num=-num;
        uart0_tx('-');
    }
    if(num>0)
    {
   while(num)
   {
       a[i++]=num%10;
       num=num/10;
   }
   for(i=i-1;i>=0;i--)
       uart0_tx(a[i]+48);
   //sum=sum*10+(a[i]);
   
   }
}
void uart0_tx_float(float num)
{
    int n=num;
    uart0_tx_interger(n);
    uart0_tx('.');
    num=num-n;
    num=num*100;
    uart0_tx_interger(num);
}


