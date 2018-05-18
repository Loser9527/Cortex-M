#include "systick.h"

volatile uint16_t TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms
	 * SystemFrequency / 100000	 10us
	 * SystemFrequency / 1000000 1us
	 */
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while (1);
	}
}

void Delay_us(uint16_t nTime)
{
	uint8_t i;
	while(nTime--)
	{
		i = 12;
		while(i--);
	}
}

void Delay_ms(uint16_t nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void Delay_s(uint16_t nTime)
{
	while(nTime--)
	Delay_ms(1000);
}
