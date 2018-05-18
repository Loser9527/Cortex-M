#include "ft6236.h"

void delay_xus(uint32_t time)  
{  
  uint32_t i=8*time;  
  while(i--);  
}

void delay_xms(uint32_t time)  
{  
  uint32_t i=8000*time;  
  while(i--);  
}

void FT6236_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd( FT6236_RST_CLK | FT6236_SCL_CLK |
												 FT6236_SDA_CLK | FT6236_INT_CLK ,
												 ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = FT6236_RST_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //高速
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽输出
  GPIO_Init(FT6236_RST_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = FT6236_SCL_PIN;         					   //引脚	
	GPIO_Init(FT6236_SCL_PORT, &GPIO_InitStructure);								
	FT6236_SCL_SET;
	
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //引脚	
	GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);
	FT6236_SDA_SET;	
	
	GPIO_InitStructure.GPIO_Pin = FT6236_INT_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(FT6236_INT_PORT, &GPIO_InitStructure);
}

//外部中断初始化函数
void EXTIX1_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTIX_GPIO1, EXTIX_Pin1);

	EXTI_InitStructure.EXTI_Line = EXTIX_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	EXTI_ClearITPendingBit(EXTIX_Line1);    //清除LINEx上的中断标志位 
	NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn1;	//使能TOUCH_INT所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);  
}

void FT6236_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //高速
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽输出
  GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);	
}

void FT6236_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                       //输入模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;									 //上拉
  GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);	
}

/*
* 函数名称：FT6236_IIC_Start；
* 功能说明：FT6236起始信号；
* 入口参数：无
* 返回值  ：无；
* 备注    ：无；
*/
void FT6236_IIC_Start(void)					
{
	FT6236_SDA_OUT();   	//sda线输出
	FT6236_SDA_SET;									
	FT6236_SCL_SET;				//SCL最小高电平脉宽:0.6us
	delay_xus(5);					//起始信号的最小建立时间:0.6us
	FT6236_SDA_CLR;				//SCL高电平期间，SDA的一个下降沿表示起始信号
	delay_xus(5);					//起始信号的最小保持时间:0.6us
	FT6236_SCL_CLR;				//箝住总线,为发送器件地址做准备;
}

/*
* 函数名称：FT6236_IIC_Stop；
* 功能说明：FT6236结束信号；
* 入口参数：无
* 返回值  ：无；
* 备注    ：无；
*/
void FT6236_IIC_Stop(void)							
{
	FT6236_SDA_OUT();   //sda线输出	
	FT6236_SCL_CLR;			//SCL最小高电平脉宽:0.6us
	FT6236_SDA_CLR;	
	delay_xus(5);
	FT6236_SCL_SET;
	delay_xus(5);
	FT6236_SDA_SET;			//SCL高电平期间，SDA的一个上升沿表示停止信号						
}

/*
* 函数名称：FT6236_Send_ACK；
* 功能说明：单片机发送应答信号；
* 入口参数：无
* 返回值  ：无；
* 备注    ：无；
*/
void FT6236_Send_ACK(void)							
{
	FT6236_SCL_CLR;	
	FT6236_SDA_OUT();     		//sda线输出	
	FT6236_SDA_CLR;	
	delay_xus(5);																
	FT6236_SCL_SET;		        //SCL最小高电平脉宽:0.6us
	delay_xus(5);
	FT6236_SCL_CLR;		        //SCL最小低电平脉宽:1.2us
}

/*
* 函数名称：FT6236_Send_NACK；
* 功能说明：单片机发送非应答信号；
* 入口参数：无
* 返回值  ：无；
* 备注    ：无；
*/
void FT6236_Send_NACK(void)
{
	FT6236_SCL_CLR;	
	FT6236_SDA_OUT();     				//sda线输出	
	FT6236_SDA_SET;	
	delay_xus(5);																
	FT6236_SCL_SET;				//SCL最小高电平脉宽:0.6us
	delay_xus(5);
	FT6236_SCL_CLR;				//SCL最小低电平脉宽:1.2us
}

/*
* 函数名称：FT6236_Wait_Ack；
* 功能说明：等待应答信号；
* 入口参数：无
* 返回值  ：0-->接收应答成功；1-->接收应答失败；
* 备注    ：无；
*/
uint8_t FT6236_Wait_Ack(void)							
{
	uint8_t ucErrTime=0;
	FT6236_SDA_IN();      		//SDA设置为输入
	FT6236_SDA_SET;
	delay_xus(5);
	FT6236_SCL_SET;						//使SDA上数据有效;SCL最小高电平脉宽:0.6us
	delay_xus(5);
	while(FT6236_SDA_Read)
	{	
		ucErrTime++;
		if(ucErrTime>250)		//无应答
		{
			FT6236_IIC_Stop();	
			return 1;
		}
	}
	FT6236_SCL_CLR;
	return 0;
}

/*
* 函数名称：FT6236_Send_Byte；
* 功能说明：向FT6236发送一个字节数据；
* 入口参数：data-->发送的数据；
* 返回值  ：无；
* 备注    ：无；
*/
void FT6236_Send_Byte(uint8_t data)						
{
	uint8_t i;						
	FT6236_SDA_OUT();    	//sda线输出	
	FT6236_SCL_CLR;				//拉低时钟开始数据传输
	delay_xus(5);
	for(i=0;i<8;i++)			//8位1B地址/数据的长度
	{
		if(data & 0x80)
		FT6236_SDA_SET;
		else
		FT6236_SDA_CLR;
		data<<=1;
		FT6236_SCL_SET;
		delay_xus(5);
		FT6236_SCL_CLR;
		delay_xus(5);
	}		
}

/*
* 函数名称：FT6236_Read_Byte；
* 功能说明：从FT6236读一个字节数据；
* 入口参数：无
* 返回值  ：读出的数据；
* 备注    ：无；
*/
uint8_t FT6236_Read_Byte(unsigned char ack)						
{
	uint8_t i,data = 0;				//接收数据位数和内容暂存单元
	FT6236_SDA_IN();					//SDA设置为输入
	delay_xus(5);
	for(i=8;i>0;i--)
	{
		FT6236_SCL_CLR;
		delay_xus(5);
		FT6236_SCL_SET;
		data <<= 1;
		if(FT6236_SDA_Read)
		data++;
	}
	if(!ack)
	FT6236_Send_NACK();
	else
	FT6236_Send_ACK();
	return(data);							//返回1Byte的数据
}


/*
* 函数名称：FT6236_Write_Reg；
* 功能说明：FT6236连续写寄存器；
* 入口参数：reg-->寄存器地址，buf-->发送缓存空间，len-->连续长度；
* 返回值  ：0-->成功，1-->失败；
* 备注    ：无；
*/
uint8_t FT6236_Write_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
	FT6236_IIC_Start();
	
	FT6236_Send_Byte(FT_CMD_WR);        //发送写命令；
	FT6236_Wait_Ack();
	
	FT6236_Send_Byte(reg&0xff);         //发送低8位地址
	FT6236_Wait_Ack();
	
	for(i=0;i<len;i++)
	{
    FT6236_Send_Byte(buf[i]);     	  //发数据
		ret=FT6236_Wait_Ack();
		if(ret)break;                   	//应答为'1'，失败，立即返回；
	}
  FT6236_IIC_Stop();            	    //产生一个停止条件	    
	return ret; 
}

/*
* 函数名称：FT6236_Read_Reg；
* 功能说明：FT6236连续读寄存器；
* 入口参数：reg-->寄存器地址，buf-->接收缓存空间，len-->连续长度；
* 返回值  ：0-->成功，1-->失败；
* 备注    ：无；
*/		  
uint8_t FT6236_Read_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i; 
 	FT6236_IIC_Start();	
	
 	FT6236_Send_Byte(FT_CMD_WR);                  //发送写命令 	 
	FT6236_Wait_Ack();		
	
	FT6236_Send_Byte(reg&0xff);                   //发送低8位地址
	FT6236_Wait_Ack();
	  
 	FT6236_IIC_Start();  
	
	FT6236_Send_Byte(FT_CMD_RD);                  //发送读命令		
	FT6236_Wait_Ack();			

	for(i=0;i<len;i++)
	{	   
		*buf++=FT6236_Read_Byte(i==(len-1)?0:1); 	  //读入1B数据到接收数据缓冲区中  
	} 
  FT6236_IIC_Stop();                       		  //产生一个停止条件	  
	return 0;
} 



void FT6236_Init(void)
{
	uint8_t temp;
	
	FT6236_GPIO_Init();
	
	EXTIX1_Init();
	
	FT6236_RST_CLR;
	delay_xms(20);
	FT6236_RST_SET;
	delay_xms(60);
	temp=0;
	FT6236_Write_Reg(FT_DEVIDE_MODE,&temp,1);   //进入正常操作模式 	
 	temp=22;                                    //触摸有效值，22，越小越灵敏	
 	FT6236_Write_Reg(FT_ID_G_THGROUP,&temp,1);  //设置触摸有效值
 	temp=12;                                    //激活周期，不能小于12，最大14
 	FT6236_Write_Reg(FT_ID_G_PERIODACTIVE,&temp,1); 	
}

const uint16_t FT6236_TPX_TBL[5]=
{
	FT_TP1_REG,
	FT_TP2_REG,
	FT_TP3_REG,
	FT_TP4_REG,
	FT_TP5_REG
};
TouchPointRefTypeDef TPR_Structure;

void FT6236_Scan(void)
{
//	uint8_t i=0;
	uint8_t sta = 0;
	uint8_t buf[4] = {0};    
	FT6236_Read_Reg(0x02,&sta,1);//读取触摸点的状态 
//	printf("触摸点数：%8x",sta);
//	printf("\r\n");//插入换行 	   
// 	if((sta & 0x0f) == 5)	//判断是否有触摸点按下，0x02寄存器的低4位表示有效触点个数
// 	{
// 		TPR_Structure.TouchSta = ~(0xff << (sta & 0x0f));	//~(0xFF << (sta & 0x0F))将点的个数转换为触摸点按下有效标志
// 		for(i=0;i<5;i++)	                                //分别判断触摸点1-5是否被按下
// 		{
// 			if(TPR_Structure.TouchSta & (1<<i))			    //读取触摸点坐标
// 			{											    //被按下则读取对应触摸点坐标数据
// 				FT6236_Read_Reg(FT6236_TPX_TBL[i],buf,4);	//读取XY坐标值
//				TPR_Structure.x[i]=((uint16_t)(buf[0]&0x0f)<<8)+buf[1];
//				TPR_Structure.y[i]=((uint16_t)(buf[2]&0x0f)<<8)+buf[3];
// 				if((buf[0]&0xc0)!=0x80)
// 				{
//					TPR_Structure.x[i]=TPR_Structure.y[i]=0;//必须是contact事件，才认为有效	
//					return;
//				}
// 			}
// 		}
// 		TPR_Structure.TouchSta |= TP_PRES_DOWN;     //触摸按下标记
// 	}
 	if((sta & 0x0f) == 1)	//判断是否有触摸点按下，0x02寄存器的低4位表示有效触点个数
 	{
		FT6236_Read_Reg(FT6236_TPX_TBL[0],buf,4);	//读取XY坐标值
		TPR_Structure.x[0]=((uint16_t)(buf[0]&0x0f)<<8)+buf[1];
		TPR_Structure.y[0]=((uint16_t)(buf[2]&0x0f)<<8)+buf[3];
		if((buf[0]&0xc0)!=0x80)
		{
			TPR_Structure.x[0]=TPR_Structure.y[0]=0;//必须是contact事件，才认为有效	
			return;
		}
 		TPR_Structure.TouchSta |= TP_PRES_DOWN;     //触摸按下标记
 	}
 	else
 	{
 		if(TPR_Structure.TouchSta &TP_PRES_DOWN) 	//之前是被按下的
 		TPR_Structure.TouchSta &= ~TP_PRES_DOWN;        //触摸松开标记	
 		else
 		{
 			TPR_Structure.x[0] = 0;
 			TPR_Structure.y[0] = 0;
 			TPR_Structure.TouchSta &= 0xe0;	//清楚触摸点有效标记
 		}
 	}
}

