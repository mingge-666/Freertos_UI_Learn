#include "gpio.h" 
#include "Key.h"
#include "ui_widget_button.h"

emButtonCheckTdf Get_KeyState(void){
	
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)==0){
		return emButtonStatus_Up;
	}
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)==0){
		return emButtonStatus_Down;
	}
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){
		return emButtonStatus_Enter;
	}
//	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){
//		return 4;
//	}
	return emButtonStatus_None;
}

