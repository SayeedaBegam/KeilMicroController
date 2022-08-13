
#include <LPC214X.H>

int r;
int rotation = 2;

void motor_cw(void);
void motor_ccw(void);

void delay(void);
int main(void)
{	
	
	PINSEL0 = 00; 	// select the pin function as GPIO
	IODIR0 = (0xF<<4); 	// Set the port direction P0.4-P0.7 port pins output)
				
	while(1)
	{
		
		for(r=0; r<rotation; r++)
		{
			motor_cw();
		}
		
		for(r=0; r<rotation; r++)
		{
			motor_ccw();
		}
				
	}
}
void motor_cw(void)		// Clockwise rotation
{
	IOCLR0 = 0xC0; 	
	IOSET0 = 0x30;		// 0011
	delay();

	IOCLR0 = 0x90;		
	IOSET0 = 0x60;		// 0110
	delay();

	IOCLR0 = 0x30;
	IOSET0 = 0xC0;		// 1100
	delay();

	IOCLR0 = 0x60;
	IOSET0 = 0x90;		// 1001
	delay();
}

void motor_ccw(void)	// Counter-Clockwise rotation
{
	IOCLR0 = 0x60;
	IOSET0 = 0x90;		// 1001
	delay();
	
	IOCLR0 = 0x30;
	IOSET0 = 0xC0;		// 1100
	delay();
	
	IOCLR0 = 0x90;		
	IOSET0 = 0x60;		// 0110
	delay();
	
	IOCLR0 = 0xC0; 	
	IOSET0 = 0x30;		// 0011
	delay();
}

void delay(void)		// rotation change
{
	int  s;
	for(s = 0;s<=550000;s++)
	{};
}