#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

#include "lcd.h"
#include "sdram.h"
//#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"

#include "pwm.h"
#include "AnJian.h"
#include "oled.h"
#include "adc.h"
#include "stdlib.h"
#include "yundong.h"
#include "tim.h"
/************************************************
 ALIENTEK ������STM32F4������
 MPU6050ģ����Գ���-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

void buf_clear(char *p,u8 size);
void read_buf(u8 *p,u8 size);
void xiexian(u16 x, u16 y);
u16 input_x,input_y,x,y,now_x=0,now_y=0,init_x=4750,init_y=4609;//4310,4650
int X_nowcoordinate = 0,Y_nowcoordinate = 0;

int main(void)
{
	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
	u8 key;
	float pitch,roll,yaw; 		//ŷ����
	short temp;		
	u8 ret=0;
	char buf_x[10]={0},buf_y[10]={0};
	char Mode_buf[5];
	int Mode;
	float angle_x=0, angle_y=0,mpu_x=0,mpu_y=0;
	char str_buf[20] = {0};
	char Xielv_date[5];
	float Xielv;
	
  HAL_Init();				        //��ʼ��HAL��
  Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
  delay_init(180);                //��ʼ����ʱ����
	//uart_init(500000);		        //���ڳ�ʼ��	
  
	Anjian_init();
  LCD_Init();                     //LCD��ʼ��
	//MPU_Init();					//��ʼ��MPU6050
	timer3_pwm_init();
	POINT_COLOR=RED;			//��������Ϊ��ɫ 

	
	
	
	now_x = init_x;								//now��ǰֵ��init��ʾ��ʼֵ
	now_y = init_y;
	set_tim3_compare3(init_x);		//���ó�ʼֵ
	set_tim3_compare4(init_y);
	delay_ms(1000);
			while(1){			//������ԭ��
				buf_clear(buf_x,10);			//�������
				buf_clear(buf_y,10);
				buf_clear(Mode_buf,5);
				
				Mode = atoi(Mode_buf);
				
				switch (Mode)
				{
					case 0:
						LCD_ShowString(30,290,200,16,16,"input_x");		//��ȡx����
						read(buf_x);
						delay_ms(100);
						LCD_ShowString(115,290,200,16,16,buf_x);  //��ȡ����
					
						LCD_ShowString(30,310,200,16,16,"input_y");	 //��ȡy�������pwmֵ
						read(buf_y);
						delay_ms(100);
						LCD_ShowString(115,310,200,16,16,buf_y);			
					
						input_x = atoi(buf_x);
						input_y = atoi(buf_y);
						now_x +=input_x;
						now_y +=input_y;
					
						set_tim3_compare3(now_x);
						set_tim3_compare4(now_y);
					
					
						LCD_ShowString(30,330,200,16,16,"input_x");
						LCD_ShowNum(115,330,now_x,5,16);
						LCD_ShowString(30,360,200,16,16,"input_y");
						LCD_ShowNum(115,360,now_y,5,16);
						while(scan() != 12);
						delay_ms(1000);
						LCD_Clear(WHITE);
						now_x = init_x;
						now_y = init_y;
						set_tim3_compare3(init_x);		//�Զ�
						set_tim3_compare4(init_y);
						break;
					
					
					case 1:
						read(Xielv_date);
						Xielv = atoi(Xielv_date);
						XieLv_line(&X_nowcoordinate,&Y_nowcoordinate,50,50,Xielv);
					
						break;
					
					case 2:
						break;
						
				}
				

				

						LCD_ShowString(30,400,200,16,16,"x_now=");
						LCD_ShowNum(115,330,now_x,5,16);
						LCD_ShowString(30,440,200,16,16,"y_now=");
						LCD_ShowNum(115,360,now_y,5,16);

				

			}

}







void buf_clear(char *p,u8 size)
{
	int i;
	for(i=0;i<size;i++)
	{
		p[i]=0;
	}
}

void read_buf(u8 *p,u8 size)
{
	int i;
	for(i=0;i<size;i++)
	{
		p[i] = USART_RX_BUF[i];
	}
}

//����仯ֵ
void xiexian(u16 x, u16 y)
{
	u16 x1=0,y1=0;
	while(x1!=x||y1!=y)
	{
		if((x1*y)>(y1*x))
		{
			if(y1<y)
				y1++;
		}
		else
		{
			if(x1<x)
				x1++;
		}
		set_tim3_compare3(x1+init_x);
		set_tim3_compare4(y1+init_y);
	LCD_ShowString(30,30,200,16,16,"ing");
	}
	
}

//����ʼֵ

//��������

//����Ƕ�
//rad_x=jiaodu(input_x);
//rad_y=jiaodu(input_y);
//��ת���
/*
if((mpu_x-rad_x)==0)
{
	set_tim3_compare3(init_x);
	init_x++;
}
if((mpu_y-rad_x)==0)
{
	set_tim3_compare4(init_y);
	init_y++;
}

//init_x++;
//init_y++;
//�Ƚ��Ƿ����
*/
