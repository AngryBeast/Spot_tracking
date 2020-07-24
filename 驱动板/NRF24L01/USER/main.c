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
	
#define SOURCE 1995
#define LEFT 2200			//3333重装载值下舵机转动的参数
 //#define MID  1900
#define MID  1845
 #define RIGHT 1600
 #define SPEED_INIT 900
void X_Steering(int yaw);
void Y_Steering(int roll);
//int las_roll,las_yaw;
int X_data_processing(int X);
int Y_data_processing(int Y);
void XieLv_line();
int X_now = 0,Y_now = 0;

int main(void)
{ 
	u16 t=0;			 
	u8 tmp_buf[33];	
	u16 temp = 0;
	char X_date[5];
	char Y_date[5];
	char Mode_date[5];
	int roll,pitch,temperature,yaw;
	int X_coordinate,Y_coordinate,Mode_coordinate;
	int Product_multiple;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED  
	IIC_Init();
	OLED_Init();
	KeyBoard_Init();
	TIM14_PWM_Init(3333-1,84-1);	//84M/84=1Mhz的计数频率,重装载值3333，所以PWM频率为 1M/3333.3333=300hz.  飞思卡尔S-D5舵机  
	TIM13_PWM_Init(3333-1,84-1);
	OLED_P8x16Str(0,0,"X=");
	OLED_P8x16Str_single(16,0,X_now);
	OLED_P8x16Str(64,0,"Y=");
	OLED_P8x16Str_single(80,0,Y_now);
	X_Steering(SOURCE);							//刚开始时指向原点
	Y_Steering(MID);
	printf("Init seccess\n");
	delay_ms(10);	
		while(1)
		{	  		  
			
			OLED_P8x16Str_single(16,0,X_now/10);			//显示X和Y坐标
			OLED_P8x16Str_single(24,0,X_now%10);
			OLED_P8x16Str_single(80,0,Y_now/10);
			OLED_P8x16Str_single(88,0,Y_now%10);
			delay_ms(10);
				
			read_keyBoard(Mode_date);								//从矩阵键盘中读入模式选项
			Mode_coordinate = atoi(Mode_date);
			switch(Mode_coordinate)
			{
				case 0:																//移动至点模式
								printf("PointMode");
								read_keyBoard(X_date);				//从矩阵键盘中读取值
								delay_ms(1);
								read_keyBoard(Y_date);
			
								X_coordinate = atoi(X_date);					//将其转化为整形
								printf("X = %d/r/n",X_coordinate );
								X_now = X_coordinate;
								delay_ms(10);
								Y_coordinate = atoi(Y_date);
								printf("Y = %d/r/n",Y_coordinate );
								Y_now = Y_coordinate;
				
								X_Steering(X_data_processing(X_coordinate));
								delay_ms(1);
								Y_Steering(Y_data_processing(Y_coordinate));
								break;
				
				
				case 1:																//画线模式
								printf("XieLvMode");
								XieLv_line();
								break;
			}
			

			
			
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			X_Steering(SOURCE);
//			Y_Steering(MID);
			
				
			delay_ms(10); 
			t++; 
		};	
	
		
}


void XieLv_line()					//第三题画线函数
{
	char Xielv_date[5];
	float Xielv_coordinate;
	int temp;
	int X_zhankong,Y_zhankong;
	int X_zhankong_now,Y_zhankong_now;
	int X_temp_now,Y_temp_now;
	//float X_zhankong_now_f,Y_zhankong_now_f;
	int count = 0,flag;
	int Result_X_now,Result_Y_now;
	read_keyBoard(Xielv_date);				//从矩阵键盘读取输入的数据
	Xielv_coordinate = atof(Xielv_date);	//将数据转从字符数组型化成浮点型
//	OLED_P8x16Str(0,32,"xielv=");
//	OLED_P8x16Str_single(64,32,(int)Xielv_coordinate);
//	OLED_P8x16Str(72,32,".");
//	OLED_P8x16Str_single(80,32,(int)Xielv_coordinate*10%10);
	if (50 - Y_now < Xielv_coordinate * (50 - X_now))		//Y先到达边界
	{
		temp = (int)((float)50 / Xielv_coordinate - X_now);		//求出Y到达边界时X的值
		printf(" temp =  %d",(int)((float)50 / Xielv_coordinate));
		//Y_zhankong = Y_data_processing(50);
		//X_zhankong = X_data_processing(temp);
		
		Result_Y_now = 50;
		Result_X_now = temp;					//X和Y的最终移动结果
		
		printf("Result_Y_now = %d,Result_X_now = %d",Result_Y_now,Result_X_now);
		
		flag = 1;			//Y先到达边界的情况
	}
	else					//X先到达边界
	{
		//printf(" Y_now = %d",Y_now);
		//printf(" temp =  %d",(int)((float)50 / Xielv_coordinate));
		temp = (int)(((float)50 / Xielv_coordinate) - Y_now);
		
		//Y_zhankong = Y_data_processing(temp);
		//X_zhankong = X_data_processing(50);	
		
		Result_X_now = 50;
		Result_Y_now = temp;
		
		printf("Result_Y_now = %d,Result_X_now = %d",Result_Y_now,Result_X_now);
		
		flag = 0;
	}
	
	Y_zhankong_now = Y_data_processing(Y_now); 		//好像没用到
	X_zhankong_now = X_data_processing(X_now);
	
	Y_temp_now = Y_now;			//X的当前坐标，其实是题目要求0,0
	X_temp_now = X_now;

	while(Y_temp_now < Result_Y_now || X_temp_now < Result_X_now)				//当X或Y没有移动到终点时执行循环
	{
		if (flag == 1)											//根据斜率来控制移动的比率
		{
			Y_temp_now += 1;
			if (count % (int)Xielv_coordinate == 0)
				X_temp_now += 1;
		}
		else
		{
			X_temp_now += 1;
			if (count % (int)Xielv_coordinate == 0)
				Y_temp_now += 1;
		}
		
		if (Y_temp_now < Result_Y_now)			//Y没有移动到Y的终点
		{
			Y_Steering(Y_data_processing(Y_temp_now));					//根据当前的点的坐标读出占空比的值再控制舵机
			delay_ms(5);
		}
		if (X_temp_now < Result_X_now)
		{
			X_Steering(X_data_processing(X_temp_now));
			delay_ms(5);
		}
		
		count++;
		
	}
	
	X_now = Result_X_now;				
	Y_now = Result_Y_now;
	
}



void Y_Steering(int Y)			//输入占空比控制舵机
{
		printf("Y Zhankong= %d\r\n",Y);
		TIM_SetCompare1(TIM13,Y);
		delay_ms(10);
}



void X_Steering(int X)			//+-150
{
		printf("X Zhankong= %d\r\n",X);
		TIM_SetCompare1(TIM14,X);
		delay_ms(10);
}

int X_data_processing(int X)			//根据输入的X读出占空比
{
	int X_zhankong = SOURCE;
	//printf("X = %d\r\n",X);
	switch(X)
	{
		case 0:X_zhankong = 1995;break;
		case 1:X_zhankong = MID;X_zhankong = 1990;break;
		case 2:X_zhankong = MID;X_zhankong = 1980;break;
		case 3:X_zhankong = MID;X_zhankong = 1975;break;
		case 4:X_zhankong = 1970;break;
		case 5:X_zhankong = 1965;break;
		case 6:X_zhankong = 1955;break;
		case 7:X_zhankong = 1950;break;
		case 8:X_zhankong = 1949;break;
		case 9:X_zhankong = 1948;break;
		case 10:X_zhankong = 1943;break;
		case 11:X_zhankong = 1930;break;
		case 12:X_zhankong = 1925;break;
		case 13:X_zhankong = 1918;break;
		case 14:X_zhankong = 1915;break;
		case 15:X_zhankong = 1910;break;
		case 16:X_zhankong = 1900;break;
		case 17:X_zhankong = 1895;break;
		case 18:X_zhankong = 1890;break;
		case 19:X_zhankong = 1882;break;
		case 20:X_zhankong = 1877;break;
		case 21:X_zhankong = 1872;break;
		case 22:X_zhankong = 1865;break;
		case 23:X_zhankong = 1860;break;
		case 24:X_zhankong = 1855;break;
		case 25:X_zhankong = 1850;break;
		case 26:X_zhankong = 1840;break;
		case 27:X_zhankong = 1833;break;
		case 28:X_zhankong = 1828;break;
		case 29:X_zhankong = 1822;break;
		case 30:X_zhankong = 1815;break;
		case 31:X_zhankong = 1810;break;
		case 32:X_zhankong = 1803;break;
		case 33:X_zhankong = 1796;break;
		case 34:X_zhankong = 1792;break;
		case 35:X_zhankong = 1785;break;
		case 36:X_zhankong = 1780;break;
		case 37:X_zhankong = 1773;break;
		case 38:X_zhankong = 1766;break;
		case 39:X_zhankong = 1759;break;
		case 40:X_zhankong = 1754;break;
		case 41:X_zhankong = 1750;break;
		case 42:X_zhankong = 1745;break;
		case 43:X_zhankong = 1739;break;
		case 44:X_zhankong = 1733;break;
		case 45:X_zhankong = 1726;break;
		case 46:X_zhankong = 1720;break;
		case 47:X_zhankong = 1710;break;
		case 48:X_zhankong = 1703;break;
		case 49:X_zhankong = 1702;break;
		case 50:X_zhankong = 1700;break;
		
															
	}
	return X_zhankong;
	
	
}




int Y_data_processing(int Y)
{
	int Y_zhankong = MID;
	//printf("Y = %d\r\n",Y);
	switch(Y)
	{
		case 0:Y_zhankong = 1845;break;
		case 1:Y_zhankong = 1900;Y_zhankong = 1850;break;
		case 2:Y_zhankong = 1900;Y_zhankong = 1855;break;
		case 3:Y_zhankong = 1900;Y_zhankong = 1860;break;
		case 4:Y_zhankong = 1863;break;
		case 5:Y_zhankong = 1868;break;
		case 6:Y_zhankong = 1871;break;
		case 7:Y_zhankong = 1878;break;
		case 8:Y_zhankong = 1883;break;
		case 9:Y_zhankong = 1889;break;
		case 10:Y_zhankong = 1895;break;
		case 11:Y_zhankong = 1900;break;
		case 12:Y_zhankong = 1907;break;
		case 13:Y_zhankong = 1912;break;
		case 14:Y_zhankong = 1915;break;
		case 15:Y_zhankong = 1920;break;
		case 16:Y_zhankong = 1926;break;
		case 17:Y_zhankong = 1932;break;
		case 18:Y_zhankong = 1934;break;
		case 19:Y_zhankong = 1938;break;
		case 20:Y_zhankong = 1943;break;
		case 21:Y_zhankong = 1953;break;
		case 22:Y_zhankong = 1955;break;
		case 23:Y_zhankong = 1963;break;
		case 24:Y_zhankong = 1966;break;
		case 25:Y_zhankong = 1970;break;
		case 26:Y_zhankong = 1972;break;
		case 27:Y_zhankong = 1978;break;
		case 28:Y_zhankong = 1985;break;
		case 29:Y_zhankong = 1991;break;
		case 30:Y_zhankong = 1998;break;
		case 31:Y_zhankong = 2001;break;
		case 32:Y_zhankong = 2005;break;
		case 33:Y_zhankong = 2012;break;
		case 34:Y_zhankong = 2017;break;
		case 35:Y_zhankong = 2019;break;
		case 36:Y_zhankong = 2028;break;
		case 37:Y_zhankong = 2034;break;
		case 38:Y_zhankong = 2035;break;
		case 39:Y_zhankong = 2036;break;
		case 40:Y_zhankong = 2043;break;
		case 41:Y_zhankong = 2046;break;
		case 42:Y_zhankong = 2051;break;
		case 43:Y_zhankong = 2057;break;
		case 44:Y_zhankong = 2063;break;
		case 45:Y_zhankong = 2070;break;
		case 46:Y_zhankong = 2071;break;
		case 47:Y_zhankong = 2073;break;
		case 48:Y_zhankong = 2078;break;
		case 49:Y_zhankong = 2083;break;
		case 50:Y_zhankong = 2091;break;
		case 1900:Y_zhankong = 1900;break;
		case 1950:Y_zhankong = 1950;break;
															
	}
	return Y_zhankong;
	
	
}

