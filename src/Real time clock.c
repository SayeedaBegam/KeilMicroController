
#include <lpc214x.h>
#include <stdio.h>

void transmit(unsigned char ch)
{
	while(!(U0LSR & 0x20));
	U0THR=ch;
}
void main()
{
	int i;
	unsigned char temp[50]="UART Implementation";
	
	PINSEL0=5;
	U0LCR=0x83;
	U0DLM=0x00;
	U0DLL=97;
	U0LCR=0x03;
	for(i=0;temp[i]!='\0';i++)
	{
		transmit(temp[i]);
	}
}