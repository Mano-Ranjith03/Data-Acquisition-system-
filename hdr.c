#include <lpc21xx.h>
#define u8 unsigned char
#define u32 unsigned int
extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int sec);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *ptr);
extern void lcd_int(int num);
extern void lcd_float(float num);
extern void uart0_init(unsigned int baud );
extern void uart0_tx(unsigned char c);
extern void uart0_tx_string(char *ptr);
extern void uart0_tx_interger(int num);
extern void uart0_tx_float(float num);
extern void adc_init(void);
extern unsigned int adc_read(unsigned char ch_num);
extern void i2c_write(unsigned char sa,unsigned char mr,unsigned char data);
extern void i2c_init(void);
extern unsigned char i2c_read(unsigned char sa,unsigned char mr);

