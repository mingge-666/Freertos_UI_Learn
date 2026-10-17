#include "freertos.h"
#include "task.h"
#include "OLED.h"
#include "ui_task.h"
#include "gpio.h"
#include "Key.h"
#include "ui_widget_single_line.h"
#include "ui_widget_button.h"
#include "page_led_control.h"
#include "Button_operation.h"
#include "LED_operation.h"



void vUITask(void){
	OLED_Init();
	while(1){
		vTest();

	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
		Key_Tick();
		LED_Tick();
    }
}
	
