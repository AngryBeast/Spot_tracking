#include "tim.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
#include "lcd.h"

float pitch,roll,yaw;
float mpu_x,mpu_y;
short temp;
TIM_HandleTypeDef timer4_handler;
void timer4_init(){
	
	timer4_handler.Instance=TIM4;
	timer4_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer4_handler.Init.Period = 4999;
	timer4_handler.Init.Prescaler = 8999;
	timer4_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	HAL_TIM_Base_Start_IT(&timer4_handler);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM4_CLK_ENABLE();
	
	HAL_NVIC_SetPriority(TIM4_IRQn,1,3);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&timer4_handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//	{
//			mpu_x = roll;
//			mpu_y = yaw;
//			temp=roll*10;
//			if(temp<0)
//			{
//				LCD_ShowChar(30+48,240,'-',16,0);		//显示负号
//				temp=-temp;		//转为正数
//			}else LCD_ShowChar(30+48,240,' ',16,0);		//去掉负号 
//			LCD_ShowNum(30+48+8,240,temp/10,3,16);		//显示整数部分	    
//			LCD_ShowNum(30+48+40,240,temp%10,1,16);		//显示小数部分 
//			temp=yaw*10;
//			if(temp<0)
//			{
//				LCD_ShowChar(30+48,260,'-',16,0);		//显示负号
//				temp=-temp;		//转为正数
//			}else LCD_ShowChar(30+48,260,' ',16,0);		//去掉负号 
//			LCD_ShowNum(30+48+8,260,temp/10,3,16);		//显示整数部分	    
//			LCD_ShowNum(30+48+40,260,temp%10,1,16);		//显示小数部分
//		}
}
