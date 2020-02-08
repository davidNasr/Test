
#include "TM4C123GH6PM.h"
#include "Kit_Connections.h"
#include "Port.h"
#include "STD_Types.h"
#include "Bit_Math.h"
#include "Gpio_Types.h"
#include "Gpio.h"


//default clock is 8MHZ
int main(void)
{
	Port_Init('F');
	int i = 0;
	
	while(1)
	{
		GPIO_WriteChannel(GPIO_Channel_F1,STD_high);
		
		if(GPIO_ReadChannel(GPIO_Channel_F0) == STD_low)
		{
			GPIO_WriteChannel(GPIO_Channel_F3,STD_low);
			GPIO_WriteChannel(GPIO_Channel_F2,STD_high);
		}else
			{
				GPIO_WriteChannel(GPIO_Channel_F2,STD_low);
				GPIO_WriteChannel(GPIO_Channel_F3,STD_high);
			}
	}
	
}

/*
void PORTF_init (void)
{
	//enable clock for PORTF    //F1, F2 and F3 are LEDs
	volatile unsigned long delay;
	SYSCTL -> RCGC2 = 0x00000020;  //32-bit register (4 bytes) //every port has 1 bit in first (LSB) byte (00FE DCBA = 0010 0000)
	delay = SYSCTL -> RCGC2;    	 //dummy cycle to wait for initialization	
  
	//configuration
	GPIOF -> LOCK = 0x4C4F434B;		//unlock GPIO Port F
	GPIOF -> CR = 0x1F;						//allow changes to PF4-0
	GPIOF -> AMSEL = 0x00;				//disable analog on Port F
	GPIOF -> PCTL = 0x00000000;		//PCTL GPIO on PF4-0
	GPIOF -> DIR = 0x0E;					//PF4,PF0 in, PF3-1 out
	GPIOF -> AFSEL = 0x00;				//disable alt funct on PF7-0
	GPIOF -> PUR = 0x11;					//enable pull-up on PF0 and PF4
	GPIOF -> DEN = 0x1F;					//enable digital I/O on PF4-0

}
*/
