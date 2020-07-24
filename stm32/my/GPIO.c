#include <sys.h>
#include <GPIO.h>
GPIO_InitTypeDef gpio_inits;

/*

*/
void GPIO_init(GPIO_TypeDef  *GPIOx,u8 pin,u8 mode,u8 pull){

	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	gpio_inits.Pin=pin;
	gpio_inits.Mode=mode;                 
	gpio_inits.Pull=pull;
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOx,&gpio_inits);
}





// GPIO_MODE_INPUT
// GPIO_MODE_OUTPUT_PP	          
// GPIO_MODE_OUTPUT_OD         
// GPIO_MODE_AF_PP          
// GPIO_MODE_AF_OD             
// GPIO_MODE_IT_RISING          
// GPIO_MODE_IT_FALLING        
// GPIO_MODE_IT_RISING_FALLING  
// GPIO_MODE_EVT_RISING      
// GPIO_MODE_EVT_FALLING      
// GPIO_MODE_EVT_RISING_FALLING
// GPIO_MODE_ANALOG
