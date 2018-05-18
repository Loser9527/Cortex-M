#include "key.h"

//IO�ڳ�ʼ��
void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(KEY1_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;         					   //����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                 //����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           	     //��������
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	
	
	
}

//�ⲿ�жϳ�ʼ������
void EXTIX2_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTIX_GPIO2, EXTIX_Pin2);

	EXTI_InitStructure.EXTI_Line = EXTIX_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	EXTI_ClearITPendingBit(EXTIX_Line2);    //���LINEx�ϵ��жϱ�־λ 
	NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn2;	//ʹ��TOUCH_INT���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  
}


void KEY_Init(void)
{
	KEY_GPIO_Init();
	EXTIX2_Init();
}

