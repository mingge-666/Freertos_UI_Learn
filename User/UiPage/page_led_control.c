#include "page_led_control.h"
#include "ui_widget_single_line.h"
#include "ui_widget_button.h"
#include "OLED.h"
#include "LED.h"
#include "string.h"
#include "gpio.h"
#include "Button_operation.h"


static char s_acLED0[] = "LED0";


static SinglelineTDf s_SinglelineTestLED0 = {//文本显示位置
	.x = 64-((sizeof(s_acLED0)/sizeof(s_acLED0[0])-1)*OLED_8X16)/2,//OLED屏幕长128个像素
	.y = 0,
	.Data = s_acLED0,
	.FontSize = OLED_8X16,
};


static SinglelineTDf *s_apSinglelineTest[] = {//指针数组（用来存放指针的数组）
	&s_SinglelineTestLED0,

};



void vButtonCallback_On(void);
void vButtonCallback_Off(void);
void vButtonCallback_Toggle(void);


static char s_acOn[] = "On";
static char s_acOff[] = "Off";
static char s_acToggle[] = "Toggle";

static stButtonTdf s_stButton_On = {
	.x = 20,
	.y = 1.2 * 16,
	.Data = s_acOn,
	.FontSize = OLED_8X16,
	.emButtonSelectStatus = emButtonSelectStatus_IsSelected,
	.emButtonPressStatusCurrent = emButtonPressStatus_IsNotPressed,
	.emButtonPressStatusLast    = emButtonPressStatus_IsNotPressed,
	.uiPressedCount = 0,
	.uiPressedCountThreshold = 5,
	.vpfCallback = vButtonCallback_On,
};//在OLED屏幕的On显示方式

static stButtonTdf s_stButton_Off = {
	.x = 80,
	.y = 1.2 * 16,
	.Data = s_acOff,
	.FontSize = OLED_8X16,
	.emButtonSelectStatus = emButtonSelectStatus_IsNotSelected,
	.emButtonPressStatusCurrent = emButtonPressStatus_IsNotPressed,
	.emButtonPressStatusLast    = emButtonPressStatus_IsNotPressed,
	.uiPressedCount = 0,
	.uiPressedCountThreshold = 5,
	.vpfCallback = vButtonCallback_Off,
};//在OLED屏幕的Off显示方式

static stButtonTdf s_stButton_Toggle = {
	.x = 20,
	.y = 2.5 * 16,
	.Data = s_acToggle,
	.FontSize = OLED_8X16,
	.emButtonSelectStatus = emButtonSelectStatus_IsNotSelected,
	.emButtonPressStatusCurrent = emButtonPressStatus_IsNotPressed,
	.emButtonPressStatusLast    = emButtonPressStatus_IsNotPressed,
	.uiPressedCount = 0,
	.uiPressedCountThreshold = 5,
	.vpfCallback = vButtonCallback_Toggle,
};//在OLED屏幕的Toggle显示方式

static stButtonTdf *s_apstButton[] = {
	&s_stButton_On,
	&s_stButton_Off,
	&s_stButton_Toggle,
};//指针数组用来存放各种按键模式在OLED上的显示数据的结构体

void vShowAllSingleLineTest(void){
	uint16_t i;
	for(i = 0;i<sizeof(s_apSinglelineTest)/sizeof(s_apSinglelineTest[0]);i++){
		OLED_ShowString(s_apSinglelineTest[i]->x,
						s_apSinglelineTest[i]->y,
						s_apSinglelineTest[i]->Data,
						s_apSinglelineTest[i]->FontSize
		);
	}
}//OLED标题文本显示

void vShowButtonAll(void){
	uint16_t i;
	for(i = 0;i<sizeof(s_apstButton)/sizeof(s_apstButton[0]);i++){
		OLED_ShowString(s_apstButton[i]->x,
						s_apstButton[i]->y,
						s_apstButton[i]->Data,
						s_apstButton[i]->FontSize
		);
		if(s_apstButton[i]->emButtonPressStatusCurrent){//被按下后反色显示
			OLED_ReverseArea(s_apstButton[i]->x,
							  s_apstButton[i]->y,
							  strlen(s_apstButton[i]->Data)*s_apstButton[i]->FontSize,
							  s_apstButton[i]->FontSize*2
							 );
		}

		if(s_apstButton[i]->emButtonSelectStatus){//被选中后上方显示横线
			OLED_DrawLine(s_apstButton[i]->x,
						  s_apstButton[i]->y,
						  s_apstButton[i]->x+strlen(s_apstButton[i]->Data)*s_apstButton[i]->FontSize,
			              s_apstButton[i]->y
			              );
		}
				
	}
	
}//OLED按键文本显示



//按键扫描函数，当按键按下，是目标反色一段时间
emButtonTriggerStatusTdf vButtonCallbackScan(stButtonTdf *pstButton){
	emButtonTriggerStatusTdf ButtonTriggerStatus = emButtonSelectStatus_IsNotTriggered;
	if(pstButton->emButtonPressStatusCurrent == emButtonPressStatus_IsPressed &&
		pstButton->emButtonPressStatusLast == emButtonPressStatus_IsNotPressed){
			ButtonTriggerStatus = emButtonSelectStatus_IsTriggered;//触发
			s_stButton_On.uiPressedCount = 0;
		}
	pstButton->uiPressedCount++;//反色限时
	if(pstButton->uiPressedCount>pstButton->uiPressedCountThreshold){
		pstButton->uiPressedCount = 0;
		pstButton->emButtonPressStatusCurrent = emButtonPressStatus_IsNotPressed;
	}
	pstButton->emButtonPressStatusLast = pstButton->emButtonPressStatusCurrent;
	return ButtonTriggerStatus;//返回触发模式
}

void vButtonCallback_On(void){//按键回调函数，执行相应的操作
	if(vButtonCallbackScan(&s_stButton_On) == emButtonSelectStatus_IsTriggered){
		vLEDCMode(GPIO_PIN_13,LED_On);
	}
}

void vButtonCallback_Off(void){
	if(vButtonCallbackScan(&s_stButton_Off) == emButtonSelectStatus_IsTriggered){
		vLEDCMode(GPIO_PIN_13,LED_Off);
	}
}

void vButtonCallback_Toggle(void){
	if(vButtonCallbackScan(&s_stButton_Toggle) == emButtonSelectStatus_IsTriggered){
		vLEDCMode(GPIO_PIN_13,LED_Toggle);
	}
}

void vButtonCallbackAll(void){//轮询执行回调函数
	uint16_t i;
	for(i = 0; i<sizeof(s_apstButton)/sizeof(s_apstButton[0]);i++){
		if(s_apstButton[i]->vpfCallback == 0){
			continue;
		}
		s_apstButton[i]->vpfCallback();
	}
}

void cCheckButtonStatus(void){//检查按键状态。实时显示OLED
	static uint8_t s_ucSelectIndex = 0;
	emButtonCheckTdf emButtonCheck = emButtonStatus_None;
	emButtonCheck = Get_KeyNum();
	if(emButtonCheck == emButtonStatus_Up){
		s_apstButton[s_ucSelectIndex]->emButtonSelectStatus = emButtonSelectStatus_IsNotSelected;
		s_ucSelectIndex -- ;
		if(s_ucSelectIndex > sizeof(s_apstButton)/sizeof(s_apstButton[0])-1){
			s_ucSelectIndex = sizeof(s_apstButton)/sizeof(s_apstButton[0])-1;
		}
		s_apstButton[s_ucSelectIndex]->emButtonSelectStatus = emButtonSelectStatus_IsSelected;
	}
	if(emButtonCheck == emButtonStatus_Down){
		s_apstButton[s_ucSelectIndex]->emButtonSelectStatus = emButtonSelectStatus_IsNotSelected;
		s_ucSelectIndex ++ ;
		if(s_ucSelectIndex > sizeof(s_apstButton)/sizeof(s_apstButton[0])-1){
			s_ucSelectIndex = 0;
		}
		s_apstButton[s_ucSelectIndex]->emButtonSelectStatus = emButtonSelectStatus_IsSelected;
	}
	if(emButtonCheck == emButtonStatus_Enter){
		s_apstButton[s_ucSelectIndex]->emButtonPressStatusCurrent = emButtonPressStatus_IsPressed;
		
	}
}

void vTest(void){
	OLED_Clear();
	vShowAllSingleLineTest();
	vShowButtonAll();
	vButtonCallbackAll();
	cCheckButtonStatus();
	OLED_Update();

}

