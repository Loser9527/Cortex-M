#include "DMA.h"

u8 MyAdc_DMAConfig(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr)
{
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2ʱ��ʹ�� 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1ʱ��ʹ�� 
	}
	while(DMA_Streamx->CR&0X01);//�ȴ�DMA������ 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//�õ�streamͨ����
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//���֮ǰ��stream�ϵ������жϱ�־
	else DMAx->LIFCR|=0X3D<<6*streamx;						//���֮ǰ��stream�ϵ������жϱ�־
	
	DMA_Streamx->PAR=par;		//DMA�����ַ
	DMA_Streamx->M0AR=mar;		//DMA �洢��0��ַ
	DMA_Streamx->NDTR=ndtr;		//DMA �洢��0��ַ
	DMA_Streamx->CR=0;			//��ȫ����λCR�Ĵ���ֵ 
	
	DMA_Streamx->CR|=0<<6;		//���赽�洢��ģʽ(0)  �洢��������ģʽ(1)
	DMA_Streamx->CR|=1<<8;		//��ѭ��ģʽ(0)  	  ѭ��ģʽ(1)
	DMA_Streamx->CR|=0<<9;		//���������ģʽ(0)	  ���������ģʽ(1)
	DMA_Streamx->CR|=0<<10;		//�洢��������ģʽ(0)  �洢��������ģʽ(1)
	DMA_Streamx->CR|=1<<11;		//�������ݳ���:16λ(1) 8λΪ(0)
	DMA_Streamx->CR|=1<<13;		//�洢�����ݳ���:16λ(1) 8λΪ(0)
	DMA_Streamx->CR|=1<<16;		//�е����ȼ�	
	DMA_Streamx->CR|=0<<21;		//����ͻ�����δ���
	DMA_Streamx->CR|=0<<23;		//�洢��ͻ�����δ���
	DMA_Streamx->CR|=(u32)chx<<25;//ͨ��ѡ��
	
	DMA_Streamx->CR|=1<<0;		//����DMA����
	return 0;
}


//����һ��DMA����
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ�����
//
u8 MyAdc_DMAEnable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Streamx->CR&=~(1<<0); 	//�ر�DMA���� 
	while(DMA_Streamx->CR&0X1);	//ȷ��DMA���Ա�����  
	DMA_Streamx->NDTR=ndtr;		//DMA �洢��0��ַ 
	DMA_Streamx->CR|=1<<0;		//����DMA����
	return 0;
//	
}	 