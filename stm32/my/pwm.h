#ifndef __PWM_H
#define __PWM_H
#include "sys.h"


void timer3_pwm_init(void);
void set_tim3_compare4(u32 compare);//设置输出pwm的值
void set_tim3_compare3(u32 compare);


#endif
