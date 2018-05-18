#ifndef __FT6236_H
#define __FT6236_H

#include "stm32f0xx.h"
#include "timer.h"

//RESET
#define				FT6236_RST_CLK								RCC_AHBPeriph_GPIOB
#define				FT6236_RST_PORT								GPIOB
#define				FT6236_RST_PIN								GPIO_Pin_0

#define 			FT6236_RST_SET								GPIO_SetBits(FT6236_RST_PORT, FT6236_RST_PIN)
#define				FT6236_RST_CLR								GPIO_ResetBits(FT6236_RST_PORT, FT6236_RST_PIN)

//SCL
#define				FT6236_SCL_CLK								RCC_AHBPeriph_GPIOB
#define				FT6236_SCL_PORT								GPIOB
#define				FT6236_SCL_PIN								GPIO_Pin_1

#define 			FT6236_SCL_SET								GPIO_SetBits(FT6236_SCL_PORT, FT6236_SCL_PIN)
#define				FT6236_SCL_CLR								GPIO_ResetBits(FT6236_SCL_PORT, FT6236_SCL_PIN)

//SDA
#define				FT6236_SDA_CLK								RCC_AHBPeriph_GPIOB
#define				FT6236_SDA_PORT								GPIOB
#define				FT6236_SDA_PIN								GPIO_Pin_10

#define 			FT6236_SDA_SET								GPIO_SetBits(FT6236_SDA_PORT, FT6236_SDA_PIN)
#define				FT6236_SDA_CLR								GPIO_ResetBits(FT6236_SDA_PORT, FT6236_SDA_PIN)
#define				FT6236_SDA_Read								GPIO_ReadInputDataBit(FT6236_SDA_PORT, FT6236_SDA_PIN)

//INT
#define				FT6236_INT_CLK								RCC_AHBPeriph_GPIOB
#define				FT6236_INT_PORT								GPIOB
#define				FT6236_INT_PIN								GPIO_Pin_11

#define				EXTIX_GPIO1										EXTI_PortSourceGPIOB
#define				EXTIX_Pin1											EXTI_PinSource11

#define				EXTIX_Line1										EXTI_Line11
#define				EXTIX_IRQn1										EXTI4_15_IRQn

//I2C读写命令	
#define FT_CMD_WR 							0X70    //写命令
#define FT_CMD_RD 							0X71		//读命令

//FT6236 部分寄存器定义 
#define FT_DEVIDE_MODE 					0x00   	//FT6236模式控制寄存器
#define FT_REG_NUM_FINGER	  		0x02		//触摸状态寄存器

#define FT_TP1_REG 							0X03	  //第一个触摸点数据地址
#define FT_TP2_REG 							0X09		//第二个触摸点数据地址
#define FT_TP3_REG 							0X0F		//第三个触摸点数据地址
#define FT_TP4_REG 							0X15		//第四个触摸点数据地址
#define FT_TP5_REG 							0X1B		//第五个触摸点数据地址  
 

#define	FT_ID_G_LIB_VERSION			0xA1    //版本		
#define FT_ID_G_MODE 						0xA4   	//FT6236中断模式控制寄存器
#define FT_ID_G_THGROUP					0x80   	//触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE		0x88   	//激活状态周期设置寄存器  
#define Chip_Vendor_ID          0xA3    //芯片ID(0x36)
#define ID_G_FT6236ID						0xA8		//0x11

#define TP_PRES_DOWN            0x80    //触屏被按下	
#define TP_COORD_UD             0x40    //触摸坐标更新标记
#define KEY_DOWN_FLAG						0x20		//按键标志位

//触摸点相关数据结构体定义
typedef struct			
{
	uint8_t TouchSta;	//触摸情况，b7:按下1/松开0; b6:0没有按键按下/1有按键按下;bit5:0按键没按下1:按键按下；bit4-bit0触摸点按下有效标志，有效为1，分别对应触摸点5-1；
	uint16_t x[5];		//支持5点触摸，需要使用5组坐标存储触摸点数据
	uint16_t y[5];
	
}TouchPointRefTypeDef;
extern TouchPointRefTypeDef TPR_Structure;

uint8_t FT6236_Write_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT6236_Read_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
void FT6236_Init(void);
void FT6236_Scan(void);

#endif
