

#include <AnJian.h>
#include <delay.h>
#include <stdlib.h>
#include <oled.h>
char anjian_array[]="123A456B789C*0#D";
#if F429

void Anjian_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_inits;
	gpio_inits.Pin=GPIO_PIN_8;								//H8
	gpio_inits.Mode=GPIO_MODE_OUTPUT_PP;       //默认设为输出          
	gpio_inits.Pull=GPIO_PULLUP;								//		
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOH,&gpio_inits);			//

	gpio_inits.Pin=GPIO_PIN_14;					//B14
	HAL_GPIO_Init(GPIOB,&gpio_inits);
	
	gpio_inits.Pin=GPIO_PIN_6|GPIO_PIN_8;		//C6,C8
	HAL_GPIO_Init(GPIOC,&gpio_inits);
	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8|GPIO_PIN_6,GPIO_PIN_SET);
	
	gpio_inits.Pin=GPIO_PIN_8;						//A8	
	gpio_inits.Mode=GPIO_MODE_INPUT;       //输入          
	gpio_inits.Pull=GPIO_PULLUP;				//	上拉输入
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_inits);
	
	gpio_inits.Pin=GPIO_PIN_7;				//D5
	HAL_GPIO_Init(GPIOC,&gpio_inits);
	
	gpio_inits.Pin=GPIO_PIN_12;				//H12
	HAL_GPIO_Init(GPIOH,&gpio_inits);
	
	gpio_inits.Pin=GPIO_PIN_9;				//D4
	HAL_GPIO_Init(GPIOC,&gpio_inits);
}

int scan()
{
	int ret=0;
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8|GPIO_PIN_6,GPIO_PIN_SET);
	  unsigned int array[] = {GPIO_PIN_15,GPIO_PIN_13,GPIO_PIN_11,GPIO_PIN_9};  
//	for(i=0;i<4;i++)
//	{
//	                                                                                                                                                                                                                                            
//		HAL_GPIO_WritePin(GPIOG ,array[i],GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
//		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0)
//		{	ret = (4*i+3);break;	}
//		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0)
//		{	ret = (4*i+2);break;	}
//		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0)
//		{	ret = (4*i+1);break;	}
//		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0)
//		{	ret = (4*i+0);break;	}
//		else {	ret = 255;}
//		HAL_GPIO_WritePin(GPIOG ,array[i],GPIO_PIN_SET);
//		delay_ms(1);
//	}		
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_8,GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)==0)
		{	ret = 3;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_12)==0)
		{	ret = 2;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==0)
		{	ret = 1;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==0)
		{	ret = 0;return ret;	}
		else {	ret = 255;}
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET);
		delay_us(20);
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)==0)
		{	ret = 7;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_12)==0)
		{	ret = 6;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==0)
		{	ret = (5);return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==0)
		{	ret = (4);return ret;	}
		else {	ret = 255;}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
		
		delay_us(20);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)==0)
		{	ret = 11;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_12)==0)
		{	ret = 10;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==0)
		{	ret = 9;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==0)
		{	ret = 8;return ret;	}
		else {	ret = 255;}
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);
		delay_us(20);
		
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)==0)
		{	ret = 15;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_12)==0)
		{	ret = 14;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==0)
		{	ret = 13;return ret;	}
		else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==0)
		{	ret = 12;return ret;	}
		else {	ret = 255;}
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
		delay_us(20);
	return ret;
}
#else
void Anjian_init()
{
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_inits;
	gpio_inits.Pin=GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_9;					//PG15,PG13,PG11,PG9;
	gpio_inits.Mode=GPIO_MODE_OUTPUT_PP;       //默认设为输出          
	gpio_inits.Pull=GPIO_NOPULL;								//		
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOG,&gpio_inits);			//GPIOG初始化
	
	gpio_inits.Pin=GPIO_PIN_6|GPIO_PIN_4|GPIO_PIN_2|GPIO_PIN_0;					//PD6,PD4,PD2,PD0;
	gpio_inits.Mode=GPIO_MODE_INPUT;       //输入          
	gpio_inits.Pull=GPIO_PULLUP;				//	上拉输入
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOD,&gpio_inits);			//GPIOD初始化
	//GPIOG->ORD = 0X0000FFFF;							//输出高电平
	GPIOG->BSRR = 0X0000FFFF;
	//GPIOG->BSRR = 0XFFFF0000;
}



/* 扫描按键 */
int scan()		//左行右列，上左下右，
{
		//ODR 输出读写寄存器
		//void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIO_PinState PinState);
		//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET); //GPIOB.5 输出高

		//HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET); //GPIOB.5 输出低
	unsigned int i,ret;

	unsigned int array[] = {GPIO_PIN_15,GPIO_PIN_13,GPIO_PIN_11,GPIO_PIN_9};
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15,GPIO_PIN_SET);
	for(i=0;i<4;i++)
	{
	                                                                                                                                                                                                                                            
		HAL_GPIO_WritePin(GPIOG ,array[i],GPIO_PIN_RESET);                                                                                                                                                                                                                                                                                HAL_GPIO_WritePin(GPIOG,array[0],GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0)
		{	ret = (4*i+3);break;	}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0)
		{	ret = (4*i+2);break;	}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0)
		{	ret = (4*i+1);break;	}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0)
		{	ret = (4*i+0);break;	}
		else {	ret = 255;}
		HAL_GPIO_WritePin(GPIOG ,array[i],GPIO_PIN_SET);
		delay_ms(1);
	}
	return ret;
}
#endif

//读取按键输入的值，通过p数组返回
int read(char *p) 
{
	u8 ret,i=0,flag=0;
	
	while(i<5)
	{
		ret = scan();
		delay_ms(10);
		if(ret == scan()&&ret!=255&&flag!=1)
		{
			if(anjian_array[ret] == '*')		//输入结束
			{
				break;
			}
			else if(anjian_array[ret] == 'A')	//第一个按下A ，返回负数
			{
				p[i]='-';
				flag=1;
			}
			else
			{
				p[i]=anjian_array[ret];
				flag=1;
			}
			
			OLED_ShowChar(10,30,anjian_array[ret],16,1);
		}
		
		if(ret == 255&&flag==1)
			if(ret == scan()&&flag==1)
			{
				flag =0;
				i++;
			}
		OLED_Refresh_Gram();
	}
	return 0;
}
//没有用
int anjian_inc()
{
	int i=0,ret=0;
	while(1)
	{
		i = scan();
		if(anjian_array[i]=='A')
			ret++;
		else if(anjian_array[i]=='B')
			ret--;
		else if(anjian_array[i]=='*')
			break;
		OLED_ShowNum(30,30,ret,4,12);
	}
	OLED_Refresh_Gram();
	return ret;	
}	

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////














































void f429_anjian_init()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_inits;
	gpio_inits.Pin=GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_9;					//PB5,PB3,PB7,PB9; 上拉输入
	gpio_inits.Mode=GPIO_PULLUP;       //默认设为输出      GPIO_MODE_OUTPUT_PP    
	gpio_inits.Pull=GPIO_PULLUP;								//		
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio_inits);			//GPIOB初始化
	
	gpio_inits.Pin=GPIO_PIN_15|GPIO_PIN_14;					//PA15,PA14,	输出
	gpio_inits.Mode=GPIO_MODE_OUTPUT_PP;       //          
	gpio_inits.Pull=GPIO_NOPULL;				//	
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_inits);			//GPIOD初始化
	
	gpio_inits.Pin=GPIO_PIN_2|GPIO_PIN_7;					//PD2,PD7		输出
	gpio_inits.Mode=GPIO_MODE_OUTPUT_PP;       //         
	gpio_inits.Pull=GPIO_NOPULL;				//	
	gpio_inits.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD,&gpio_inits);			//GPIOD初始化
	GPIOG->ODR = 0X0000FFFF;						//默认输出高电平
}

//u8 read()
//{
//	unsigned char ret = 0,flag;
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15, GPIO_PIN_SET);
//	flag = GPIOB->IDR;
//	if(flag&0x000002A8)		//不为零则有按键按下
//	{
//		ret = 1;
//	}
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14, GPIO_PIN_SET);
//	flag = GPIOB->IDR;
//	if(flag&0x000002A8)		//不为零则有按键按下
//	{
//		ret = 1;
//	}
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET);
//	flag = GPIOB->IDR;
//	if(flag&0x000002A8)		//不为零则有按键按下
//	{
//		ret = 1;
//	}
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7, GPIO_PIN_SET);
//	flag = GPIOB->IDR;
//	if(flag&0x000002A8)		//不为零则有按键按下
//	{
//		ret = 1;
//	}
//	return ret;
//}

