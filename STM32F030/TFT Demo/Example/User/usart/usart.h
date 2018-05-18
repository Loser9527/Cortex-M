/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� usart.h
  * @����       �� strongerHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��10��18��
  * @ժҪ       �� USARTͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __USART_H
#define __USART_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f0xx.h"
#include <stdio.h>


/* �������� ------------------------------------------------------------------*/
void USART_Initializes(void);
void USART1_SendByte(uint8_t Data);
void USART1_SendNByte(uint8_t *pData, uint16_t Length);
void USART1_Printf(uint8_t *String);


#endif /* _USART_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
