#include "stm32f10x.h"
#include "delay.h"
#include "bsp_spi_dma.h"
#include "lcd_spi.h"
#include "bsp_usart.h"
#include "bmp_data.h"


uint16_t color;

int main(void)
{	
	Delay_Init();
	SPIx_Init();
	DMA_Config();
	LCD_Init();
	USART_Config();
	
	while(1)
	{
		color = WHITE;
		LCD_Clear(&color);
		Delay_s(1);
		color = BLACK;
		LCD_Clear(&color);
		Delay_s(1);
		LCD_BMP((uint16_t *)gImage_lion);
		Delay_s(1);
	}
//	{
//		LCD_Clear(RED);
//		LCD_Clear(GREEN);
//		LCD_Clear(BLUE);
//		LCD_Clear(WHITE);
//		LCD_Clear(BLACK);
//		LCD_Clear(YELLOW);
//		LCD_Clear(ORANGE);
//		LCD_Clear(GRAY);
//		LCD_Clear(LGRAY);
//		LCD_Clear(DARKGRAY);
//		LCD_Clear(PORPO);
//		LCD_Clear(PINK);
//		LCD_Clear(GRAYBLUE);
//		LCD_Clear(LGRAYBLUE);
//		LCD_Clear(DARKBLUE);
//		LCD_Clear(LIGHTBLUE);
//	}
}

