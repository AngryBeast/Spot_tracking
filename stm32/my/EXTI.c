#include "EXTI.h"
#include "led.h"
GPIO_InitTypeDef exti_gpio_init;

unsigned char state = 0;
void exti_init(void)
{
		exti_gpio_inits();
		
		HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
}

void EXTI0_IRQHandler()   											//中断线0   还有1-5独立；
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);				//调用中断处理公用函数
}


void exti_gpio_inits(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	exti_gpio_init.Pin=GPIO_PIN_0;             //PA0
  exti_gpio_init.Mode=GPIO_MODE_IT_RISING;      //GPIO_MODE_IT_RISING 上升沿触发    GPIO_MODE_IT_FALLING 下降沿
  exti_gpio_init.Pull=GPIO_PULLDOWN;          	//下拉
	
	HAL_GPIO_Init(GPIOA,&exti_gpio_init);
	
}

//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0){
			led_switch(led1,state);
			state = !state;
	}
}
