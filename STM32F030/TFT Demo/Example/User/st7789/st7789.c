#include "st7789.h"
#include "timer.h"

void ST7789_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd( ST7789_LED_CLK | ST7789_RST_CLK |
												 ST7789_CS_CLK | ST7789_DC_CLK |
												 ST7789_WR_CLK | ST7789_RD_CLK ,
												 ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = ST7789_LED_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //高速
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽输出
  GPIO_Init(ST7789_LED_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ST7789_RST_PIN;         					   //引脚	
	GPIO_Init(ST7789_RST_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ST7789_CS_PIN;         					   //引脚	
	GPIO_Init(ST7789_CS_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ST7789_DC_PIN;         					   //引脚	
	GPIO_Init(ST7789_DC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ST7789_WR_PIN;         					   //引脚	
	GPIO_Init(ST7789_WR_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ST7789_RD_PIN;         					   //引脚	
	GPIO_Init(ST7789_RD_PORT, &GPIO_InitStructure);	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	//数据引脚
	GPIOA->MODER &= 0xffff0000;		//PA0-7 清0
	GPIOA->MODER |= 0x00005555;		//PA0-7 输出
	GPIOA->OTYPER &= 0xff00;			//推挽
	GPIOA->ODR &= 0xFF00;
	
	ST7789_RST_LOW;
	TIMDelay_Nms(10);
	ST7789_RST_HIGH;
	TIMDelay_Nms(100);
	#if TFT2_0
	Write_ST7789_Reg(0xB2);			Write_ST7789_Data(0x05); //porch setting
															Write_ST7789_Data(0x05); 
															Write_ST7789_Data(0x00); 
															Write_ST7789_Data(0x33); 
															Write_ST7789_Data(0x33); 	

	Write_ST7789_Reg(0xB7);			Write_ST7789_Data(0x32); //64;VGH&VGL,12V&-8V
									  	
	Write_ST7789_Reg(0xC2);			Write_ST7789_Data(0x01);
	
	Write_ST7789_Reg(0xC3);			Write_ST7789_Data(0x0B); //1F;GVDD,5.1V  16
	
	Write_ST7789_Reg(0xBB);			Write_ST7789_Data(0x20); //28;VCOM
	
	Write_ST7789_Reg(0xC5);			Write_ST7789_Data(0x20); //vcom shift.0V  20
															  




	Write_ST7789_Reg(0xD0);			Write_ST7789_Data(0xA4); 
															Write_ST7789_Data(0xA1); //AVDD&AVCL,6.8v&-4.8v
												  
	Write_ST7789_Reg(0xD2);			Write_ST7789_Data(0x4C); 													  
	
	Write_ST7789_Reg(0xE8);			Write_ST7789_Data(0x03); //Booster CLK Select
				 
	Write_ST7789_Reg(0xE9);			Write_ST7789_Data(0x0D); //EQ
															Write_ST7789_Data(0x12);
															Write_ST7789_Data(0x00);

	Write_ST7789_Reg(0x36);			Write_ST7789_Data(0x00); //ACCESS

	Write_ST7789_Reg(0x35);			Write_ST7789_Data(0x00); //TE

	Write_ST7789_Reg(0x3A);			Write_ST7789_Data(0x05); //16bit
															


	Write_ST7789_Reg(0xC6);			Write_ST7789_Data(0x11); //0x09orig [DB7-5] 0forDotInv,1forColumnInv; 
		                                               //[DB4-0] Frame Rate,0x0F:60Hz 64hz

		
	    
	Write_ST7789_Reg(0xE0);			Write_ST7789_Data(0xD0); //V0[7-4] & V63[3-0]
															Write_ST7789_Data(0x06); //V62[5-0]
															Write_ST7789_Data(0x0B); //V61[5-0]
															Write_ST7789_Data(0x0A); //V59[4-0]
															Write_ST7789_Data(0x09); //V57[4-0]
															Write_ST7789_Data(0x05); //J1[5-4] & V50[3-0]
															Write_ST7789_Data(0x2E); //V43[6-0]
															Write_ST7789_Data(0x43); //V27[6-4] & V36[2-0]
															Write_ST7789_Data(0x44); //V20[6-0]
															Write_ST7789_Data(0x09); //J0[5-4] & V13[3-0]
															Write_ST7789_Data(0x16); //V6[4-0]
															Write_ST7789_Data(0x15); //V4[4-0]
															Write_ST7789_Data(0x23); //V2[5-0]
															Write_ST7789_Data(0x27); //V1[5-0]

	Write_ST7789_Reg(0xE1);			Write_ST7789_Data(0xD0); //V0[7-4] & V63[3-0]
															Write_ST7789_Data(0x06); //V62[5-0]
															Write_ST7789_Data(0x0B); //V61[5-0]
															Write_ST7789_Data(0x09); //V59[4-0]
															Write_ST7789_Data(0x08); //V57[4-0]
															Write_ST7789_Data(0x06); //J1[5-4] & V50[3-0]
															Write_ST7789_Data(0x2E); //V43[6-0]
															Write_ST7789_Data(0x44); //V27[6-4] & V36[2-0]
															Write_ST7789_Data(0x44); //V20[6-0]
															Write_ST7789_Data(0x3A); //J0[5-4] & V13[3-0]
															Write_ST7789_Data(0x15); //V6[4-0]
															Write_ST7789_Data(0x15); //V4[4-0]
															Write_ST7789_Data(0x23); //V2[5-0]
															Write_ST7789_Data(0x26); //V1[5-0]
#else
	Write_ST7789_Reg(0xB2);			Write_ST7789_Data(0x0C); //porch setting
															Write_ST7789_Data(0x0C); 
															Write_ST7789_Data(0x00); 
															Write_ST7789_Data(0x33); 
															Write_ST7789_Data(0x33); 	

	Write_ST7789_Reg(0xB7);			Write_ST7789_Data(0x02); //64;VGH&VGL,12V&-8V
									  	
	Write_ST7789_Reg(0xC2);			Write_ST7789_Data(0x01);
	
	Write_ST7789_Reg(0xC3);			Write_ST7789_Data(0x16); //1F;GVDD,5.1V  16
	
	Write_ST7789_Reg(0xBB);			Write_ST7789_Data(0x3C); //28;VCOM
	
	Write_ST7789_Reg(0xC5);			Write_ST7789_Data(0x20); //vcom shift.0V  20
															  




	Write_ST7789_Reg(0xD0);			Write_ST7789_Data(0xA4); 
															Write_ST7789_Data(0xA2); //AVDD&AVCL,6.8v&-4.8v
												  
	Write_ST7789_Reg(0xD2);			Write_ST7789_Data(0x4C); 													  
	
	Write_ST7789_Reg(0xE8);			Write_ST7789_Data(0x83); //Booster CLK Select
				 
	Write_ST7789_Reg(0xE9);			Write_ST7789_Data(0x09); //EQ
															Write_ST7789_Data(0x09);
															Write_ST7789_Data(0x08);

	Write_ST7789_Reg(0x36);			Write_ST7789_Data(0x00); //ACCESS

	Write_ST7789_Reg(0x35);			Write_ST7789_Data(0x00); //TE

	Write_ST7789_Reg(0x3A);			Write_ST7789_Data(0x05); //16bit
															


	Write_ST7789_Reg(0xC6);			Write_ST7789_Data(0x0d); //0x09orig [DB7-5] 0forDotInv,1forColumnInv; 
		                                               //[DB4-0] Frame Rate,0x0F:60Hz 64hz

		
	    
	Write_ST7789_Reg(0xE0);			Write_ST7789_Data(0xD0); //V0[7-4] & V63[3-0]
															Write_ST7789_Data(0x06); //V62[5-0]
															Write_ST7789_Data(0x0C); //V61[5-0]
															Write_ST7789_Data(0x09); //V59[4-0]
															Write_ST7789_Data(0x09); //V57[4-0]
															Write_ST7789_Data(0x25); //J1[5-4] & V50[3-0]
															Write_ST7789_Data(0x2E); //V43[6-0]
															Write_ST7789_Data(0x33); //V27[6-4] & V36[2-0]
															Write_ST7789_Data(0x45); //V20[6-0]
															Write_ST7789_Data(0x36); //J0[5-4] & V13[3-0]
															Write_ST7789_Data(0x12); //V6[4-0]
															Write_ST7789_Data(0x12); //V4[4-0]
															Write_ST7789_Data(0x2E); //V2[5-0]
															Write_ST7789_Data(0x34); //V1[5-0]

	Write_ST7789_Reg(0xE1);			Write_ST7789_Data(0xD0); //V0[7-4] & V63[3-0]
															Write_ST7789_Data(0x06); //V62[5-0]
															Write_ST7789_Data(0x0C); //V61[5-0]
															Write_ST7789_Data(0x09); //V59[4-0]
															Write_ST7789_Data(0x09); //V57[4-0]
															Write_ST7789_Data(0x25); //J1[5-4] & V50[3-0]
															Write_ST7789_Data(0x2E); //V43[6-0]
															Write_ST7789_Data(0x33); //V27[6-4] & V36[2-0]
															Write_ST7789_Data(0x45); //V20[6-0]
															Write_ST7789_Data(0x36); //J0[5-4] & V13[3-0]
															Write_ST7789_Data(0x12); //V6[4-0]
															Write_ST7789_Data(0x12); //V4[4-0]
															Write_ST7789_Data(0x2E); //V2[5-0]
															Write_ST7789_Data(0x34); //V1[5-0]
#endif
	Write_ST7789_Reg(0x21);
	
	Write_ST7789_Reg(0x11);
	TIMDelay_Nms(120);

	Write_ST7789_Reg(0x29);
	TIMDelay_Nms(50);	
	
	ST7789_LED_ON;
}

/*
* 函数名称：Write_ST7789_Reg；
* 功能说明：写命令；
* 入口参数：hibyte->命令；
* 返回值  ：无；
* 备注    ：无；
*/
void Write_ST7789_Reg(uint8_t data)
{ 
	ST7789_DC_LOW;
	ST7789_RD_HIGH;
	DATA_OUT(data);
	ST7789_CS_LOW;  //片选
  ST7789_WR_LOW;
	ST7789_WR_HIGH;
  ST7789_CS_HIGH;
}

/*
* 函数名称：Write_ST7789_Data；
* 功能说明：写数据；
* 入口参数：hibyte->数据；
* 返回值  ：无；
* 备注    ：无；
*/
void Write_ST7789_Data(uint8_t data)
{
	ST7789_DC_HIGH;
	ST7789_RD_HIGH;
	DATA_OUT(data);
	ST7789_CS_LOW;  //片选
	ST7789_WR_LOW;
	ST7789_WR_HIGH;
  ST7789_CS_HIGH;
}

/*
* 函数名称：Read_ST7789_Data；
* 功能说明：读数据；
* 入口参数：无；
* 返回值  ：8位数据；
* 备注    ：无；
*/
uint8_t Read_ST7789_Data(void)
{   
	uint8_t read_data;
	
	GPIOA->MODER &= 0xffff0000;		//PA0-7 输入
	GPIOA->PUPDR &= 0xffff0000;		//PA0-7 上拉
	GPIOA->PUPDR |= 0x00005555;
	GPIOA->ODR &= 0Xff00;     

	ST7789_DC_HIGH;
	ST7789_WR_HIGH;
	ST7789_CS_LOW;  //片选
	ST7789_RD_LOW;
	read_data = DATA_READ();
	ST7789_RD_HIGH;
  ST7789_CS_HIGH;	

	GPIOA->MODER &= 0xffff0000;		//PA0-7 清0
	GPIOA->MODER |= 0x00005555;		//PA0-7 输出
	GPIOA->OTYPER &= 0xff00;		//推挽
	GPIOA->ODR |= 0x00FF;   
	
	return read_data;  
}

void Address_Set(uint16_t x,uint16_t y)
{
	Write_ST7789_Reg(0x2a);        //设置x坐标；
	Write_ST7789_Data(x>>8);
	Write_ST7789_Data(x&0xff); 
	Write_ST7789_Data(0x00);
	Write_ST7789_Data(0xf0); 
	Write_ST7789_Reg(0x2b);        //设置y坐标；
	Write_ST7789_Data(y>>8);
	Write_ST7789_Data(y&0xff);
#if TFT2_0
	Write_ST7789_Data(0x01);
	Write_ST7789_Data(0x40);
#else
	Write_ST7789_Data(0x00);
	Write_ST7789_Data(0xf0)
#endif
	Write_ST7789_Reg(0x2c);
}

/*
* 函数名称：Write_ST7789_16Bit；
* 功能说明：写16位颜色数据；
* 入口参数：无；
* 返回值  ：无；
* 备注    ：无；
*/
void Write_ST7789_16Bit(uint8_t hibyte,uint8_t lowbyte)
{
	ST7789_DC_HIGH;
	ST7789_RD_HIGH;
	DATA_OUT(hibyte);
	ST7789_CS_LOW;  //片选
	ST7789_WR_LOW;
	ST7789_WR_HIGH;	
	DATA_OUT(lowbyte);
	ST7789_WR_LOW;
	ST7789_WR_HIGH;
  ST7789_CS_HIGH;		
}

/*
* 函数名称：Write_ST7789_Point；
* 功能说明：写点的颜色数据；
* 入口参数：目标坐标；
* 返回值  ：16位颜色值；
* 备注    ：无；
*/
void Write_ST7789_Point(uint16_t x,uint16_t y,uint16_t color)
{
	Write_ST7789_Reg(0x2a);        //设置x坐标；
	Write_ST7789_Data((x>>8));
	Write_ST7789_Data((x&0xff)); 		
	Write_ST7789_Reg(0x2b);        //设置y坐标；	if((x&0xff00) != 0)	
	Write_ST7789_Data((y>>8));
	Write_ST7789_Data((y&0xff));
	Write_ST7789_Reg(0x2c);
	
	ST7789_DC_HIGH;
	ST7789_RD_HIGH;
	DATA_OUT(color>>8);
	ST7789_CS_LOW;  //片选
	ST7789_WR_LOW;
	ST7789_WR_HIGH;	
	DATA_OUT(color&0xff);
	ST7789_WR_LOW;
	ST7789_WR_HIGH;
  ST7789_CS_HIGH;
}

/*
* 函数名称：Read_ST7789_Point；
* 功能说明：读点的颜色数据；
* 入口参数：目标坐标；
* 返回值  ：16位颜色值；
* 备注    ：无；
*/
uint16_t Read_ST7789_Point(uint16_t x,uint16_t y)
{   
	uint16_t r,g,b;
	Address_Set(x,y);        //指定坐标；
	Write_ST7789_Reg(0x3e);  //读内存命令；
	Read_ST7789_Data();      //无效；
	
	r=Read_ST7789_Data();    //r、b和g的数据格式为前5位和6位；
	g=Read_ST7789_Data();
	b=Read_ST7789_Data();
	
	return ((r>>3)<<11)|((g>>2)<<5)|(b>>3);
}

