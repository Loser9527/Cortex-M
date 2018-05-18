#ifndef __KEY_H
#define __KEY_H

#include "stm32f0xx.h"

//KEY1
#define				KEY1_CLK								RCC_AHBPeriph_GPIOB
#define				KEY1_PORT								GPIOB
#define				KEY1_PIN								GPIO_Pin_8

#define				EXTIX_GPIO2							EXTI_PortSourceGPIOB
#define				EXTIX_Pin2							EXTI_PinSource8

#define				EXTIX_Line2							EXTI_Line8
#define				EXTIX_IRQn2							EXTI4_15_IRQn


void KEY_Init(void);

#endif
