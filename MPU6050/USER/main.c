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

#define N 2								//��ֵ�˲�����

//ALIENTEK ̽����STM32F407������ ʵ��32
//MPU6050���ᴫ���� ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
float filter(float value_buf[]);
void Sentdate(u8 tmp_buf[33],float Product_multiple,int roll,int yaw);
int main(void)
{ 
	u8 t=0;			
	u8 key = 0;
	u8 tmp_buf[33];	
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temperature;	
	short i;
	short stay_flag = 0;
	float Product_multiple = 5;
	short temp;	
	float roll_buf[N+1];				//roll�˲�ǰ����
	float pitch_buf[N+1];				//pitch�˲�ǰ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��
	MPU_Init();					//��ʼ��MPU6050
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
//	OLED_Init();
	NRF24L01_Init();    		//��ʼ��NRF24L01 
	
	
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
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
		
		key=KEY_Scan(0);		//�õ���ֵ
		
		for(i = 0; i < N; i++)
		{
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
			{ 
				temperature = MPU_Get_Temperature();	//�õ��¶�ֵ
				MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
				MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������		
				roll_buf[i] = roll;
				pitch_buf[i] = pitch;
			}
		}
		LCD_ShowNum(30+96+96,400,Product_multiple,1,16);
				//pitch
				if(roll<0)
				{
					LCD_ShowChar(30+48,310,'-',16,0);		//��ʾ����
//					roll=-roll;		//תΪ����
				}
				else 
				LCD_ShowChar(30+48,310,' ',16,0);		//ȥ������ 
				LCD_ShowString(30,310,200,16,16,"N_ROLL=");
				LCD_ShowNum(30+48+8,310,roll*10/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,310,(short)roll*10%10,1,16);		//��ʾС������ 
				
		Sentdate(tmp_buf,Product_multiple,roll,yaw);
		
//		roll = filter(roll_buf);			//�˲��Ժ�
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
					LCD_ShowChar(30+48,230,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,230,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,230,temperature/100,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,230,temperature%10,1,16);		//��ʾС������ 
				temp=pitch*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,250,'-',16,0);		//��ʾ���� 
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,250,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,250,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,250,temp%10,1,16);		//��ʾС������ 
				temp=roll*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,270,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,270,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,270,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,270,temp%10,1,16);		//��ʾС������ 
				
				temp=yaw*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,290,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,290,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,290,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,290,temp%10,1,16);		//��ʾС������  
				
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
			if (roll < 0)					//�����ݴ���Ĵ�����׼������
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
			tmp_buf[32]=0;//���������		   
		}else
		{										   	
			LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//�����ʾ			   
		};
}



float filter(float value_buf[])							//�˲�
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
