



#ifndef GPIO_H
#define GPIO_H

#include "STD_Types.h"
#include "GPIO_Types.h"

void GPIO_WriteChannel(GPIO_ChannelType channel, STD_levelType level);
void GPIO_WritePort(GPIO_PortType port, uint8 value);
GPIO_LevelType GPIO_ReadChannel(GPIO_ChannelType ChannelId);
uint8 GPIO_ReadPort(GPIO_PortType port);

#endif
