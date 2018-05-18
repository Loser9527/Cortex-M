#include "stm32f0xx.h"
#include "systick.h"
#include "usart.h"
#include "timer.h"
#include "st7789.h"
#include "GUI.h"
#include "GUIDEMO.h"


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
	System_Initializes();
	
	while(1)
	{
			printf("\r\n ********** emwin速度测试程序*********** \r\n"); 

			GUI_SetColor(GUI_WHITE);   
			/* 显示测试 */
			GUI_DispStringAt(" emWin Speed test Demo",10,10);
			GUI_Delay(2000);


			//移植本程序时，注意要把启动文件中的栈空间设置大一点

			//emwin官方demo，修改guidemo.h文件中的宏可增加演示应用
			GUIDEMO_Main();
	}
}

