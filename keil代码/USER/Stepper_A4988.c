#include "Stepper_A4988.h"
/*GPIO_motornum和GPIOx用于选择电机，GPIO_direction用于选择电机方向，dir：0为逆1为正，k为90°的倍数*/

//每次 0.1°
#include "stm32f10x.h"                  // Device header
void MOTOR_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(Motor_RCC,ENABLE);
	 RCC_APB2PeriphClockCmd(Motor_RCC1,ENABLE);
	//Motor初始化
	GPIO_InitStructure.GPIO_Pin = Motor1_STEP|Motor1_DIR|Motor2_STEP|Motor2_DIR;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO,&GPIO_InitStructure);	// 初始化GPIOF
	GPIO_ResetBits(Motor_GPIO,Motor1_STEP);			//初始化GPIOF_12输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor1_DIR);			//初始化GPIOF_13输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor2_STEP);			//初始化GPIOF_14输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor2_DIR);			//初始化GPIOF_15输出低电平
	
	GPIO_InitStructure.GPIO_Pin = Motor3_STEP|Motor3_DIR|Motor4_STEP|Motor4_DIR;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO1,&GPIO_InitStructure);	// 初始化GPIOF
	GPIO_ResetBits(Motor_GPIO1,Motor3_STEP);			//初始化GPIOF_12输出低电平
	GPIO_ResetBits(Motor_GPIO1,Motor3_DIR);			//初始化GPIOF_13输出低电平
	GPIO_ResetBits(Motor_GPIO1,Motor4_STEP);			//初始化GPIOF_14输出低电平
	GPIO_ResetBits(Motor_GPIO1,Motor4_DIR);			//初始化GPIOF_15输出低电平
}
//motor 1-4  motor 0,1各表示一个方向，motor_step表示转多少个90度
void Stepgo(unsigned int motor_num,unsigned int motor_dir,unsigned int motor_step)//一个step转90度
{
	unsigned int i;
	if(motor_num==1)
	{
		switch(motor_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO,Motor1_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO,Motor1_DIR); break; 
			default : break; 
		}
		for(i=0;i<motor_step;i++)
		{
			GPIO_SetBits(Motor_GPIO,Motor1_STEP);
			delay_us(200);									
			GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
			delay_us(200);
		}
	}
	
	if(motor_num==2)//下面
	{
		switch(motor_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO,Motor2_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO,Motor2_DIR); break; 
			default : break; 
		}
		for(i=0;i<motor_step;i++)
		{
			GPIO_SetBits(Motor_GPIO,Motor2_STEP);
			delay_us(1000);									//周期1.3ms
			GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
			delay_us(1000);
		}
	}
	if(motor_num==3)//上
	{
		switch(motor_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO,Motor3_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO,Motor3_DIR); break; 
			default : break; 
		}
		for(i=0;i<motor_step;i++)
		{
			GPIO_SetBits(Motor_GPIO1,Motor3_STEP);
			delay_us(500);									//周期1.3ms
			GPIO_ResetBits(Motor_GPIO1,Motor3_STEP);
			delay_us(500);
		}
	}
	if(motor_num==4)
	{
		switch(motor_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO1,Motor4_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO1,Motor4_DIR); break; 
			default : break; 
		}
		for(i=0;i<motor_step;i++)
		{
			GPIO_SetBits(Motor_GPIO1,Motor4_STEP);
			delay_ms(1);									//周期1.3ms
			GPIO_ResetBits(Motor_GPIO1,Motor4_STEP);
			delay_ms(1);
		}
	}
}

