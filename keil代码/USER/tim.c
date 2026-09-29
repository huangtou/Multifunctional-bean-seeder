#include "tim.h"
#include "stm32f10x.h"
#include "Stepper_A4988.h"
#include "xianwei.h"
#include "lcd.h"
//TIM2_Config(1000-1,72-1);				//((1+arr )/72M)*(1+psc )=((1+999)/72M)*(1+71)=1ms
//TIM4_Config(2000-1,36000-1);    //1s

//t=（(arr+1)* (psc+1)）/时钟频率
void tim_Init(void)
{
		TIM_TimeBaseInitTypeDef timInitStructure;
		NVIC_InitTypeDef 				nvicInitStructure;
	
		//1.配置定时器时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		
		//2.配置定时器结构体
		timInitStructure.TIM_ClockDivision	= TIM_CKD_DIV1;
		timInitStructure.TIM_CounterMode	= TIM_CounterMode_Up;
		timInitStructure.TIM_Period			= 10000-1;
		timInitStructure.TIM_Prescaler		= 7200-1;
		
		TIM_TimeBaseInit(TIM5, &timInitStructure);
		//3.开启定时器中断
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM5, ENABLE);
		
		//4.配置中断结构体
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		
		nvicInitStructure.NVIC_IRQChannel					= TIM5_IRQn;
		nvicInitStructure.NVIC_IRQChannelPreemptionPriority	= 1;
		nvicInitStructure.NVIC_IRQChannelSubPriority		= 2;
		nvicInitStructure.NVIC_IRQChannelCmd				= ENABLE;
		
		NVIC_Init(&nvicInitStructure);
		
}
//5.搭建定时器中断服务函数
void TIM5_IRQHandler(void)
{
		static uint16_t t = 0;
		
		if( TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//每一秒进入一次中断
		{
				
				Stepgo(2,0,1500);//播种下步进电机
//				t=t+1;
//				if(t==5)
//				{
//					Stepgo(3,1,1500);//播种上步进电机 一个脉冲转0.1度，720个刚好是72度
//					delay_ms(100);
//					t=0;
//				}
				
			  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		}
		
		
}
