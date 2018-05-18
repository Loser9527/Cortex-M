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
	
	GPIO_InitStructure.GPIO_Pin = FT6236_RST_PIN;         					   //����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //���ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //�������
  GPIO_Init(FT6236_RST_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = FT6236_SCL_PIN;         					   //����	
	GPIO_Init(FT6236_SCL_PORT, &GPIO_InitStructure);								
	FT6236_SCL_SET;
	
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //����	
	GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);
	FT6236_SDA_SET;	
	
	GPIO_InitStructure.GPIO_Pin = FT6236_INT_PIN;         					   //����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(FT6236_INT_PORT, &GPIO_InitStructure);
}

//�ⲿ�жϳ�ʼ������
void EXTIX1_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTIX_GPIO1, EXTIX_Pin1);

	EXTI_InitStructure.EXTI_Line = EXTIX_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	EXTI_ClearITPendingBit(EXTIX_Line1);    //���LINEx�ϵ��жϱ�־λ 
	NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn1;	//ʹ��TOUCH_INT���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  
}

void FT6236_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //���ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //�������
  GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);	
}

void FT6236_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FT6236_SDA_PIN;         					   //����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                       //����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;									 //����
  GPIO_Init(FT6236_SDA_PORT, &GPIO_InitStructure);	
}

/*
* �������ƣ�FT6236_IIC_Start��
* ����˵����FT6236��ʼ�źţ�
* ��ڲ�������
* ����ֵ  ���ޣ�
* ��ע    ���ޣ�
*/
void FT6236_IIC_Start(void)					
{
	FT6236_SDA_OUT();   	//sda�����
	FT6236_SDA_SET;									
	FT6236_SCL_SET;				//SCL��С�ߵ�ƽ����:0.6us
	delay_xus(5);					//��ʼ�źŵ���С����ʱ��:0.6us
	FT6236_SDA_CLR;				//SCL�ߵ�ƽ�ڼ䣬SDA��һ���½��ر�ʾ��ʼ�ź�
	delay_xus(5);					//��ʼ�źŵ���С����ʱ��:0.6us
	FT6236_SCL_CLR;				//��ס����,Ϊ����������ַ��׼��;
}

/*
* �������ƣ�FT6236_IIC_Stop��
* ����˵����FT6236�����źţ�
* ��ڲ�������
* ����ֵ  ���ޣ�
* ��ע    ���ޣ�
*/
void FT6236_IIC_Stop(void)							
{
	FT6236_SDA_OUT();   //sda�����	
	FT6236_SCL_CLR;			//SCL��С�ߵ�ƽ����:0.6us
	FT6236_SDA_CLR;	
	delay_xus(5);
	FT6236_SCL_SET;
	delay_xus(5);
	FT6236_SDA_SET;			//SCL�ߵ�ƽ�ڼ䣬SDA��һ�������ر�ʾֹͣ�ź�						
}

/*
* �������ƣ�FT6236_Send_ACK��
* ����˵������Ƭ������Ӧ���źţ�
* ��ڲ�������
* ����ֵ  ���ޣ�
* ��ע    ���ޣ�
*/
void FT6236_Send_ACK(void)							
{
	FT6236_SCL_CLR;	
	FT6236_SDA_OUT();     		//sda�����	
	FT6236_SDA_CLR;	
	delay_xus(5);																
	FT6236_SCL_SET;		        //SCL��С�ߵ�ƽ����:0.6us
	delay_xus(5);
	FT6236_SCL_CLR;		        //SCL��С�͵�ƽ����:1.2us
}

/*
* �������ƣ�FT6236_Send_NACK��
* ����˵������Ƭ�����ͷ�Ӧ���źţ�
* ��ڲ�������
* ����ֵ  ���ޣ�
* ��ע    ���ޣ�
*/
void FT6236_Send_NACK(void)
{
	FT6236_SCL_CLR;	
	FT6236_SDA_OUT();     				//sda�����	
	FT6236_SDA_SET;	
	delay_xus(5);																
	FT6236_SCL_SET;				//SCL��С�ߵ�ƽ����:0.6us
	delay_xus(5);
	FT6236_SCL_CLR;				//SCL��С�͵�ƽ����:1.2us
}

/*
* �������ƣ�FT6236_Wait_Ack��
* ����˵�����ȴ�Ӧ���źţ�
* ��ڲ�������
* ����ֵ  ��0-->����Ӧ��ɹ���1-->����Ӧ��ʧ�ܣ�
* ��ע    ���ޣ�
*/
uint8_t FT6236_Wait_Ack(void)							
{
	uint8_t ucErrTime=0;
	FT6236_SDA_IN();      		//SDA����Ϊ����
	FT6236_SDA_SET;
	delay_xus(5);
	FT6236_SCL_SET;						//ʹSDA��������Ч;SCL��С�ߵ�ƽ����:0.6us
	delay_xus(5);
	while(FT6236_SDA_Read)
	{	
		ucErrTime++;
		if(ucErrTime>250)		//��Ӧ��
		{
			FT6236_IIC_Stop();	
			return 1;
		}
	}
	FT6236_SCL_CLR;
	return 0;
}

/*
* �������ƣ�FT6236_Send_Byte��
* ����˵������FT6236����һ���ֽ����ݣ�
* ��ڲ�����data-->���͵����ݣ�
* ����ֵ  ���ޣ�
* ��ע    ���ޣ�
*/
void FT6236_Send_Byte(uint8_t data)						
{
	uint8_t i;						
	FT6236_SDA_OUT();    	//sda�����	
	FT6236_SCL_CLR;				//����ʱ�ӿ�ʼ���ݴ���
	delay_xus(5);
	for(i=0;i<8;i++)			//8λ1B��ַ/���ݵĳ���
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
* �������ƣ�FT6236_Read_Byte��
* ����˵������FT6236��һ���ֽ����ݣ�
* ��ڲ�������
* ����ֵ  �����������ݣ�
* ��ע    ���ޣ�
*/
uint8_t FT6236_Read_Byte(unsigned char ack)						
{
	uint8_t i,data = 0;				//��������λ���������ݴ浥Ԫ
	FT6236_SDA_IN();					//SDA����Ϊ����
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
	return(data);							//����1Byte������
}


/*
* �������ƣ�FT6236_Write_Reg��
* ����˵����FT6236����д�Ĵ�����
* ��ڲ�����reg-->�Ĵ�����ַ��buf-->���ͻ���ռ䣬len-->�������ȣ�
* ����ֵ  ��0-->�ɹ���1-->ʧ�ܣ�
* ��ע    ���ޣ�
*/
uint8_t FT6236_Write_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
	FT6236_IIC_Start();
	
	FT6236_Send_Byte(FT_CMD_WR);        //����д���
	FT6236_Wait_Ack();
	
	FT6236_Send_Byte(reg&0xff);         //���͵�8λ��ַ
	FT6236_Wait_Ack();
	
	for(i=0;i<len;i++)
	{
    FT6236_Send_Byte(buf[i]);     	  //������
		ret=FT6236_Wait_Ack();
		if(ret)break;                   	//Ӧ��Ϊ'1'��ʧ�ܣ��������أ�
	}
  FT6236_IIC_Stop();            	    //����һ��ֹͣ����	    
	return ret; 
}

/*
* �������ƣ�FT6236_Read_Reg��
* ����˵����FT6236�������Ĵ�����
* ��ڲ�����reg-->�Ĵ�����ַ��buf-->���ջ���ռ䣬len-->�������ȣ�
* ����ֵ  ��0-->�ɹ���1-->ʧ�ܣ�
* ��ע    ���ޣ�
*/		  
uint8_t FT6236_Read_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i; 
 	FT6236_IIC_Start();	
	
 	FT6236_Send_Byte(FT_CMD_WR);                  //����д���� 	 
	FT6236_Wait_Ack();		
	
	FT6236_Send_Byte(reg&0xff);                   //���͵�8λ��ַ
	FT6236_Wait_Ack();
	  
 	FT6236_IIC_Start();  
	
	FT6236_Send_Byte(FT_CMD_RD);                  //���Ͷ�����		
	FT6236_Wait_Ack();			

	for(i=0;i<len;i++)
	{	   
		*buf++=FT6236_Read_Byte(i==(len-1)?0:1); 	  //����1B���ݵ��������ݻ�������  
	} 
  FT6236_IIC_Stop();                       		  //����һ��ֹͣ����	  
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
	FT6236_Write_Reg(FT_DEVIDE_MODE,&temp,1);   //������������ģʽ 	
 	temp=22;                                    //������Чֵ��22��ԽСԽ����	
 	FT6236_Write_Reg(FT_ID_G_THGROUP,&temp,1);  //���ô�����Чֵ
 	temp=12;                                    //�������ڣ�����С��12�����14
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
	FT6236_Read_Reg(0x02,&sta,1);//��ȡ�������״̬ 
//	printf("����������%8x",sta);
//	printf("\r\n");//���뻻�� 	   
// 	if((sta & 0x0f) == 5)	//�ж��Ƿ��д����㰴�£�0x02�Ĵ����ĵ�4λ��ʾ��Ч�������
// 	{
// 		TPR_Structure.TouchSta = ~(0xff << (sta & 0x0f));	//~(0xFF << (sta & 0x0F))����ĸ���ת��Ϊ�����㰴����Ч��־
// 		for(i=0;i<5;i++)	                                //�ֱ��жϴ�����1-5�Ƿ񱻰���
// 		{
// 			if(TPR_Structure.TouchSta & (1<<i))			    //��ȡ����������
// 			{											    //���������ȡ��Ӧ��������������
// 				FT6236_Read_Reg(FT6236_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
//				TPR_Structure.x[i]=((uint16_t)(buf[0]&0x0f)<<8)+buf[1];
//				TPR_Structure.y[i]=((uint16_t)(buf[2]&0x0f)<<8)+buf[3];
// 				if((buf[0]&0xc0)!=0x80)
// 				{
//					TPR_Structure.x[i]=TPR_Structure.y[i]=0;//������contact�¼�������Ϊ��Ч	
//					return;
//				}
// 			}
// 		}
// 		TPR_Structure.TouchSta |= TP_PRES_DOWN;     //�������±��
// 	}
 	if((sta & 0x0f) == 1)	//�ж��Ƿ��д����㰴�£�0x02�Ĵ����ĵ�4λ��ʾ��Ч�������
 	{
		FT6236_Read_Reg(FT6236_TPX_TBL[0],buf,4);	//��ȡXY����ֵ
		TPR_Structure.x[0]=((uint16_t)(buf[0]&0x0f)<<8)+buf[1];
		TPR_Structure.y[0]=((uint16_t)(buf[2]&0x0f)<<8)+buf[3];
		if((buf[0]&0xc0)!=0x80)
		{
			TPR_Structure.x[0]=TPR_Structure.y[0]=0;//������contact�¼�������Ϊ��Ч	
			return;
		}
 		TPR_Structure.TouchSta |= TP_PRES_DOWN;     //�������±��
 	}
 	else
 	{
 		if(TPR_Structure.TouchSta &TP_PRES_DOWN) 	//֮ǰ�Ǳ����µ�
 		TPR_Structure.TouchSta &= ~TP_PRES_DOWN;        //�����ɿ����	
 		else
 		{
 			TPR_Structure.x[0] = 0;
 			TPR_Structure.y[0] = 0;
 			TPR_Structure.TouchSta &= 0xe0;	//�����������Ч���
 		}
 	}
}

