#include "stm32f10x.h"                  // Device header

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    NVIC_InitTypeDef NVIC_IntiStructure;
    NVIC_IntiStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_IntiStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_IntiStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_IntiStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_IntiStructure);

    USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) != SET);
    USART_SendData(USART1,Byte);
}

void Serial_SendArray(uint8_t *Array,uint8_t length)
{
    for(uint8_t i = 0; i<length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}


uint8_t Rxdata;
char string[100];
uint8_t Flag = 0;

void USART1_IRQHandler(void)
{
    static uint8_t status = 0;
    
    if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
    {
        Rxdata = USART_ReceiveData(USART1);
        static uint8_t loop = 0;

        if(Rxdata == '%' && status == 0)
        {
            status = 1;
            Flag = 0;
        }

        else if(status == 1)
        {
            if(Rxdata != '\r')
            {
				if(Rxdata != '\n')
				{
					string[loop] = Rxdata;
					loop++;
				}
				else
				{
					string[loop] = '\0';
					status = 2;
					loop = 0;
				}
			}
        }

        else if(status == 2)
        {
            status = 0;
            Flag = 1;
        }
        USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
    }
}

uint8_t Serial_GetTxdata(void)
{
    return Rxdata;
}

uint8_t Serial_GetFlag(void)
{
    return Flag;
}

