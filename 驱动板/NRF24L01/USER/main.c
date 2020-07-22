#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "spi.h"
#include "key.h" 
#include "24l01.h"
#include "OLED.h"
#include "myiic.h"
#include "pwm.h"
#include "KeyBoard.h"
#include <math.h>
#include <stdlib.h>


#define SIZE sizeof(TEXT_Buffer)	 
	

 #define LEFT 2200			//3333重装载值下舵机转动的参数
 //#define MID  1900
#define MID  1845
 #define RIGHT 1600
 #define SPEED_INIT 900
void X_Steering(int yaw);
void Y_Steering(int roll);
//int las_roll,las_yaw;

int main(void)
{ 
	u16 t=0;			 
	u8 tmp_buf[33];	
	u16 temp = 0;
	char X_date[5];
	char Y_date[5];
	int roll,pitch,temperature,yaw;
	int X_coordinate,Y_coordinate;
	//int X_coordinate,Y_coordinate;
//	int las_roll,las_pitch,las_temperature,las_yaw;
	int Product_multiple;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED  
	IIC_Init();
	KeyBoard_Init();
	TIM14_PWM_Init(3333-1,84-1);	//84M/84=1Mhz的计数频率,重装载值3333，所以PWM频率为 1M/3333.3333=300hz.  飞思卡尔S-D5舵机  
	
	TIM13_PWM_Init(3333-1,84-1);
	
	//F9舵机   B6左 B7右
	TIM_SetCompare1(TIM14,MID);			//mid 电机归中
	TIM_SetCompare1(TIM4,MID);
	//las_roll = las_yaw = MID;
	printf("Init seccess\n");
	delay_ms(10);	
		while(1)
		{	  		  
			
		
				delay_ms(10);
				
//				temp = KeyBoard_scan();
//				printf("key = %d",KeyBoard_scan());
				
			read_keyBoard(X_date);
			delay_ms(1);
			read_keyBoard(Y_date);
			
			X_coordinate = atoi(X_date);
			printf("X = %d/r/n",X_coordinate );
			delay_ms(10);
			Y_coordinate = atoi(Y_date);
			printf("Y = %d/r/n",Y_coordinate );
			
			X_Steering(X_coordinate);
			delay_ms(1);
			Y_Steering(Y_coordinate);
			
			
//				if (t % 10 == 0)
//				{
//					if (yaw != las_yaw)
//					{
//						X_Steering(yaw);
//					}

//					if (roll != las_roll)
//					{
//						Y_Steering(roll);
//					}
//					
//				}

				
				delay_ms(10); 
			t++; 
		};	
	
		
}


void Y_Steering(int Y)			//+260
{
//		int result = (int)(2.6 *(roll*10));
		int result = (int)(2.6 *Y);
		//las_roll = roll;
		printf("Y Zhankong= %d\r\n",result + MID);
		TIM_SetCompare1(TIM13,MID + result);
		delay_ms(10);
}



void X_Steering(int X)			//+-150
{
	//TIM_SetCompare1(TIM14,MID+ yaw);
//	int result = 3 * (yaw/10);

	int result;
	if (X < 25)
		//result = 5.4 * (25-X);
		result = 135/25 * (25-X);
	else
		result = -(150/25 * (X-25));
	//las_yaw = yaw;
	printf("X Zhankong= %d\r\n",result + MID);
	TIM_SetCompare1(TIM14,MID+ result);
	delay_ms(10);
}
