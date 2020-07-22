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
#include <math.h>


#define SIZE sizeof(TEXT_Buffer)	 
	

 #define LEFT 2200			//3333��װ��ֵ�¶��ת���Ĳ���
 //#define MID  1900
#define MID  1845
 #define RIGHT 1600
 #define SPEED_INIT 900
void X_Steering(int yaw);
void Y_Steering(int roll);
int las_roll,las_yaw;

int main(void)
{ 
	u16 t=0;			 
	u8 tmp_buf[33];	
	int roll,pitch,temperature,yaw;
//	int las_roll,las_pitch,las_temperature,las_yaw;
	int Product_multiple;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  
	IIC_Init();
 	NRF24L01_Init();    		//��ʼ��NRF24L01 
	TIM14_PWM_Init(3333-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ3333������PWMƵ��Ϊ 1M/3333.3333=300hz.  ��˼����S-D5���  
//	TIM13_PWM_Init(1000-1,84-1);	//1M/1000 = 1000HZ, T = 1ms
	//TIM41_PWM_Init(3333-1,84-1);  //B6
	
	//TIM42_PWM_Init(3333-1,84-1);
	
	TIM13_PWM_Init(3333-1,84-1);
	
	//F9���   B6�� B7��
	TIM_SetCompare1(TIM14,MID);			//mid �������
	TIM_SetCompare1(TIM4,MID);
	las_roll = las_yaw = MID;
	printf("Init seccess\n");
	delay_ms(10);	
	while(NRF24L01_Check())
	{
		OLED_P8x16Str(0,0,"NRF24L01 Error");
		delay_ms(400);
	}
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		  
			
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				tmp_buf[32]=0;//�����ַ���������
				
				//���ݷ���
				if(tmp_buf[0] == 0)
					roll = -tmp_buf[1];
				else
					roll = tmp_buf[1];
				if(tmp_buf[2] == 0)
					pitch	= -tmp_buf[3];
				else
					pitch = tmp_buf[3];
				
				if(tmp_buf[4] == 0)
					yaw = -tmp_buf[5];
				else
					yaw = tmp_buf[5];
				
				Product_multiple = tmp_buf[6];
				
				
				
				delay_ms(10);
				
//				roll = Product_multiple*roll /10;
//				yaw = Product_multiple*yaw /10;
//				pitch = Product_multiple*pitch /10;
				
				//printf("roll = %d,pitch = %d \n\n",roll,pitch);
				
				
				if (t % 10 == 0)
				{
					if (yaw != las_yaw)
					{
						X_Steering(yaw);
					}

					if (roll != las_roll)
					{
						Y_Steering(roll);
					}
					
				}

				
				delay_ms(10);
				
			}else delay_us(100);	 
			t++; 
		};	
	
		
}


void Y_Steering(int roll)			//+260
{
//		TIM_SetCompare1(TIM13,MID + roll);
	
//		int result = (int)(2.6 *(roll*10));
		int result = (int)(2.6 *roll);
		las_roll = roll;
		printf("Y = %d\n",result + MID);
		TIM_SetCompare1(TIM13,MID + result);
		delay_ms(10);
}



void X_Steering(int yaw)			//+-150
{
	//TIM_SetCompare1(TIM14,MID+ yaw);
//	int result = 3 * (yaw/10);

	int result = 3 * yaw;
	las_yaw = yaw;
	printf("X = %d\n",result + MID);
	TIM_SetCompare1(TIM14,MID+ result);
	delay_ms(10);
}
