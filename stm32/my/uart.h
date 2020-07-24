#ifndef 	__UART_H
#define 	__UART_H

#include "sys.h"

void uart3_init(void);
void uart3_gpio_init(void);
void uart1_gpio_init(void);
void uart1_init(void);
extern UART_HandleTypeDef uart1_inits;

#endif
