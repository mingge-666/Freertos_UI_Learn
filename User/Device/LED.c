#include "LED.h"
#include "gpio.h"



void vLEDCMode(uint16_t GPIO_Pin_x , emGpioStatusTdf State){
	if(State == LED_On){
		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_x,GPIO_PIN_RESET);
	}
	else if(State == LED_Off){
		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_x,GPIO_PIN_SET);
	}
	else if(State == LED_Toggle){
		HAL_GPIO_TogglePin(GPIOC,GPIO_Pin_x);
	}
}

void vLEDBMode(uint16_t GPIO_Pin_x , emGpioStatusTdf State){
	if(State == LED_On){
		HAL_GPIO_WritePin(GPIOB,GPIO_Pin_x,GPIO_PIN_RESET);
	}
	else if(State == LED_Off){
		HAL_GPIO_WritePin(GPIOB,GPIO_Pin_x,GPIO_PIN_SET);
	}
	else if(State == LED_Toggle){
		HAL_GPIO_TogglePin(GPIOB,GPIO_Pin_x);
	}
}

void vLEDAMode(uint16_t GPIO_Pin_x , emGpioStatusTdf State){
	if(State == LED_On){
		HAL_GPIO_WritePin(GPIOA,GPIO_Pin_x,GPIO_PIN_RESET);
	}
	else if(State == LED_Off){
		HAL_GPIO_WritePin(GPIOA,GPIO_Pin_x,GPIO_PIN_SET);
	}
	else if(State == LED_Toggle){
		HAL_GPIO_TogglePin(GPIOA,GPIO_Pin_x);
	}
}

