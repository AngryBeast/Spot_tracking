#include <stdlib.h>
#include "yundong.h"
#include "sys.h"
#include "pwm.h"
#include "Anjian.h"
#include "delay.h"


float jiaodu(u16 distance)
{
	float a,ret;
	a=atan2f(distance,1000);
	//ret = (a/PI)*6000; //（a*180*2000/(PI*180)）;计算pwm值   角度=a*180/PI  角度/180*6000==pwm比较值  
	ret = a*180/PI;
	return ret;
}

float jiaodu_y(u16 distance)  //计算y轴误差
{
	float a,ret;
	a=atan2f(distance+30,1000)-atan2f(30,1000);
	ret = a*180/PI/180*6000-distance*0.06;
	return ret;
}

float jiaodu_x(u16 distance)  //计算y轴误差
{
	float a,ret;
	a=atan2f(distance+28,1000)-atan2f(28,1000);
	ret = a*180/PI/180*6000-distance*0.1;
	return ret;
}


void Xcoordinate_Ctrl_Steering(int X)
{
	set_tim3_compare3(jiaodu_x(X));
}

void Ycoordinate_Ctrl_Steering(int Y)
{
	set_tim3_compare4(jiaodu_y(Y));
}


void draw_line(int* X_nowcoordinate, int* Y_nowcoordinate)
{
	char X_data[5],Y_data[5];
	int X1_coordinate,Y1_coordinate,X2_coordinate,Y2_coordinate;
	float Xielv;
	
	read(X_data);
	read(Y_data);
	
	X1_coordinate = atoi(X_data);
	Y1_coordinate = atoi(Y_data);
	
	read(X_data);
	read(Y_data);
	
	X2_coordinate = atoi(X_data);
	Y2_coordinate = atoi(Y_data);
	
	Xielv = fabs(((float)X1_coordinate - X2_coordinate) / (Y1_coordinate - Y2_coordinate)); 
	
	XieLv_line(&X1_coordinate,&Y1_coordinate,X2_coordinate,Y2_coordinate,Xielv);
	
	
	
}




void XieLv_line(int* X_nowcoordinate,int* Y_nowcoordinate,int Result_X,int Result_Y,float Xielv)					//第三题画线函数
{
	int temp;

	int X_temp_now,Y_temp_now;
	int X_now = *X_nowcoordinate;
	int Y_now = *Y_nowcoordinate;
	int count = 0,flag;
	int Result_X_now,Result_Y_now;
//	OLED_P8x16Str(0,32,"xielv=");
//	OLED_P8x16Str_single(64,32,(int)Xielv_coordinate);
//	OLED_P8x16Str(72,32,".");
//	OLED_P8x16Str_single(80,32,(int)Xielv_coordinate*10%10);
	
	
	if (Result_Y - Y_now < Xielv * (Result_X - X_now))		//Y先到达边界
	{
		temp = (int)((float)Result_Y / Xielv - X_now);		//求出Y到达边界时X的值
		printf(" temp =  %d",(int)((float)Result_Y / Xielv));
		
		Result_Y_now = Result_Y;
		Result_X_now = temp;					//X和Y的最终移动结果
		
		printf("Result_Y_now = %d,Result_X_now = %d",Result_Y_now,Result_X_now);
		
		flag = 1;			//Y先到达边界的情况
	}
	else					//X先到达边界
	{
		//printf(" Y_now = %d",Y_now);
		//printf(" temp =  %d",(int)((float)50 / Xielv_coordinate));
		temp = (int)((float)Result_X * Xielv);
		
		//Y_zhankong = Y_data_processing(temp);
		//X_zhankong = X_data_processing(50);	
		
		Result_X_now = Result_X;
		Result_Y_now = temp;
		
		printf("Result_Y_now = %d,Result_X_now = %d",Result_Y_now,Result_X_now);
		
		flag = 0;
	}
	
	
	Y_temp_now = Y_now;			//X的当前坐标
	X_temp_now = X_now;

	while(Y_temp_now < Result_Y_now || X_temp_now < Result_X_now)				//当X或Y没有移动到终点时执行循环
	{
		if (flag == 1)											//根据斜率来控制移动的比率
		{
			Y_temp_now += 1;
			if (count % (int)Xielv == 0)
				X_temp_now += 1;
		}
		else
		{
			X_temp_now += 1;
			if (count % (int)Xielv == 0)
				Y_temp_now += 1;
		} 
		
		if (Y_temp_now < Result_Y_now)			//Y没有移动到Y的终点
		{
			//Y_Steering(Y_data_processing(Y_temp_now));					//根据当前的点的坐标读出占空比的值再控制舵机
			
			
			//set_tim3_compare4(Y_temp_now);
			//set_tim3_compare4(jiaodu_y(Y_temp_now * 10));
			Ycoordinate_Ctrl_Steering(Y_temp_now);
			
			delay_ms(5);
		}
		if (X_temp_now < Result_X_now)
		{
			//X_Steering(X_data_processing(X_temp_now));
			
		
			Xcoordinate_Ctrl_Steering(X_temp_now);
			
			delay_ms(5);
		}
		
		count++;
		
	}
	
	//now_X = Result_X_now;				
	//now_Y = Result_Y_now;
	
	*X_nowcoordinate = Result_X;
	*Y_nowcoordinate = Result_Y;
	
}
