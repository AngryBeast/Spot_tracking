#include "uart.h"

UART_HandleTypeDef uart1_inits;
u8 buf[1];
void uart1_init(void)
{
	uart1_inits.Instance = USART1;
	uart1_inits.Init.BaudRate=115200;				    //波特率
	uart1_inits.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	uart1_inits.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	uart1_inits.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	uart1_inits.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	uart1_inits.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&uart1_inits);
	
	HAL_UART_Receive_IT(&uart1_inits, (u8 *)buf, 1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
   
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//抢占优先级3，子优先级3
	}
 	
}

void UART1_IRQHandle(void)
{
	HAL_UART_IRQHandler(&uart1_inits);
	while(HAL_UART_GetState(&uart1_inits) != HAL_UART_STATE_READY);//等待就绪
	while(HAL_UART_Receive_IT(&uart1_inits, (u8 *)buf, 1) != HAL_OK);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 rec;
  if(huart->Instance==USART1)//如果是串口1 
  {
	rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&uart1_inits,&rec,1,1000); 
  }
}





