/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "timer.h"
#include "usart.h"
#include "ft6236.h"
#include "key.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/************************************************
�������� �� USART1_IRQHandler
��    �� �� USART1�ж�
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART1_SendByte((uint8_t)(USART1->RDR));     //���ͽ��յ����ַ�����
  }
}


/*
�ж��ⲿ�ж�״̬�Լ�����ⲿ״̬��־λ�ĺ��� EXTI_GetFlagStatus �� EXTI_ClearFlag��
�� EXTI_GetITStatus �����л����ж������ж��Ƿ�ʹ�ܣ�ʹ���˲�ȥ�ж��жϱ�־λ����
EXTI_GetFlagStatus ֱ�������ж�״̬��־λ��
*/
void EXTI4_15_IRQHandler(void)
{
	TIMDelay_N10us(1);
//	GPIOA->ODR ^= GPIO_Pin_15;
	if(GPIO_ReadInputDataBit(FT6236_INT_PORT, FT6236_INT_PIN) == RESET)	   	
	TPR_Structure.TouchSta |= TP_COORD_UD;		//���������и���
  EXTI_ClearFlag(EXTIX_Line1); 							//��� LINEx �ϵ��жϱ�־λ
	TIMDelay_N10us(1000);
	if(GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN) == RESET)
	TPR_Structure.TouchSta |= KEY_DOWN_FLAG;		//������־λ
	EXTI_ClearFlag(EXTIX_Line2); 							//��� LINEx �ϵ��жϱ�־λ	
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
