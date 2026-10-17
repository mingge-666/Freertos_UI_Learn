#ifndef __UI_WIDGET_SINGLE_LINE_H
#define __UI_WIDGET_SINGLE_LINE_H

#include <stdint.h>

typedef struct{//屏幕显示数据结构
	int16_t x;
	int16_t y;
	char    *Data;
	uint8_t FontSize;
}
SinglelineTDf;//单行显示

#endif

