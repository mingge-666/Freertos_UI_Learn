#ifndef __KEY_H
#define __KEY_H

#include <stdint.h>
typedef enum{
	LED_On  = 0,
	LED_Off  ,
	LED_Toggle,
}emGpioStatusTdf;//对应的是高电平点亮

void vLEDCMode(uint16_t GPIO_Pin_x , emGpioStatusTdf State);

#endif
