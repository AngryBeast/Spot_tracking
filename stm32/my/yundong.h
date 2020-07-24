#ifndef __YUNDONG_H
#define __YUNDONG_H

#include "sys.h"
#include <math.h>

#define PI 3.1415

float jiaodu(u16 distance);
float jiaodu_y(u16 distance);
float jiaodu_x(u16 distance);
void XieLv_line(int* X_nowcoordinate,int* Y_nowcoordinate,int Result_X,int Result_Y,float Xielv);
void Xcoordinate_Ctrl_Steering(int X);
void Ycoordinate_Ctrl_Steering(int Y);
#endif

