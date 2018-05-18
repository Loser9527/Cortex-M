#include "stm32f10x.h"
#include "systick.h"
#include "bsp_usart.h"
#include "bsp_spi.h"
#include "lcd_spi.h"
#include "GUI.h"
#include "GUIDEMO.h"


void System_Initializes(void)
{
	SysTick_Init();
	USART_Config();
	SPIx_Init();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	GUI_Init();
}
	
	
int main(void)
{	
	System_Initializes();

	GUI_SetColor(GUI_WHITE);
	
	GUI_DispStringAt("STemWin Speed test Demo",10,10);
	GUI_Delay(2000);
  
	GUIDEMO_Main();
}

