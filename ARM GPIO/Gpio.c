

#include "Gpio.h"
#include "TM4C123GH6PM.h"
#include "Gpio_Types.h"
#include "STD_Types.h"
#include "Bit_Math.h"


void GPIO_WriteChannel(GPIO_ChannelType channel, STD_levelType level)
{
	GPIO_PortType currentPort;
	GPIO_ChannelType currentChannel;
	
	if(channel <= 31)											//get port and pin
	{
		 currentPort = channel/8;
		 currentChannel = channel%8;
	}else if (channel <= 37)
		{
			currentPort = GPIO_Port_E;
			currentChannel = channel - 32;
		}else
			{
				currentPort = GPIO_Port_F;
				currentChannel = channel - 38;	
			}
			
		switch(currentPort)
			{
			case GPIO_Port_A :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOA
				break;
			
			case GPIO_Port_B :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOB
				break;
			
			case GPIO_Port_C :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOC
				break;
			
			case GPIO_Port_D :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOD
				break;
			
			case GPIO_Port_E :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOE
				break;
			
			default :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOF
				break;
			}

		if (level == STD_high)
		{
			SET_BIT(GPIO_PORT -> DATA,currentChannel);
		}else
			{
				CLR_BIT(GPIO_PORT -> DATA,currentChannel);	
			}

}
GPIO_LevelType GPIO_ReadChannel(GPIO_ChannelType ChannelId)
{
	GPIO_PortType currentPort;
	GPIO_ChannelType currentChannel;
	GPIO_LevelType channelValue = 0;
	
	if(ChannelId <= 31)											//get port and pin
	{
		 currentPort = ChannelId/8;
		 currentChannel = ChannelId%8;
	}else if (ChannelId <= 37)
		{
			currentPort = GPIO_Port_E;
			currentChannel = ChannelId - 32;
		}else
			{
				currentPort = GPIO_Port_F;
				currentChannel = ChannelId - 38;	
			}
			
		switch(currentPort)
			{
			case GPIO_Port_A :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOA
				break;
			
			case GPIO_Port_B :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOB
				break;
			
			case GPIO_Port_C :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOC
				break;
			
			case GPIO_Port_D :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOD
				break;
			
			case GPIO_Port_E :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOE
				break;
			
			default :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOF
				break;
			}

		channelValue = GET_BIT(GPIO_PORT -> DATA,currentChannel);
			
		return channelValue;
			
}

void GPIO_WritePort(GPIO_PortType port, uint8 value)
{
	switch(port)
			{
			case GPIO_Port_A :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOA
				break;
			
			case GPIO_Port_B :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOB
				break;
			
			case GPIO_Port_C :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOC
				break;
			
			case GPIO_Port_D :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOD
				break;
			
			case GPIO_Port_E :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOE
				break;
			
			default :
				#undef GPIO_PORT
				#define GPIO_PORT GPIOF
				break;
			}
			
			GPIO_PORT -> DATA = (uint32) value;
}

