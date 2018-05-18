/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� timer.c
  * @����       �� strongerHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��10��18��
  * @ժҪ       �� ��ʱ��Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-10-18 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "timer.h"


/************************************************
�������� �� TIMER_Initializes
��    �� �� ��ʱ����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* RCCʱ������ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

  /* TIM14ʱ����Ԫ���� */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM14_PRESCALER_VALUE;       //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = TIM14_PERIOD_TIMING;            //��ʱ����
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

  /* ʹ��Ԥ��Ƶֵ */
  TIM_ARRPreloadConfig(TIM14, ENABLE);                               //ʹ������ֵ
}

/************************************************
�������� �� TIMDelay_N10us
��    �� �� ��ʱ����ʱN��10us(����ʽ)
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_N10us(uint16_t Times)
{
  TIM_Cmd(TIM14, ENABLE);                                            //������ʱ��
  while(Times--)
  {
    while(TIM_GetFlagStatus(TIM14, TIM_FLAG_Update) == RESET);       //�ȴ�10us��ʱ��
    TIM_ClearFlag(TIM14, TIM_FLAG_Update);                           //�����־
  }
  TIM_Cmd(TIM14, DISABLE);                                           //�رն�ʱ��
}

/************************************************
�������� �� TIMDelay_Nms
��    �� �� ��ʱ����ʱNms
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_N10us(100);
  }
}

/************************************************
�������� �� TIMDelay_Ns
��    �� �� ��ʱ����ʱNs
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_Ns(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_Nms(1000);
  }
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
