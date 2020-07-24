#include "usart1.h"

 u8 rdata[1];
 
 UART_HandleTypeDef usart1_handler; //UART���
 
 void usart1_init()
{
	usart1_handler.Instance=USART1;					    //USART1
	usart1_handler.Init.BaudRate=115200;				    //������
	usart1_handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	usart1_handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	usart1_handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	usart1_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	//usart1_handler.Init.
	usart1_handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&usart1_handler);					    //HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&usart1_handler, rdata,1);
}
 
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
   
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//��ռ���ȼ�3�������ȼ�3
	}
}

void USART1_IRQHandler(void)   
{
	
	HAL_UART_IRQHandler(&usart1_handler);
	while (HAL_UART_GetState(&usart1_handler) != HAL_UART_STATE_READY);//�ȴ�����
	while(HAL_UART_Receive_IT(&usart1_handler, (u8 *)rdata, 1) != HAL_OK);	
}
	

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  u8 rec;
  if(huart->Instance==USART1)//����Ǵ���1 
  {
		rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&usart1_handler,&rec,1,1000);
	}
	else if(huart->Instance==USART3)//����Ǵ���1 
  {
		rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&usart1_handler,&rec,1,1000);
	}
}

//usart3_init

/*
u8 rdata3[1];
 
 UART_HandleTypeDef usart3_handler; //UART���
 
 void usart3_init()
{
	usart3_handler.Instance=USART1;					    //USART1
	usart3_handler.Init.BaudRate=115200;				    //������
	usart3_handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	usart3_handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	usart3_handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	usart3_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	usart3_handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&usart3_handler);					    //HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&usart3_handler, rdata3,1);
}
 
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
   
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//��ռ���ȼ�3�������ȼ�3
	}
 	
}

void USART3_IRQHandler(void)   
{
	HAL_UART_IRQHandler(&usart3_handler);
	while (HAL_UART_GetState(&usart3_handler) != HAL_UART_STATE_READY);//�ȴ�����
	while(HAL_UART_Receive_IT(&usart3_handler, (u8 *)rdata, 1) != HAL_OK);	
}
*/
