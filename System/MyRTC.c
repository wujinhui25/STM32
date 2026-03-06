#include "stm32f10x.h"                  // Device header
#include "time.h"

void SetMyRTC_time(void);
//uint16_t x;
uint16_t MyRTC_Time[] = {2026,2,25,23,59,55,3};

void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE); //使能PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE); //使能BKP
	
	PWR_BackupAccessCmd(ENABLE);// 启用（或禁用）对 RTC 和备份寄存器的访问。
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xAA55)
	{
		RCC_LSEConfig(RCC_LSE_ON); //配置LSE振荡器（外部低速时钟）
		while(RCC_GetFlagStatus( RCC_FLAG_LSERDY) != SET); //获取标志位；说明LSE振荡器就绪
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//配置LSE为（选择）RTCCLK的时钟源
		RCC_RTCCLKCmd(ENABLE); //启动(使能)RTCCLK
		
		RTC_WaitForSynchro(); //等待同步（清除RSF标志位并循环等待直到RSF为1）
		RTC_WaitForLastTask(); //等待上一次写入操作结束（RTOFF被置1）

		RTC_SetPrescaler(32768-1); //写入预分频器，配置分频系数
		RTC_WaitForLastTask();

		SetMyRTC_time(); //写入CNT计数器的值
		RTC_WaitForLastTask();
		
		BKP_WriteBackupRegister(BKP_DR1,0xAA55);
		}
		else
		{
		RTC_WaitForSynchro(); //等待同步（清除RSF标志位并循环等待直到RSF为1）
		RTC_WaitForLastTask(); //等待上一次写入操作结束（RTOFF被置1）
		}
	
}

void SetMyRTC_time(void)
{
	time_t time_cnt;
	struct tm time_date;
	time_date.tm_year = MyRTC_Time[0]-1900;
	time_date.tm_mon = MyRTC_Time[1]-1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	time_date.tm_wday = MyRTC_Time[6]-1;
	
	time_cnt = mktime(&time_date)-8*60*60; //获取匹配的时间戳（CNT秒数）
	
	RTC_SetCounter(time_cnt);//写入CNT计数器的值
	RTC_WaitForLastTask();
	
}


void ReadMyRTC_time(void)
{
	time_t time_cnt;
	struct tm time_date;
	time_cnt=RTC_GetCounter()+8*60*60;//转化为北京时间，且保证时间戳匹配
	time_date = *localtime(&time_cnt); //将读到的计数器CNT值转化为结构体的对应值
	
	/*将对读到的应值 写入数组*/
	MyRTC_Time[0] = time_date.tm_year+1900; 
	MyRTC_Time[1] = time_date.tm_mon+1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
	MyRTC_Time[6] = time_date.tm_wday;
}

