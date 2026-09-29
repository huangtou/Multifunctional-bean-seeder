#include "stm32f10x.h"                  // Device header
#include "Stepper_motor2.h"

void Driver_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PC,PG端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;			 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;			 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 
	
	
 GPIO_ResetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);	//ENable使能口
 GPIO_ResetBits(GPIOG,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);	//dir方向口
}

//TIMx->PSC寄存器设置为72-1，则TIMx->ARR寄存器值为156，这样定时器的频率就是6400HZ
void Stepper_TIM_Init(u16 per,u16 psc)//per==arr
{
	GPIO_InitTypeDef	GPIO_InitStructrue;    //GPIO结构体定义
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructrue;    //时钟结构体定义
	TIM_OCInitTypeDef  TIM_OCInitStructrue;                //中断通道结构体定义
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //开启GPIO端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //开启定时器时钟

	GPIO_InitStructrue.GPIO_Mode=GPIO_Mode_AF_PP;            //引脚定义设置
	GPIO_InitStructrue.GPIO_Pin	=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;                //引脚定义设置
	GPIO_InitStructrue.GPIO_Speed =	GPIO_Speed_50MHz;        //引脚定义设置
	GPIO_Init(GPIOB, &GPIO_InitStructrue);                    //引脚定义设置

	TIM_TimeBaseInitStructrue.TIM_ClockDivision=0;                //定时器初始化设置
	TIM_TimeBaseInitStructrue.TIM_CounterMode=TIM_CounterMode_Up;//定时器初始化设置
	TIM_TimeBaseInitStructrue.TIM_Period=per;                    //定时器初始化设置
	TIM_TimeBaseInitStructrue.TIM_Prescaler=psc;                  //定时器初始化设置
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructrue);            //定时器初始化设置

	TIM_OCInitStructrue.TIM_OCMode=TIM_OCMode_PWM1;                //PWM1模式
	TIM_OCInitStructrue.TIM_OCPolarity=TIM_OCPolarity_High;        //设置PWM输出极性high
	TIM_OCInitStructrue.TIM_OutputState=TIM_OutputState_Enable;    //PWM比较输出使能
	TIM_OCInitStructrue.TIM_Pulse=0;                                //初始化脉宽为0

	TIM_OC1Init(TIM4,&TIM_OCInitStructrue);                        //初始化通道一
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM4,&TIM_OCInitStructrue);                        //初始化通道二
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM4,&TIM_OCInitStructrue);                        //初始化通道三
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM4,&TIM_OCInitStructrue);                        //初始化通道四
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);    //使能TIM4在ARR上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);
}


void EN_Step_Motor(int motor_num,int EN)
{
	if(EN==1)//开启
	{
		if(motor_num==1)
		{
			 GPIO_SetBits(GPIOC,GPIO_Pin_1);
		}
		if(motor_num==2)
		{
			 GPIO_SetBits(GPIOC,GPIO_Pin_2);
		}
		if(motor_num==3)
		{
			 GPIO_SetBits(GPIOC,GPIO_Pin_3);
		}
		if(motor_num==4)
		{
			 GPIO_SetBits(GPIOC,GPIO_Pin_4);
		}
	}
	if(EN==0)
	{
		if(motor_num==1)
		{
			 GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		}
		if(motor_num==2)
		{
			 GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		}
		if(motor_num==3)
		{
			 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		}
		if(motor_num==4)
		{
			 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		}
	}
	if(EN==3)//全开
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
	}
	if(EN==4)//全关
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	}
}

void Dir_change(int motor_num,int Dir)
{
	if(Dir==1)//顺时针转
	{
		if(motor_num==1)
		{
			 GPIO_SetBits(GPIOG,GPIO_Pin_1);
		}
		if(motor_num==2)
		{
			 GPIO_SetBits(GPIOG,GPIO_Pin_2);
		}
		if(motor_num==3)
		{
			 GPIO_SetBits(GPIOG,GPIO_Pin_3);
		}
		if(motor_num==4)
		{
			 GPIO_SetBits(GPIOG,GPIO_Pin_4);
		}
	}
	if(Dir==-1)//逆时针转
	{
		if(motor_num==1)
		{
			 GPIO_ResetBits(GPIOG,GPIO_Pin_1);
		}
		if(motor_num==2)
		{
			 GPIO_ResetBits(GPIOG,GPIO_Pin_2);
		}
		if(motor_num==3)
		{
			 GPIO_ResetBits(GPIOG,GPIO_Pin_3);
		}
		if(motor_num==4)
		{
			 GPIO_ResetBits(GPIOG,GPIO_Pin_3);
		}
	}
}

//设置脉冲宽度
void pulse(int motor_num,int angle)//下面函数调用
{
	if(motor_num==1)
	{
		TIM4->CCR1=angle;
	}
	if(motor_num==2)
	{
		TIM4->CCR2=angle;
	}
	if(motor_num==3)
	{
		TIM4->CCR3=angle;
	}
	if(motor_num==4)
	{
		TIM4->CCR4=angle;
	}
}

//int pul =156;    //默认32细分下每秒一圈，对应TIM8->ARR的值
//按键更改脉冲频率调速
//button_num为按键
//pul为脉冲宽度
void change_pulse(int motor_num,int pul)    //更改脉冲频率函数，进而改变速度,如果pul=2*pul则，可以让电机停下来
{
	TIM8->ARR=pul;
	pulse(motor_num,pul/2);            //脉冲宽度为0.5，输出标准方波
 
}

//per==arr
void Stop_Stepper(int motor_num,u16 arr)//向上计数，高电平有效，那如果比较值设置最大，一直输出低电平，就停止
{
	//通过设置比较值为最大值，脉宽为0，使步进电机停止
	if(motor_num==1)
		{
			 TIM_SetCompare1(TIM4,arr);//相当于设置CCR,
		}
		if(motor_num==2)
		{
			 TIM_SetCompare2(TIM4,arr);
		}
		if(motor_num==3)
		{
			 TIM_SetCompare3(TIM4,arr);
		}
		if(motor_num==4)
		{
			 TIM_SetCompare4(TIM4,arr);
		}
}






