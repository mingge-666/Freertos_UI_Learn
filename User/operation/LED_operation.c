#include "LED_operation.h"
#include <stdint.h>
#include "LED.h"


static uint32_t LEDTimer = 0;

void LED_Tick(void){
	LEDTimer++;//1ms¼Ó1
}


void vLEDBrink(uint32_t u32OnTimeMs,uint32_t u32OffTimeMs,uint16_t GPIO_Pin_x){
	LEDTimer %= (u32OnTimeMs+u32OffTimeMs);
	if(LEDTimer>=u32OnTimeMs){
		vLEDCMode(GPIO_Pin_x,LED_Toggle);
	}
}

