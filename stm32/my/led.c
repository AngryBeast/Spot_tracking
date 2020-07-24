#include "led.h"

GPIO_InitTypeDef GPIO_inits;
void led_init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_inits.Pin=GPIO_PIN_0|GPIO_PIN_1;
	GPIO_inits.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_inits.Pull=GPIO_PULLUP;
	GPIO_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(GPIOB,&GPIO_inits);
}


void led_switch(unsigned char led,unsigned char states)
{
	if(led == led0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, states);
	}
	else if(led == led1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, states);
	}
}

void led_init_429()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_inits.Pin=GPIO_PIN_14;
	GPIO_inits.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_inits.Pull=GPIO_PULLUP;
	GPIO_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(GPIOD,&GPIO_inits);
}

void led_switch_429(unsigned char states)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, states);
}