#include "stm32f0xx.h"
#include "usart.h"
#include "timer.h"
#include "key.h"
#include "st7789.h"
#include "ft6236.h"


/************************************************
�������� �� System_Initializes
��    �� �� ϵͳ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
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

			if(TPR_Structure.TouchSta & TP_COORD_UD)		//�����а���
			{
				GPIOA->ODR ^= GPIO_Pin_15;
				TPR_Structure.TouchSta &= ~TP_COORD_UD;	//����
				FT6236_Scan();							//��ȡ��������
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			//ͨ������1��ӡ�������굽������
				printf("X����:\t%d\r\n",TPR_Structure.x[0]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
				printf("Y����:\t%d\r\n",TPR_Structure.y[0]);
				printf("\r\n");//���뻻��
				ST7789_DrawCircle(TPR_Structure.x[0], TPR_Structure.y[0], 3, 1);
			}
			if(TPR_Structure.TouchSta & KEY_DOWN_FLAG)	//�����а���
			{
				TPR_Structure.TouchSta &= ~KEY_DOWN_FLAG;	//����
				Address_Set(0,0);
				for(i=0;i<n;i++)
				{
					Write_ST7789_16Bit((WHITE>>8),(WHITE&0xff));
				}																					//����
			}
	}
	
}

