#include "stm32f0xx.h"
#include "systick.h"
#include "usart.h"
#include "timer.h"
#include "st7789.h"
#include "GUI.h"


/************************************************
函数名称 ： System_Initializes
功    能 ： 系统初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void System_Initializes(void)
{
	SysTick_Init();
  USART_Initializes();
  TIMER_Initializes();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	GUI_Init();
}


int main(void)
{
	uint16_t i;
//	uint32_t color1,color2;
		
	System_Initializes();	
	

//	GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
//	GUI_FillCircle(120, 60, 40);
//	GUI_SetDrawMode(GUI_DRAWMODE_XOR);
//	GUI_FillCircle(140, 80, 40);
	
//	GUI_DrawGradientH(0, 0, 239, 99, 0x0000FF, 0x00FFFF);	
//	color1 = GUI_GetPixelIndex(120, 40);
//	color2 = GUI_GetPixelIndex(239, 99);
//	GUI_DrawGradientH(0, 100, 239, 199, color1, color2);	
	
	GUI_SetFont(&GUI_Font8x16);
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_SetPenSize(10);
	GUI_SetColor(GUI_RED);
	GUI_DrawLine(80, 10, 240, 90);
	GUI_DrawLine(80, 90, 240, 10);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("GUI_TM_NORMAL" , 160, 10);
	GUI_SetTextMode(GUI_TM_REV);
	GUI_DispStringHCenterAt("GUI_TM_REV" , 160, 26);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_DispStringHCenterAt("GUI_TM_TRANS" , 160, 42);
	GUI_SetTextMode(GUI_TM_XOR);
	GUI_DispStringHCenterAt("GUI_TM_XOR" , 160, 58);
	GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_REV);
	GUI_DispStringHCenterAt("GUI_TM_TRANS | GUI_TM_REV", 160, 74);		

	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_NORMAL);
	while(1)
	{
			GUI_DispDecAt(i++,10,50,4);
			if(i>9999) i=0;
//			if(!i)
//			{
//				printf("color1 = 0x%08x\n",color1);
//				printf("color2 = 0x%08x\n",color2);
//			}
	}
	
}

