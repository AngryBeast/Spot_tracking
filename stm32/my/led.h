#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define led0 0
#define led1 1


void led_init(void);
void led_switch(unsigned char led,unsigned char status);

void led_init_429(void);
void led_switch_429(unsigned char status);
#endif 

