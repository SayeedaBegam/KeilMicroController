
#include <lpc214x.h>

void delay()
{
	int i;
	for(i=0;i<1500;i++);
}
void main()
{
	int i,j;
	PINSEL1=1<<19; // Enable DAC by selecting P0.25 as AOUT
	DACR=0; // initial Digital value is 0
	while(1)
	{
		for(i=0;i<1024;i++) // increaments output from 0 to 1023
		{
			DACR=i<<6;
			delay();
		}
		for(i=1023;i>=0;i--) // decreaments output from 1023 to 0
		{
			DACR=i<<6;
			delay();
		}
	}
}