

#include "Port.h"
#include "TM4C123GH6PM.h"
#include "Bit_Math.h"

#define PINCOUNT 43

const Port_ConfigType ConfigPtr[] = {
/*PA0*/		{Output,STD_low},
/*PA1*/		{Output,STD_low},
/*PA2*/		{Output,STD_low},
/*PA3*/		{Output,STD_low},
/*PA4*/		{Output,STD_low},
/*PA5*/		{Output,STD_low},
/*PA6*/	  {Output,STD_low},
/*PA7*/		{Output,STD_low},
	
/*PB0*/		{Output,STD_low},
/*PB1*/		{Output,STD_low},
/*PB2*/		{Output,STD_low},
/*PB3*/		{Output,STD_low},
/*PB4*/		{Output,STD_low},
/*PB5*/		{Output,STD_low},
/*PB6*/		{Output,STD_low},
/*PB7*/		{Output,STD_low},
	
/*PC0*/		{Output,STD_low},
/*PC1*/		{Output,STD_low},
/*PC2*/		{Output,STD_low},
/*PC3*/		{Output,STD_low},
/*PC4*/		{Output,STD_low},
/*PC5*/		{Output,STD_low},
/*PC6*/		{Output,STD_low},
/*PC7*/		{Output,STD_low},
	
/*PD0*/		{Output,STD_low},
/*PD1*/		{Output,STD_low},
/*PD2*/		{Output,STD_low},
/*PD3*/		{Output,STD_low},
/*PD4*/		{Output,STD_low},
/*PD5*/		{Output,STD_low},
/*PD6*/		{Output,STD_low},
/*PD7*/		{Output,STD_low},

/*PE0*/		{Output,STD_low},
/*PE1*/		{Output,STD_low},
/*PE2*/		{Output,STD_low},
/*PE3*/		{Output,STD_low},
/*PE4*/		{Output,STD_low},
/*PE5*/		{Output,STD_low},

/*PF0*/		{Input,STD_high},
/*PF1*/		{Output,STD_low},
/*PF2*/		{Output,STD_low},
/*PF3*/		{Output,STD_low},
/*PF4*/		{Input,STD_high}
};


void Port_Init(uint8 port)
{
	uint8 pinCounter = 0;
	uint8 portCount = 0;
	uint8 offset = 0;
	uint8 currentPin = 0;
	
	volatile unsigned long delay;
	//SYSCTL -> RCGC2 |= (uint32)(port & 0x0F);  //32-bit register (4 bytes) //every port has 1 bit in first (LSB) byte (00FE DCBA) //enable clock
	delay = SYSCTL -> RCGC2;    	 						//dummy cycle to wait for initialization
	
	switch(port)
	{
		case 'A' :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOA
			SYSCTL -> RCGC2 |= 0x01;
			portCount = 8;
			offset = 0;
			break;
		
		case 'B' :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOB
			SYSCTL -> RCGC2 |= 0x02;
			portCount = 8;
			offset = 8;
			break;
		
		case 'C' :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOC
			SYSCTL -> RCGC2 |= 0x04;
			portCount = 8;
			offset = 16;
			break;
		
		case 'D' :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOD
			SYSCTL -> RCGC2 |= 0x08;
			portCount = 8;
			offset = 24;
			break;
		
		case 'E' :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOE
			SYSCTL -> RCGC2 |= 0x10;
			portCount = 6;
			offset = 32;
			break;
		
		default :
			#undef GPIO_PORT
			#define GPIO_PORT GPIOF
			SYSCTL -> RCGC2 |= 0x20;
			portCount = 5;
			offset = 38;
			break;
	}
	
	GPIO_PORT -> LOCK = 0x4C4F434B;					//unlock GPIO Port (for C, B and F?)
	GPIO_PORT -> CR = 0xFF;									//allow changes to whole port
	GPIO_PORT -> AMSEL = 0x00;							//disable analog on Port
	GPIO_PORT -> PCTL = 0x00;								//0 for GPIO functionality
	
	
	for (currentPin=offset; currentPin < (portCount+offset); currentPin++)	//set pin directions according to configuration
	{
		if (ConfigPtr[currentPin].pinDirection == Output)
		{
			SET_BIT(GPIO_PORT -> DIR,pinCounter);
			pinCounter++;
		}else
			{
				CLR_BIT(GPIO_PORT -> DIR,pinCounter);
				pinCounter++;
			}
	
	}
	GPIOF -> AFSEL = 0x00;									//disable alt funct
	GPIO_PORT -> PUR = 0x11;
	GPIO_PORT -> DEN = 0xFF;								//enable digital I/O to whole port
}

