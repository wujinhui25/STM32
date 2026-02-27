#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"
#include "time.h"
#include "MyRTCMode.h"
#include "Key.h"
/*
void RCC_LSEConfig(uint8_t RCC_LSE); //配置LSE外部低速时钟
void RCC_LSICmd(FunctionalState NewState);  //配置LSI内部低速时钟
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource); //配置（选择）RTCCLK的时钟源
void RCC_RTCCLKCmd(FunctionalState NewState); //启动(使能)RTCCLK
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
*/
/*
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG); //获取RCC标志位，启动完成
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);
*/

/*
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState); //配置中断输出
void RTC_EnterConfigMode(void); //进入配置模式
void RTC_ExitConfigMode(void); //退出配置模式CNF位清零
uint32_t  RTC_GetCounter(void); //获取CNT计数器的值
void RTC_SetCounter(uint32_t CounterValue); //写入CNT计数器的值
void RTC_SetPrescaler(uint32_t PrescalerValue); //写入预分频器，配置分频系数
void RTC_SetAlarm(uint32_t AlarmValue); //写入闹钟值
uint32_t  RTC_GetDivider(void); //读取预分频器中DIV余数寄存器
void RTC_WaitForLastTask(void); //等待前一次写入操作结束（RTOFF被置1）
void RTC_WaitForSynchro(void); //等待同步（清除RSF标志位并循环等待直到RSF为1）
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG); 
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);
*/

extern uint16_t MyRTC_Time[7];

int main (void)
{
	Key_Init();
	MyRTC_Init();
	OLED_Init();
	OLED_Clear();     // 初始化清屏

    // 初始化默认显示（模式1：实时时钟）
    OLED_ShowString(1,7,"DATE");    
    OLED_ShowString(2,5,"xxxx-xx-xx");
    OLED_ShowString(3,7,"Time");    
    OLED_ShowString(4,5,"xx:xx:xx");
    OLED_ShowString(3,13,"Week");
	
//	OLED_ShowString(1,7,"DATE");
//	OLED_ShowString(2,5,"xxxx-xx-xx");
//	OLED_ShowString(3,7,"Time");
//	OLED_ShowString(4,5,"xx:xx:xx");
//	OLED_ShowString(3,13,"Week");

	
	while(1)
	{
		
//		ReadMyRTC_time();
//		OLED_ShowNum(2,5,MyRTC_Time[0],4);
//		OLED_ShowNum(2,10,MyRTC_Time[1],2);
//		OLED_ShowNum(2,13,MyRTC_Time[2],2);
//		OLED_ShowNum(4,5,MyRTC_Time[3],2);
//		OLED_ShowNum(4,8,MyRTC_Time[4],2);
//		OLED_ShowNum(4,11,MyRTC_Time[5],2);
//		OLED_ShowNum(4,15,MyRTC_Time[6],2);
		shift_My_Mode();
		if(My_Mode == 1)
		{
			ReadMyRTC_time();
			OLED_ShowNum(2,5,MyRTC_Time[0],4);
			OLED_ShowNum(2,10,MyRTC_Time[1],2);
			OLED_ShowNum(2,13,MyRTC_Time[2],2);
			OLED_ShowNum(4,5,MyRTC_Time[3],2);
			OLED_ShowNum(4,8,MyRTC_Time[4],2);
			OLED_ShowNum(4,11,MyRTC_Time[5],2);
			OLED_ShowNum(4,15,MyRTC_Time[6],2);
			Delay_ms(200);
		}
		else if(My_Mode==2)
		{
			if(Timer_Runing)
			{
				My_Time_keep++;
				Timekeeping_Show(My_Time_keep);
				Delay_ms(1000);
			}
			Delay_ms(200);
		}
	}
	
}



