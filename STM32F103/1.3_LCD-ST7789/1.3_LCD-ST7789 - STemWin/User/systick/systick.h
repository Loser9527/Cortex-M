#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(uint16_t nTime);
void Delay_ms(uint16_t nTime);
void Delay_s(uint16_t nTime);

#endif