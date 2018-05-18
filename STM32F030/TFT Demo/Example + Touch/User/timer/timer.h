/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� timer.h
  * @����       �� strongerHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��10��18��
  * @ժҪ       �� ��ʱ��ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f0xx.h"


/* �궨�� --------------------------------------------------------------------*/
#define TIM14_COUNTER_CLOCK        1000000                 //����ʱ��(1M��/��)                                                          //Ԥ��Ƶֵ
#define TIM14_PRESCALER_VALUE      (SystemCoreClock/TIM14_COUNTER_CLOCK - 1)
#define TIM14_PERIOD_TIMING        (10 - 1)                //��ʱ���ڣ�����ڼ���ʱ��:1���� = 1����ʱ�ӣ�

/* �������� ------------------------------------------------------------------*/
void TIMER_Initializes(void);

void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);
void TIMDelay_Ns(uint16_t Times);


#endif /* _TIMER_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
