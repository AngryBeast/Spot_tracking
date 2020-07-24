#ifndef __IIC_H
#define __IIC_H

#include "sys.h"

#define SDA_IN() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}
#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;}
#define IIC_SDA	PHout(5)
#define IIC_SCL	PHout(4)
#define READ_SDA PHin(5)

#endif
