#include "pwm.h"

TIM_HandleTypeDef timer3_pwm_handler;

void timer3_pwm_init()
{
	timer3_pwm_handler.Instance=TIM3;
	timer3_pwm_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer3_pwm_handler.Init.Period = 9999;			//计数值    300 0000/10000=300
	timer3_pwm_handler.Init.Prescaler = 29;		//分频值   90M/30 = 3M = 300 0000
	timer3_pwm_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&timer3_pwm_handler);
	
	TIM_OC_InitTypeDef pwm_channel_handler;
	pwm_channel_handler.OCMode = TIM_OCMODE_PWM1;
	pwm_channel_handler.Pulse = 4310;                                                
	pwm_channel_handler.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&timer3_pwm_handler,&pwm_channel_handler,TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&timer3_pwm_handler,&pwm_channel_handler,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&timer3_pwm_handler,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&timer3_pwm_handler,TIM_CHANNEL_4);
	
}                                                  
void set_tim3_compare4(u32 compare)
{
	TIM3->CCR4 = compare;
}

void set_tim3_compare3(u32 compare)
{
	TIM3->CCR3 = compare;
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_Initure;
	GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_0; //PB1和PB0
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; 
	GPIO_Initure.Pull=GPIO_PULLUP; 
	GPIO_Initure.Speed=GPIO_SPEED_HIGH; 
	GPIO_Initure.Alternate= GPIO_AF2_TIM3; 
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	

}

/*
	timer3_pwm_handler.Init.Period = 9999;			//计数值    300 0000/10000 =300			[4500,7500]
	timer3_pwm_handler.Init.Prescaler = 29;			//分频值   	90M/30 = 3M = 300 0000

	timer3_pwm_handler.Init.Period = 19999;			//计数值			100/2 = 50							[500,2500]	
	timer3_pwm_handler.Init.Prescaler = 89;			//分频值   	90M/90 = 100 0000
*/


