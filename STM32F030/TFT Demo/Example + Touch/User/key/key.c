#include "key.h"

//IO口初始化
void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(KEY1_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                 //输入模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           	     //上拉输入
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	
	
	
}

//外部中断初始化函数
void EXTIX2_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTIX_GPIO2, EXTIX_Pin2);

	EXTI_InitStructure.EXTI_Line = EXTIX_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	EXTI_ClearITPendingBit(EXTIX_Line2);    //清除LINEx上的中断标志位 
	NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn2;	//使能TOUCH_INT所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);  
}


void KEY_Init(void)
{
	KEY_GPIO_Init();
	EXTIX2_Init();
}

