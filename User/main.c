#include "stm32f10x.h"      
#include "OLED.h"
#include "PWM.h"
#include "Serial.h"
#include "string.h"

int main(void)
{
	OLED_Init();
	PWM_Init();
	Serial_Init();
	uint8_t test = 0;
	char target_String[] = "LEDON";
	

	while(1)
	{
		if(Serial_GetFlag())
		{
			if(strcmp(string,target_String) == 0)
			{
				PWM_SetCompare(60);
			}	
			else {test = 1;}
		}

		OLED_ShowNum(2,1,test,1);
		OLED_ShowString(1,1,string);
	}
}

