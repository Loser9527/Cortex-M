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

//I2C��д����	
#define FT_CMD_WR 							0X70    //д����
#define FT_CMD_RD 							0X71		//������

//FT6236 ���ּĴ������� 
#define FT_DEVIDE_MODE 					0x00   	//FT6236ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER	  		0x02		//����״̬�Ĵ���

#define FT_TP1_REG 							0X03	  //��һ�����������ݵ�ַ
#define FT_TP2_REG 							0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 							0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 							0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 							0X1B		//��������������ݵ�ַ  
 

#define	FT_ID_G_LIB_VERSION			0xA1    //�汾		
#define FT_ID_G_MODE 						0xA4   	//FT6236�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP					0x80   	//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE		0x88   	//����״̬�������üĴ���  
#define Chip_Vendor_ID          0xA3    //оƬID(0x36)
#define ID_G_FT6236ID						0xA8		//0x11

#define TP_PRES_DOWN            0x80    //����������	
#define TP_COORD_UD             0x40    //����������±��
#define KEY_DOWN_FLAG						0x20		//������־λ

//������������ݽṹ�嶨��
typedef struct			
{
	uint8_t TouchSta;	//���������b7:����1/�ɿ�0; b6:0û�а�������/1�а�������;bit5:0����û����1:�������£�bit4-bit0�����㰴����Ч��־����ЧΪ1���ֱ��Ӧ������5-1��
	uint16_t x[5];		//֧��5�㴥������Ҫʹ��5������洢����������
	uint16_t y[5];
	
}TouchPointRefTypeDef;
extern TouchPointRefTypeDef TPR_Structure;

uint8_t FT6236_Write_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT6236_Read_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
void FT6236_Init(void);
void FT6236_Scan(void);

#endif
