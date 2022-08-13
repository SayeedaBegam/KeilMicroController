
#include<lpc21xx.h>

 void delay(int k)		// Situation Delay
 {
 int i,j;
 	 for(i=0;i<k;i++)
	 {
 for(j=0;j<1000000;j++);
   }
 }
 
 int main()
{
	PINSEL0 = 0X00000000; // P0.0 TO P0.15 as GPIO
	IO0DIR = 0X0000FFFF; // P0.0 TO P0.15 Configured as Output port.
	
	while(1)
	{
		IO0SET=0x00004421;		// Situation 1
		delay(5);
		IO0CLR=0x00000421;
			
		IO0SET=0x00004214;		// Situation 2
		delay(5);
		IO0CLR=0x00004210;
			
		IO0SET=0x00002144;		// Situation 3
		delay(5);
		IO0CLR=0x00002104;
			
		IO0SET=0x00001442;		// Situation 4
		delay(5);
		IO0CLR=0x00001042;
	}
}