#include "bsp_spi_dma.h"

void SPIx_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ��SPIʱ�� */
	SPI_APBxClock_FUN ( SPI_CLK, ENABLE );

	/* ʹ��SPI������ص�ʱ�� */
	RCC_APB2PeriphClockCmd ( SPI_LCD_CS_CLK|SPI_SCK_CLK|
																SPI_MISO_PIN|SPI_MOSI_PIN, ENABLE );

	/* ����SPI�� CS���ţ���ͨIO���� */
	GPIO_InitStructure.GPIO_Pin = SPI_LCD_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SPI_LCD_CS_PORT, &GPIO_InitStructure);

	/* ����SPI�� SCK����*/
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_SCK_PORT, &GPIO_InitStructure);

	/* ����SPI�� MISO����*/
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
	GPIO_Init(SPI_MISO_PORT, &GPIO_InitStructure);

	/* ����SPI�� MOSI����*/
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
	GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStructure);

	/* ֹͣ�ź� LCD_CS���Ÿߵ�ƽ*/
	SPI_LCD_CS_HIGH();

	/* SPI ģʽ���� */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPIx , &SPI_InitStructure);

	/* ʹ�� SPI  */
	SPI_Cmd(SPIx , ENABLE);
}

void SPIx_DataSize(uint8_t datasize)
{
	SPI_Cmd(SPIx , DISABLE);
	
	if(datasize == 8)
	SPI_DataSizeConfig(SPIx , SPI_DataSize_8b);
	else if(datasize == 16)
	SPI_DataSizeConfig(SPIx , SPI_DataSize_16b);	

	SPI_Cmd(SPIx , ENABLE);
}

uint8_t SPIx_SendByte(uint8_t byte)
{
	/* �ȴ����ͻ�����Ϊ�գ�TXE�¼� */
	while (SPI_I2S_GetFlagStatus(SPIx , SPI_I2S_FLAG_TXE) == RESET);

	/* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
	SPI_I2S_SendData(SPIx , byte);

	/* �ȴ����ջ������ǿգ�RXNE�¼� */
	while (SPI_I2S_GetFlagStatus(SPIx , SPI_I2S_FLAG_RXNE) == RESET);

	/* ��ȡ���ݼĴ�������ȡ���ջ��������� */
	return SPI_I2S_ReceiveData(SPIx );	
}

uint16_t SPIx_SendHalfWord(uint16_t HalfWord)
{
	/* �ȴ����ͻ�����Ϊ�գ�TXE�¼� */
	while (SPI_I2S_GetFlagStatus(SPIx , SPI_I2S_FLAG_TXE) == RESET);

	/* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
	SPI_I2S_SendData(SPIx , HalfWord);

	/* �ȴ����ջ������ǿգ�RXNE�¼� */
	while (SPI_I2S_GetFlagStatus(SPIx , SPI_I2S_FLAG_RXNE) == RESET);
	/* ��ȡ���ݼĴ�������ȡ���ջ��������� */
	return SPI_I2S_ReceiveData(SPIx );
}


void DMA_Config(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
		
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPIx->DR;
		
//		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&color_data;
		// ���򣺴洢��������
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		// �����С	
//		DMA_InitStructure.DMA_BufferSize = 57600;
		// �����ַ����
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;	 
		// DMAģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		// ���ȼ�����	
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		// ʧ���ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// ����DMAͨ��		   
		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    //���DMA������������ɱ�־λ
    DMA_ClearFlag(DMA_FLAG_TC);
		//ʹ��SPI_DMA���ͻ��津��
		SPI_I2S_DMACmd(SPIx,SPI_I2S_DMAReq_Tx,ENABLE);
}

void SPIx_DMA_TxSingle(uint16_t *buffer,uint16_t len_byte)
{
		DMA1_Channel3->CNDTR=len_byte;
		DMA1_Channel3->CMAR=(uint32_t)buffer;

		DMA_Cmd(DMA_CHANNEL,ENABLE);
		while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET);
		DMA_ClearFlag(DMA_FLAG_TC);
		DMA_Cmd(DMA_CHANNEL,DISABLE);
}

