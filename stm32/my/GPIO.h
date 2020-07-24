#ifndef __GPIO_H
#define __GPIO_H
#include "sys.h"

void GPIO_init(GPIO_TypeDef  *GPIOx,u8 pin,u8 mode,u8 pull);

//HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_x);
//HAL_GPIO_WritePin(GPIOx,GPIO_PIN_x,GPIO_PIN_SET);   SET÷√1 RESET÷√0




#endif
