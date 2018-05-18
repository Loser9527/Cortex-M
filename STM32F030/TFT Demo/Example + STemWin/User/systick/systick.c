#include "systick.h"

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while (1);
	}
}

///**
//  * @brief   ms延时程序,1ms为一个单位
//  * @param  
//  *		@arg nTime: Delay_ms( 1 ) 则实现的延时为 1ms
//  * @retval  无
//  */
//void Delay_ms(uint32_t nTime)
//{ 
//	TimingDelay = nTime;	

//	// 使能滴答定时器  
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

//	while(TimingDelay != 0);
//}

///**
//  * @brief   s延时程序,1m为一个单位
//  * @param  
//  *		@arg nTime: Delay_s( 1 ) 则实现的延时为 1 s
//  * @retval  无
//  */
//void Delay_s(uint32_t nTime)
//{ 
//	while(nTime--)
//	Delay_ms(1000);
//}

///**
//  * @brief  获取节拍程序
//  * @param  无
//  * @retval 无
//  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
//  */
//void TimingDelay_Decrement(void)
//{
//	if (TimingDelay != 0x00)
//	{ 
//		TimingDelay--;
//	}
//}
