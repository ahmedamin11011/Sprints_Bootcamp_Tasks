#include "SOS.h"
#include "registers.h"

void LED_1(void){
	PORTA_DATA ^= (1<<0);
}

void LED_2(void){
	PORTA_DATA ^= (1<<1);
}

void LED_3(void){
	PORTA_DATA ^= (1<<2);
	/* toggle only for 1 time */
	SOS_Delete_Task(LED_3);
}

int main(void){
	/*test*/
	PORTA_DIR =0xff;
	
	OS_ConfigType OS_Config = {TIMER0,1};
	OS_ConfigType *OS_Config_Ptr = &OS_Config;
	SOS_Init(OS_Config_Ptr);
	SOS_Create_Task(500, 1, LED_1);
	SOS_Create_Task(1000, 2, LED_2);
	SOS_Create_Task(200, 2, LED_3);
	while (1){	
	SOS_Run();
}
	}