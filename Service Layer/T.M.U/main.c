#include "TMU.h"
#include "Dio.h"

uint8 g_closeTask =0;
void Test_1(void){

	//g_closeTask++;
	PORTC_DATA^=0x01;
}

void Test_2(void){

	PORTC_DATA^=0x02;
}

void Test_3(void){


	PORTC_DATA^=0x04;
}

int main(void)
{
	
	TMU_ConfigType TMU_Config = {TIMER0,1};
    TMU_ConfigType *TMU_ConfigType_Ptr=&TMU_Config;
	PORTC_DIR=0xFF;
	
PORTC_DATA=0x00;
	
	TMU_Init(&TMU_Config);

	TMU_Start_Timer(500,Test_1,PERIODIC);
	TMU_Start_Timer(1000,Test_2,PERIODIC);
	TMU_Start_Timer(1500,Test_3,PERIODIC);


	while(1)
	{
		TMU_Dispatch();
		/*if(g_closeTask == 10){
			TMU_Stop_Timer(Test_1);
		}*/
	}
	}


