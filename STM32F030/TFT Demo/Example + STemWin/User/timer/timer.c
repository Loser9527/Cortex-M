/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： timer.c
  * @作者       ： strongerHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年10月18日
  * @摘要       ： 定时器源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-10-18 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "timer.h"


/************************************************
函数名称 ： TIMER_Initializes
功    能 ： 定时器初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* RCC时钟配置 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

  /* TIM14时基单元配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM14_PRESCALER_VALUE;       //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = TIM14_PERIOD_TIMING;            //定时周期
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

  /* 使能预分频值 */
  TIM_ARRPreloadConfig(TIM14, ENABLE);                               //使能重载值
}

/************************************************
函数名称 ： TIMDelay_N10us
功    能 ： 定时器延时N个10us(阻塞式)
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_N10us(uint16_t Times)
{
  TIM_Cmd(TIM14, ENABLE);                                            //启动定时器
  while(Times--)
  {
    while(TIM_GetFlagStatus(TIM14, TIM_FLAG_Update) == RESET);       //等待10us延时到
    TIM_ClearFlag(TIM14, TIM_FLAG_Update);                           //清除标志
  }
  TIM_Cmd(TIM14, DISABLE);                                           //关闭定时器
}

/************************************************
函数名称 ： TIMDelay_Nms
功    能 ： 定时器延时Nms
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_N10us(100);
  }
}

/************************************************
函数名称 ： TIMDelay_Ns
功    能 ： 定时器延时Ns
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Ns(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_Nms(1000);
  }
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
