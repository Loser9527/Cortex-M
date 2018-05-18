#include "stm32f10x.h"
#include "delay.h"
#include "bsp_spi.h"
#include "lcd_spi.h"
#include "bsp_usart.h"



int main(void)
{	
	Delay_Init();
	SPIx_Init();
	LCD_Init();
	USART_Config();
	LCD_Usart_Data();
	
	while(1)
	{
		printf("初始化成功，等待传入数据\n");
		Delay_s(3);
	}
}

