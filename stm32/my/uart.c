#include "uart.h"

UART_HandleTypeDef uart1_inits;
u8 buf[1];
void uart1_init(void)
{
	uart1_inits.Instance = USART1;
	uart1_inits.Init.BaudRate=115200;				    //������
	uart1_inits.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	uart1_inits.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	uart1_inits.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	uart1_inits.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	uart1_inits.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&uart1_inits);
	
	HAL_UART_Receive_IT(&uart1_inits, (u8 *)buf, 1);
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
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//��ռ���ȼ�3�������ȼ�3
	}
 	
}

void UART1_IRQHandle(void)
{
	HAL_UART_IRQHandler(&uart1_inits);
	while(HAL_UART_GetState(&uart1_inits) != HAL_UART_STATE_READY);//�ȴ�����
	while(HAL_UART_Receive_IT(&uart1_inits, (u8 *)buf, 1) != HAL_OK);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 rec;
  if(huart->Instance==USART1)//����Ǵ���1 
  {
	rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&uart1_inits,&rec,1,1000); 
  }
}





