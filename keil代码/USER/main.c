#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "openmv.h"
#include "Motor_PWM.h"
#include "motor2.h"
#include "motor3.h"
#include "tim.h"
#include "Stepper_A4988.h"
#include "xianwei.h"
#include "gd.h"
uint8_t num0;
uint8_t num1;
uint8_t num2;
uint8_t gd1,gd2;
 int main(void)
 { 
	u8 x=0;
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	LCD_Init();
	USART2_Init();//串口初始化
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
	LCD_Clear(BLACK);
	AIN_GPIO_Config();
	GENERAL_TIM_Init();
	AIN_GPIO_Config2();
	GENERAL_TIM_Init2();
	AIN_GPIO_Config3();
	GENERAL_TIM_Init3();
	MOTOR_Init();
	GENERAL_TIM_Change_PULSE3(1, 0, 100);
	Xianwei_init();
	//LCD_ShowNum(30,10,temp1,3,24);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE);//播种定时器关闭
  while(1) 
	{	
		num0=read_Value(0);
		num1=read_Value(1);
		num2=read_Value(2);
		gd1=GD_Value(0);
		gd2=GD_Value(1);
		LCD_ShowNum(30,10,num0,3,24);
		LCD_ShowNum(30,30,num1,3,24);
		LCD_ShowNum(30,50,num2,3,24);
		LCD_ShowNum(30,70,temp1,3,24);
		LCD_ShowNum(30,90,gd1,3,24);
		LCD_ShowNum(30,110,gd2,3,24);
		if(temp1==1)//履带前进
		{
			if(gd1==1)
			{
				GENERAL_TIM_Change_PULSE(1, -1, 100);//PB14 PB15  PWM PA0
				GENERAL_TIM_Change_PULSE(2, -1, 100);//PB13 PB12  PWM PA1
			}
			else
			{
				GENERAL_TIM_Change_PULSE(1, 0, 0);//PB14 PB15  PWM PA0
				GENERAL_TIM_Change_PULSE(2, 0, 0);//PB13 PB12  PWM PA1
			}
		}
		if(temp1==2)//履带后退
		{
			//my_dir=-1;
			if(gd2==1)
			{
				GENERAL_TIM_Change_PULSE(1, 1, 100);
				GENERAL_TIM_Change_PULSE(2, 1, 100);
			}
			else
			{
				GENERAL_TIM_Change_PULSE(1, 0, 0);
				GENERAL_TIM_Change_PULSE(2, 0, 0);
			}
			
		}
		
		if(temp1==3)//停止
		{
			GENERAL_TIM_Change_PULSE(1, 0, 100);
			GENERAL_TIM_Change_PULSE(2, 0, 100);//前进停
			
			GENERAL_TIM_Change_PULSE2(1, 0, 100);//旋耕器上升停止
			GENERAL_TIM_Change_PULSE2(2, 0, 100);//旋耕停
			
			GENERAL_TIM_Change_PULSE3(1, 0, 0);//抽水停止
			
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE);
		}
		
		
		if(temp1==4)//开旋耕
		{
			
			GENERAL_TIM_Change_PULSE2(1, -1, 100);//PC45  PWM  PA7
			//GENERAL_TIM_Change_PULSE2(1, 1, 100);//PA45  PWM  PA6
		}
		if(temp1==5)
		{
			
			if(num0==1)
			{
				GENERAL_TIM_Change_PULSE2(2, -1, 100);//旋耕器下降PA45  PWM  PA6
			}
			else
			{
				GENERAL_TIM_Change_PULSE2(2, 0, 0);
			}
			
		}
		if(temp1==6)
		{
			
			if(num1==1)
			{
				GENERAL_TIM_Change_PULSE2(2, 1, 100);//旋耕器上降PA4 5
			}
			else
			{
				GENERAL_TIM_Change_PULSE2(2, 0, 0);
			}
			
		}
		
		if(temp1==0)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		}
		if(temp1==7)
		{
			GENERAL_TIM_Change_PULSE3(1, 1, 100);
		}
		if(temp1==8)//开沟器下（长按）
		{
				Stepgo(1,1,2000);
		}
		if(temp1==9)//开沟器上（长按）
		{
			if(num2==1)
			{
				Stepgo(1,0,2000);
			}
			else
			{
				Stepgo(1,0,0);
			}
				
		}
		if(temp1==16)//播种定时器开
		{
			tim_Init();//播种定时器中断
		}
		if(temp1==17)//左转
		{
			GENERAL_TIM_Change_PULSE(1, 1, 100);
			GENERAL_TIM_Change_PULSE(2, -1, 100);
		}
		if(temp1==18)//右转
		{
			GENERAL_TIM_Change_PULSE(1, -1, 100);
			GENERAL_TIM_Change_PULSE(2, 1, 100);
		}
	}
}


