#include "systick.h"

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while (1);
	}
}

///**
//  * @brief   ms��ʱ����,1msΪһ����λ
//  * @param  
//  *		@arg nTime: Delay_ms( 1 ) ��ʵ�ֵ���ʱΪ 1ms
//  * @retval  ��
//  */
//void Delay_ms(uint32_t nTime)
//{ 
//	TimingDelay = nTime;	

//	// ʹ�ܵδ�ʱ��  
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

//	while(TimingDelay != 0);
//}

///**
//  * @brief   s��ʱ����,1mΪһ����λ
//  * @param  
//  *		@arg nTime: Delay_s( 1 ) ��ʵ�ֵ���ʱΪ 1 s
//  * @retval  ��
//  */
//void Delay_s(uint32_t nTime)
//{ 
//	while(nTime--)
//	Delay_ms(1000);
//}

///**
//  * @brief  ��ȡ���ĳ���
//  * @param  ��
//  * @retval ��
//  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
//  */
//void TimingDelay_Decrement(void)
//{
//	if (TimingDelay != 0x00)
//	{ 
//		TimingDelay--;
//	}
//}
