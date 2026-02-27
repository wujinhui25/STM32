#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "MyRTC.h"
#include "OLED.h"
#include "MyRTCMode.h"

uint8_t My_Mode=1;
uint8_t	Timer_Runing=0;
uint32_t My_Time_keep=0;

void shift_My_Mode(void)
{
		uint8_t	KeyNumber=0;
		KeyNumber=Key_GetNum();
	
		if(KeyNumber==1)
		{
			 
			if(My_Mode==1)
			{
				
				OLED_Clear();          // 清屏
				My_Mode = 2;           // 切换到计时模式
				// 初始化计时模式显示
				OLED_ShowString(1,5,"TimeKeeping:");
				OLED_ShowString(2,5,"00:00:00");
				Timer_Runing = 0;      // 初始暂停计时
				My_Time_keep = 0;      // 计时值清零
				
			}
			else if(My_Mode==2)
			{
				OLED_Clear();
				My_Mode = 1;
				
				
			}
		}
		else if(KeyNumber==2 && My_Mode==2)
		{
			Timer_Runing=!Timer_Runing;
		}
		else if(KeyNumber==3 && My_Mode==2)
		{
			My_Mode=2;
			Timer_Runing=0;
			My_Time_keep=0;
			OLED_ShowString(2,5,"00:00:00");
		}	
			
		
		
}

void Timekeeping_Show(uint32_t Total_Time)
{
	uint8_t hour,min,sec;
	hour=Total_Time/3600;
	min=(Total_Time%3600)/60;
	sec=Total_Time%60;
//	OLED_ShowNum(2,5,hour,2);
//	OLED_ShowNum(2,8,min,2);
//	OLED_ShowNum(2,11,sec,2);
	// 显示时:分:秒（补0显示）
    OLED_ShowNum(2,5, hour, 2);
    OLED_ShowChar(2,7, ':'); // 补充冒号，格式更清晰
    OLED_ShowNum(2,8, min, 2);
    OLED_ShowChar(2,10, ':');
    OLED_ShowNum(2,11, sec, 2);
}
