#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "OLED.h"
#include "spi.h"
#include "24l01.h"

#define N 2								//中值滤波次数

//ALIENTEK 探索者STM32F407开发板 实验32
//MPU6050六轴传感器 实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
float filter(float value_buf[]);
void Sentdate(u8 tmp_buf[33],float Product_multiple,int roll,int yaw);
int main(void)
{ 
	u8 t=0;			
	u8 key = 0;
	u8 tmp_buf[33];	
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temperature;	
	short i;
	short stay_flag = 0;
	float Product_multiple = 5;
	short temp;	
	float roll_buf[N+1];				//roll滤波前数组
	float pitch_buf[N+1];				//pitch滤波前数组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化
	MPU_Init();					//初始化MPU6050
	KEY_Init();       //初始化与按键连接的硬件接口
//	OLED_Init();
	NRF24L01_Init();    		//初始化NRF24L01 
	
	
 	POINT_COLOR=BLUE;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"Trajectory of light spot");	
	LCD_ShowString(30,90,200,16,16,"@AngryBeast");
	LCD_ShowString(30,110,200,16,16,"2020/7/19");
	while(mpu_dmp_init())
	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		delay_ms(1000);
	}
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,150,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
	LCD_ShowString(30,150,200,16,16,"NRF24L01 OK");
 	LCD_ShowString(30,230,200,16,16," Temp:    . C");	
 	LCD_ShowString(30,250,200,16,16,"Pitch:    . C");	
 	LCD_ShowString(30,270,200,16,16," Roll:    . C");	 
 	LCD_ShowString(30,290,200,16,16," Yaw :    . C");	 
	LCD_ShowString(30,400,200,16,16,"Product multiple:");
	
 	while(1)
	{
		
		key=KEY_Scan(0);		//得到键值
		
		for(i = 0; i < N; i++)
		{
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
			{ 
				temperature = MPU_Get_Temperature();	//得到温度值
				MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
				MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据		
				roll_buf[i] = roll;
				pitch_buf[i] = pitch;
			}
		}
		LCD_ShowNum(30+96+96,400,Product_multiple,1,16);
				//pitch
				if(roll<0)
				{
					LCD_ShowChar(30+48,310,'-',16,0);		//显示负号
//					roll=-roll;		//转为正数
				}
				else 
				LCD_ShowChar(30+48,310,' ',16,0);		//去掉负号 
				LCD_ShowString(30,310,200,16,16,"N_ROLL=");
				LCD_ShowNum(30+48+8,310,roll*10/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,310,(short)roll*10%10,1,16);		//显示小数部分 
				
		Sentdate(tmp_buf,Product_multiple,roll,yaw);
		
//		roll = filter(roll_buf);			//滤波以后
//		pitch = filter(pitch_buf);
		if (key)
		{
			switch(key)
			{
				case KEY0_PRES:
				{
					if(Product_multiple > 1)
					{
						Product_multiple -= 1;
					}
					else
					{
						Product_multiple /= 2;
					}
				}
				
				case KEY2_PRES:
				{
					//Sentdate(tmp_buf,Product_multiple,roll,yaw);
				}
				
			}
		}

		
		if((t%10)==0)
			{ 
				
				if(temp<0)
				{
					LCD_ShowChar(30+48,230,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,230,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,230,temperature/100,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,230,temperature%10,1,16);		//显示小数部分 
				temp=pitch*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,250,'-',16,0);		//显示负号 
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,250,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,250,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,250,temp%10,1,16);		//显示小数部分 
				temp=roll*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,270,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,270,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,270,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,270,temp%10,1,16);		//显示小数部分 
				
				temp=yaw*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,290,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,290,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,290,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,290,temp%10,1,16);		//显示小数部分  
				
				t=0;
			}
				
				
		if (t % 10 == 0)
			LED1=!LED1;
		delay_ms(10);				        
		t++; 
	} 	
}

void Sentdate(u8* tmp_buf,float Product_multiple,int roll,int yaw	)
{
		NRF24L01_TX_Mode();		   				 
		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		{			
			if (roll < 0)					//将数据存入寄存器中准备发送
			{
				tmp_buf[0] = 0;
				tmp_buf[1] = -roll;
			}
			else
			{				
				tmp_buf[0] = 1;
				tmp_buf[1] = roll;
			}
						
			if(yaw < 0)
			{
				tmp_buf[4] = 0;
				tmp_buf[5] = -yaw;
			}
			else
			{
				tmp_buf[4] = 1;
				tmp_buf[5] = yaw;
			}
			tmp_buf[6] = Product_multiple *10;
			tmp_buf[32]=0;//加入结束符		   
		}else
		{										   	
			LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//清空显示			   
		};
}



float filter(float value_buf[])							//滤波
{
	char i,j;
	float temp;
	for (j=0;j<N-1;j++)
	{
		 for (i=0;i<N-j;i++)
		 {
			if ( value_buf[i] > value_buf[i+1] )
			{
			 temp = value_buf[i];
			 value_buf[i] = value_buf[i+1]; 
			 value_buf[i+1] = temp;
			}
		 }
	}
	return value_buf[(N-1)/2];
}
