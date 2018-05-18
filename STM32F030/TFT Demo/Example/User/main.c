#include "stm32f0xx.h"
#include "usart.h"
#include "timer.h"
#include "st7789.h"


/************************************************
函数名称 ： System_Initializes
功    能 ： 系统初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void System_Initializes(void)
{
  USART_Initializes();
  TIMER_Initializes();
	ST7789_Init();
}


int main(void)
{
	uint32_t i;
	
	#if TFT2_0
	uint32_t n = 76800;
	#else
	uint16_t n = 57600;
	#endif	
	
	System_Initializes();
	
	while(1)
	{
    Address_Set(0,0);
		for(i=0;i<n;i++)
		{
			Write_ST7789_16Bit((RED>>8),(RED&0xff));
		}
		Address_Set(0,0);
		for(i=0;i<n;i++)
		{
			Write_ST7789_16Bit((GREEN>>8),(GREEN&0xff));
		}
		Address_Set(0,0);
		for(i=0;i<n;i++)
		{
			Write_ST7789_16Bit((BLUE>>8),(BLUE&0xff));
		}
		Address_Set(0,0);
		for(i=0;i<n;i++)
		{
			Write_ST7789_16Bit((WHITE>>8),(WHITE&0xff));
		}
		Address_Set(0,0);
		for(i=0;i<n;i++)
		{
			Write_ST7789_16Bit((BLACK>>8),(BLACK&0xff));
		}
	}
	
}

