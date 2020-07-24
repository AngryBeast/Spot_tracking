#include "EXTI.h"
#include "led.h"
GPIO_InitTypeDef exti_gpio_init;

unsigned char state = 0;
void exti_init(void)
{
		exti_gpio_inits();
		
		HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
}

void EXTI0_IRQHandler()   											//�ж���0   ����1-5������
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);				//�����жϴ����ú���
}


void exti_gpio_inits(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	exti_gpio_init.Pin=GPIO_PIN_0;             //PA0
  exti_gpio_init.Mode=GPIO_MODE_IT_RISING;      //GPIO_MODE_IT_RISING �����ش���    GPIO_MODE_IT_FALLING �½���
  exti_gpio_init.Pull=GPIO_PULLDOWN;          	//����
	
	HAL_GPIO_Init(GPIOA,&exti_gpio_init);
	
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0){
			led_switch(led1,state);
			state = !state;
	}
}
