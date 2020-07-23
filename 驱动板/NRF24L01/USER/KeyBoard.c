#include "sys.h"
#include "delay.h" 
#include "keyBoard.h"


char Key_array[]="123A456B789C*0#D";

void  KeyBoard_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);   
  
} 


int KeyBoard_scan()	
{
	unsigned int i,ret = 0;

	unsigned int array[] = {GPIO_Pin_15,GPIO_Pin_13,GPIO_Pin_11,GPIO_Pin_9};//横向 
	GPIO_SetBits(GPIOG,GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15);//纵向 
	for(i=0;i<4;i++)
	{
	                                                                                                                                                                                                                                            
		GPIO_ResetBits(GPIOG ,array[i]);    
    //GPIO_ResetBits(GPIOD ,GPIO_Pin_15);                                                                                                                                                                                                                                         HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)==0)
		{	ret = (4*i+3);break;	}
		else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
		{	ret = (4*i+2);break;	}
		else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)==0)
		{	ret = (4*i+1);break;	}
		else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)==0)
		{	ret = (4*i+0);break;	}
		else {	ret = 255;}
		GPIO_SetBits(GPIOG ,array[i]);
		delay_ms(1);
	}
	return ret;
}

void read_keyBoard(char *p) 
{
	u8 ret,i=0,flag=0;
	while(Key_array[KeyBoard_scan()] == '*')
	{}
		
	while(i<5)
	{
		ret = KeyBoard_scan();
		delay_ms(10);
		if(ret == KeyBoard_scan()&&ret!=255&&flag!=1)
		{
			if(Key_array[ret] == '*')		//输入结束
			{
				break;
			}
			else if(Key_array[ret] == 'D')	//按下D键，默认输入0；
			{
				p = "0";
				flag=1;
				return;
			}
//			else if(Key_array[ret] == 'B')	//按下D键，默认输入0；
//			{
//				flag=1;
//				return 1;   //模式1
//			}
//			else if(Key_array[ret] == 'C')	//按下D键，默认输入0；
//			{
//				flag=1;
//				return 2;   //模式2
//			}
			else if(Key_array[ret] == 'A')	//第一个按下A ，返回负数
			{
				p[i]='-';
				flag=1;
			}
			else
			{
				p[i]=Key_array[ret];
				flag=1;
			}
			
		}
		
		if(ret == 255&&flag==1)
			if(ret == KeyBoard_scan()&&flag==1)
			{
				flag =0;
				i++;
			}
	}
}
