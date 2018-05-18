#ifndef __ST7789_H
#define __ST7789_H

#include "stm32f0xx.h"

#define			TFT2_0			 1

#define     RED          0xF800	  //红色
#define     GREEN        0x07E0	  //绿色
#define     BLUE         0x001F	  //蓝色
#define     WHITE        0xFFFF	  //白色
#define     BLACK        0x0000	  //黑色
#define     YELLOW       0xFFE0	  //黄色
#define     ORANGE       0xFC08	  //橙色
#define     GRAY  	     0x8430   //灰色
#define     LGRAY        0xC618	  //浅灰色
#define     DARKGRAY     0x8410	  //深灰色
#define     PORPO        0x801F	  //紫色
#define     PINK         0xF81F	  //粉红色
#define     GRAYBLUE     0x5458   //灰蓝色
#define     LGRAYBLUE    0xA651   //浅灰蓝色
#define     DARKBLUE     0x01CF	  //深灰蓝色
#define 		LIGHTBLUE    0x7D7C	  //浅蓝色

//LED_DRV
#define				ST7789_LED_CLK								RCC_AHBPeriph_GPIOA
#define				ST7789_LED_PORT								GPIOA
#define				ST7789_LED_PIN								GPIO_Pin_15

#define 			ST7789_LED_ON									GPIO_SetBits(ST7789_LED_PORT, ST7789_LED_PIN)
#define				ST7789_LED_OFF								GPIO_ResetBits(ST7789_LED_PORT, ST7789_LED_PIN)
	

//RESET
#define				ST7789_RST_CLK								RCC_AHBPeriph_GPIOB
#define				ST7789_RST_PORT								GPIOB
#define				ST7789_RST_PIN								GPIO_Pin_3

#define 			ST7789_RST_HIGH								GPIO_SetBits(ST7789_RST_PORT, ST7789_RST_PIN)
#define				ST7789_RST_LOW								GPIO_ResetBits(ST7789_RST_PORT, ST7789_RST_PIN)


//CS
#define				ST7789_CS_CLK									RCC_AHBPeriph_GPIOB
#define				ST7789_CS_PORT								GPIOB
#define				ST7789_CS_PIN									GPIO_Pin_4

#define 			ST7789_CS_HIGH								GPIO_SetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define				ST7789_CS_LOW									GPIO_ResetBits(ST7789_CS_PORT, ST7789_CS_PIN)


//DC
#define				ST7789_DC_CLK									RCC_AHBPeriph_GPIOB
#define				ST7789_DC_PORT								GPIOB
#define				ST7789_DC_PIN									GPIO_Pin_5

#define 			ST7789_DC_HIGH								GPIO_SetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define				ST7789_DC_LOW									GPIO_ResetBits(ST7789_DC_PORT, ST7789_DC_PIN)


//WR
#define				ST7789_WR_CLK									RCC_AHBPeriph_GPIOB
#define				ST7789_WR_PORT								GPIOB
#define				ST7789_WR_PIN									GPIO_Pin_6

#define 			ST7789_WR_HIGH								GPIO_SetBits(ST7789_WR_PORT, ST7789_WR_PIN)
#define				ST7789_WR_LOW									GPIO_ResetBits(ST7789_WR_PORT, ST7789_WR_PIN)


//RD
#define				ST7789_RD_CLK									RCC_AHBPeriph_GPIOB
#define				ST7789_RD_PORT								GPIOB
#define				ST7789_RD_PIN									GPIO_Pin_7

#define 			ST7789_RD_HIGH								GPIO_SetBits(ST7789_RD_PORT, ST7789_RD_PIN)
#define				ST7789_RD_LOW									GPIO_ResetBits(ST7789_RD_PORT, ST7789_RD_PIN)


#define 			DATA_OUT(x)										GPIOA->BSRR=(((uint32_t)(uint8_t)~(x))<<16)|((uint32_t)(uint8_t)(x));
#define 			DATA_READ() 									(GPIOA->IDR);


void ST7789_Init(void);
void Write_ST7789_Reg(uint8_t data);
void Write_ST7789_Data(uint8_t data);
uint8_t Read_ST7789_Data(void);
void Address_Set(uint16_t x,uint16_t y);
void Write_ST7789_16Bit(uint8_t hibyte,uint8_t lowbyte);
void Write_ST7789_Point(uint16_t x,uint16_t y,uint16_t color);
uint32_t Read_ST7789_Point(uint16_t x,uint16_t y);
void Fill_ST7789(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend, uint16_t color);


#endif
