#ifndef __UI_WIDGET_BUTTON_H
#define __UI_WIDGET_BUTTON_H

#include <stdint.h>

typedef void vfButtonCallbackTdf(void);//定义一个函数类型

typedef enum{
	emButtonPressStatus_IsNotPressed  = 0,
	emButtonPressStatus_IsPressed     = 1,
}emButtonPressStatusTdf;//按下状态

typedef enum{
	emButtonSelectStatus_IsNotSelected  = 0,
	emButtonSelectStatus_IsSelected     = 1,
}emButtonSelectStatusTdf;//选择状态

typedef enum{
	emButtonSelectStatus_IsNotTriggered  = 0,
	emButtonSelectStatus_IsTriggered     = 1,
}emButtonTriggerStatusTdf;//触发状态

typedef enum{
	emButtonStatus_None  = 0,
	emButtonStatus_Up    = 1,
	emButtonStatus_Down  = 2,
	emButtonStatus_Enter = 3,
}emButtonCheckTdf;//按键状态


typedef struct{
	int16_t                    x;
	int16_t                    y;
	char                       *Data;
	uint8_t                    FontSize;
	emButtonSelectStatusTdf    emButtonSelectStatus;
	emButtonPressStatusTdf     emButtonPressStatusCurrent;
	emButtonPressStatusTdf     emButtonPressStatusLast;
	uint16_t                   uiPressedCount;
	uint16_t                   uiPressedCountThreshold;
	vfButtonCallbackTdf        *vpfCallback;
}stButtonTdf;//按键数据结构


#endif
