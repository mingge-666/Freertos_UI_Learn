#include "Button_operation.h"
#include "Key.h"

emButtonCheckTdf KeyNum = emButtonStatus_None;
void Key_Tick(void){
	static uint8_t Count=0;
	static emButtonCheckTdf Currstate = emButtonStatus_None,Prevstate = emButtonStatus_None;
	Count++;
	if(Count>=20){
		Count = 0;
		Prevstate = Currstate;
		Currstate = Get_KeyState();
		if(Currstate == emButtonStatus_None && Prevstate != emButtonStatus_None){
			KeyNum = Prevstate;
		}
	}
}

emButtonCheckTdf Get_KeyNum(void){
	emButtonCheckTdf temp;
	temp = KeyNum;
	KeyNum = emButtonStatus_None;
	return temp;
}
