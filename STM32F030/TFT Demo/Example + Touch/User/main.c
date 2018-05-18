#include "stm32f0xx.h"
#include "usart.h"
#include "timer.h"
#include "key.h"
#include "st7789.h"
#include "ft6236.h"


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
	FT6236_Init();
	KEY_Init();
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
	
	Address_Set(0,0);
	for(i=0;i<n;i++)
	{
		Write_ST7789_16Bit((WHITE>>8),(WHITE&0xff));
	}	
	
	while(1)
	{
//    Address_Set(0,0);
//		for(i=0;i<n;i++)
//		{
//			Write_ST7789_16Bit((RED>>8),(RED&0xff));
//		}
//		Address_Set(0,0);
//		for(i=0;i<n;i++)
//		{
//			Write_ST7789_16Bit((GREEN>>8),(GREEN&0xff));
//		}
//		Address_Set(0,0);
//		for(i=0;i<n;i++)
//		{
//			Write_ST7789_16Bit((BLUE>>8),(BLUE&0xff));
//		}
//		Address_Set(0,0);
//		for(i=0;i<n;i++)
//		{
//			Write_ST7789_16Bit((WHITE>>8),(WHITE&0xff));
//		}
//		Address_Set(0,0);
//		for(i=0;i<n;i++)
//		{
//			Write_ST7789_16Bit((BLACK>>8),(BLACK&0xff));
//		}

			if(TPR_Structure.TouchSta & TP_COORD_UD)		//触摸有按下
			{
				GPIOA->ODR ^= GPIO_Pin_15;
				TPR_Structure.TouchSta &= ~TP_COORD_UD;	//清标记
				FT6236_Scan();							//读取触摸坐标
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			//通过串口1打印触摸坐标到电脑上
				printf("X坐标:\t%d\r\n",TPR_Structure.x[0]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
				printf("Y坐标:\t%d\r\n",TPR_Structure.y[0]);
				printf("\r\n");//插入换行
				ST7789_DrawCircle(TPR_Structure.x[0], TPR_Structure.y[0], 3, 1);
			}
			if(TPR_Structure.TouchSta & KEY_DOWN_FLAG)	//按键有按下
			{
				TPR_Structure.TouchSta &= ~KEY_DOWN_FLAG;	//清标记
				Address_Set(0,0);
				for(i=0;i<n;i++)
				{
					Write_ST7789_16Bit((WHITE>>8),(WHITE&0xff));
				}																					//清屏
			}
	}
	
}

