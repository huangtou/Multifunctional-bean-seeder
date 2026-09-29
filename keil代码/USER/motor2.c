#include "motor2.h"
#include "stm32f10x.h"                  // Device header
 
 
//AIN1 AIN2:PA4 PA5 PWM PA6   BIN1 PC4 PC5 PWM PA7
void AIN_GPIO_Config2(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//AIN1
	RCC_APB2PeriphClockCmd(AIN1_GPIO_CLK,ENABLE);		 //开启时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	 //50MHz
	GPIO_InitStruct.GPIO_Pin = AIN1_GPIO_PIN;
	GPIO_Init(AIN1_GPIO_PORT ,&GPIO_InitStruct);
	GPIO_SetBits(AIN1_GPIO_PORT,AIN1_GPIO_PIN);			//初始化			
	//AIN2
	RCC_APB2PeriphClockCmd(AIN2_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = AIN2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(AIN2_GPIO_PORT ,&GPIO_InitStruct);
	GPIO_SetBits(AIN2_GPIO_PORT,AIN2_GPIO_PIN);
	//BIN1
	RCC_APB2PeriphClockCmd(BIN1_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = BIN1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BIN1_GPIO_PORT ,&GPIO_InitStruct);
	GPIO_SetBits(BIN1_GPIO_PORT,BIN1_GPIO_PIN);
	//BIN2
	RCC_APB2PeriphClockCmd(BIN2_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = BIN2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BIN2_GPIO_PORT ,&GPIO_InitStruct);
	GPIO_SetBits(BIN2_GPIO_PORT,BIN2_GPIO_PIN);
}
static void GENERAL_TIM_GPIO_Config2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	//输出比较通道1GPIO初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = GENERAL_TIM_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	//输出比较通道2GPIO初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = GENERAL_TIM_CH2_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
}
static void GENERAL_TIM_Mode_Config2(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 开启定时器时钟,即内部时钟CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
    /*--------------------时基结构体初始化-------------------------*/
	
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_PSC;	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	/*--------------------输出比较结构体初始化-------------------*/		
	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// 设置占空比大小GENERAL_TIM_CH1_PULSE=2000
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CH1_PULSE;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	// 设置占空比大小GENERAL_TIM_CH2_PULSE=2000
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CH2_PULSE;
	TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	// 使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}
void GENERAL_TIM_Init2(void)
{
	GENERAL_TIM_Mode_Config2();
	GENERAL_TIM_GPIO_Config2(); 
}
/*正负表示正转和反转，0表示停止
	PERIOD = 8000-1固定
	*/
void GENERAL_TIM_Change_PULSE2(int lun, int direction, int input_PULSE)
{
	
	int PULSE = (GENERAL_TIM_PERIOD + 1) * input_PULSE / 100;//input_PULSE设置为最高为100
 
	if(lun == 1)
	{
//		TIM_SetCompare1(TIM2, input_PULSE);
		GENERAL_TIM->CCR1 = PULSE;	
		if(direction == 0)//停止
		{
			GPIO_WriteBit(AIN1_GPIO_PORT,AIN1_GPIO_PIN,Bit_RESET);
			GPIO_WriteBit(AIN2_GPIO_PORT,AIN2_GPIO_PIN,Bit_RESET);
		}
		else if(direction == 1)//正转
		{
			GPIO_WriteBit(AIN1_GPIO_PORT,AIN1_GPIO_PIN,Bit_RESET);
			GPIO_WriteBit(AIN2_GPIO_PORT,AIN2_GPIO_PIN,Bit_SET);
		}
		else if(direction == -1)//反转
		{
			GPIO_WriteBit(AIN1_GPIO_PORT,AIN1_GPIO_PIN,Bit_SET);
			GPIO_WriteBit(AIN2_GPIO_PORT,AIN2_GPIO_PIN,Bit_RESET);
		}
	}
	if(lun == 2)
	{
//		TIM_SetCompare2(TIM2, input_PULSE);
		GENERAL_TIM->CCR2 = PULSE;
		if(direction == 0)//停止
		{
			GPIO_WriteBit(BIN1_GPIO_PORT,BIN1_GPIO_PIN,Bit_RESET);
			GPIO_WriteBit(BIN2_GPIO_PORT,BIN2_GPIO_PIN,Bit_RESET);
		}
		else if(direction == 1)//正转
		{
			GPIO_WriteBit(BIN1_GPIO_PORT,BIN1_GPIO_PIN,Bit_RESET);
			GPIO_WriteBit(BIN2_GPIO_PORT,BIN2_GPIO_PIN,Bit_SET);
		}
		else if(direction == -1)//反转
		{
			GPIO_WriteBit(BIN1_GPIO_PORT,BIN1_GPIO_PIN,Bit_SET);
			GPIO_WriteBit(BIN2_GPIO_PORT,BIN2_GPIO_PIN,Bit_RESET);
		}
	}
}