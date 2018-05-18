#include "stm32f0xx.h"
#include "systick.h"
#include "usart.h"
#include "timer.h"
#include "st7789.h"
#include "GUI.h"
#include "GUIDEMO.h"


/************************************************
�������� �� System_Initializes
��    �� �� ϵͳ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
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
			printf("\r\n ********** emwin�ٶȲ��Գ���*********** \r\n"); 

			GUI_SetColor(GUI_WHITE);   
			/* ��ʾ���� */
			GUI_DispStringAt(" emWin Speed test Demo",10,10);
			GUI_Delay(2000);


			//��ֲ������ʱ��ע��Ҫ�������ļ��е�ջ�ռ����ô�һ��

			//emwin�ٷ�demo���޸�guidemo.h�ļ��еĺ��������ʾӦ��
			GUIDEMO_Main();
	}
}

