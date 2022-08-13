
#include<lpc213x.h>
#define LCD (0xff<<16)
#define RS (1<<13)
#define RW (1<<14)
#define EN (1<<15)
void delay_fv(unsigned int x,int y);
void lcd_display(unsigned int x);
void cmd(unsigned char m);
void lcd_ini();
void lcd_pos(int line, int pos);
void lcd_str(unsigned char *x);
void pll();
void adc_ini();
unsigned long int adc_data();
int main()
 {
unsigned long temp;
unsigned char first,second,third,fourth,fifth;
PINSEL0=0X00000000;
IO0DIR=0XFFFFFFFF;
pll();
adc_ini();
lcd_ini();
lcd_str("TEMP VALUE IS");
lcd_pos(2,6);
lcd_display('C');
while(1)
 {
temp=adc_data();
temp=temp*3300;
temp=temp/1023;
first=temp%10+'0';
temp=temp/10;
second=temp%10+'0';
temp=temp/10;
third=temp%10+'0';
temp=temp/10;
fourth=temp%10+'0';
temp=temp/10;
lcd_pos(2,0);
lcd_display(fourth);
lcd_display(third);
lcd_display(second);
lcd_display('.');
lcd_display(first);
 }
 }
void delay_fv(unsigned int x,int y)
 {
 unsigned int i,j;
 for(i=0;i<x;i++)
 for(j=0;j<y;j++);
 }
void lcd_display(unsigned int x)
 {
 IO0CLR|=(RS|RW|EN|LCD);
 IO0SET|=(x<<16);
 IO0SET|=RS;
 IO0CLR|=RW;
 IO0SET|=EN;
 delay_fv(100,200);
IO0CLR|=EN;
 delay_fv(10,10);
 }
void cmd(unsigned char m)
 {
 IO0CLR|=(RS|RW|EN|LCD);
 IO0SET|=(m<<16);
 IO0CLR|=RS;
 IO0CLR|=RW;
 IO0SET|=EN;
 delay_fv(100,10);
 IO0CLR|=EN;
 delay_fv(100,10);
 }
void lcd_ini()
 {
cmd(0X38);
cmd(0X0e);
cmd(0X06);
cmd(0X01);
cmd(0X80);
 }
void lcd_pos(int line, int pos)
 {
 if(line==1)
 cmd(0x80+pos);
 else if(line==2)
 cmd(0xc0+pos);
 }
void lcd_str(unsigned char *x)
 {
 while(*x!='\0')
 {
 lcd_display(*x);
 x++;
 }
 }
void pll()
 {
 /*PLL IS CONFIGURED TO GET 60HZ pCLK*/
PLLCFG=0X24; // SET PSEL=2 AND MSEL=5
PLLCON=0X01; //PLL IS ACTIVE BUT NOT YET
//CONNECT
PLLFEED=0XAA; //FEED SEQUENCE
PLLFEED=0X55; //FEED SEQUENCE
while((PLLSTAT & 0X400)==0); //WAIT FOR FEED SEQUENCE
//TO BE INSERTED
PLLCON=0X03; // PLL HAS BEEN ACTIVE AND
//BEING CONNECTRD
VPBDIV=0X00; // SET PCLK 1/4th of FCCLK
PLLFEED=0XAA; //FEED SEQUENCE
PLLFEED=0X55; //FEED SEQUENCE
 }
void adc_ini()
 {
AD0CR = 1<<21; //A/D is Operational
AD0CR = 0<<21; //A/D is in Power Down Mode
PINSEL1 = 0x01000000;//P0.28 is Configured as Analog to Digital
//Converter Pin AD0.1
AD0CR = 0x00200802; //CLKDIV=4,Channel-0.1
//Selected,BURST=0,EDGE=0
/*PDN=0
A/D Clock = PCLK /(CLKDIV+1);*/
 }
unsigned long int adc_data()
 {
 unsigned long rec;
AD0CR |= (1<<24);
//Start Conversion
while(!(AD0GDR & 0x80000000));
/*Wait untill the DONE bits Sets*/
rec = AD0GDR;
AD0CR &= ~0x01000000; //Stops the A/D
//Conversion
rec = rec >> 6; // data is present after 6 bit
rec = rec & 0x3FF; //Clearing all other Bits
 return (rec);
 }
