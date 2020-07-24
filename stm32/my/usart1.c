#include "usart1.h"

 u8 rdata[1];
 
 UART_HandleTypeDef usart1_handler; //UART句柄
 
 void usart1_init()
{
	usart1_handler.Instance=USART1;					    //USART1
	usart1_handler.Init.BaudRate=115200;				    //波特率
	usart1_handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	usart1_handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	usart1_handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	usart1_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	//usart1_handler.Init.
	usart1_handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&usart1_handler);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&usart1_handler, rdata,1);
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
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//抢占优先级3，子优先级3
	}
}

void USART1_IRQHandler(void)   
{
	
	HAL_UART_IRQHandler(&usart1_handler);
	while (HAL_UART_GetState(&usart1_handler) != HAL_UART_STATE_READY);//等待就绪
	while(HAL_UART_Receive_IT(&usart1_handler, (u8 *)rdata, 1) != HAL_OK);	
}
	

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  u8 rec;
  if(huart->Instance==USART1)//如果是串口1 
  {
		rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&usart1_handler,&rec,1,1000);
	}
	else if(huart->Instance==USART3)//如果是串口1 
  {
		rec=*(--(huart->pRxBuffPtr));
    HAL_UART_Transmit(&usart1_handler,&rec,1,1000);
	}
}

//usart3_init

/*
u8 rdata3[1];
 
 UART_HandleTypeDef usart3_handler; //UART句柄
 
 void usart3_init()
{
	usart3_handler.Instance=USART1;					    //USART1
	usart3_handler.Init.BaudRate=115200;				    //波特率
	usart3_handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	usart3_handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	usart3_handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	usart3_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	usart3_handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&usart3_handler);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&usart3_handler, rdata3,1);
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
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//抢占优先级3，子优先级3
	}
 	
}

void USART3_IRQHandler(void)   
{
	HAL_UART_IRQHandler(&usart3_handler);
	while (HAL_UART_GetState(&usart3_handler) != HAL_UART_STATE_READY);//等待就绪
	while(HAL_UART_Receive_IT(&usart3_handler, (u8 *)rdata, 1) != HAL_OK);	
}
*/
