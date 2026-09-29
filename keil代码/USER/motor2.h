#ifndef _MOTOR2_H
#define _MOTOR2_H

//AIN1 AIN2:PA4 PA5 PWM PA6   BIN1 PC4 PC5 PWM PA7

#include "stm32f10x.h"
 
// 这里我们使用通用定时器TIM2
 
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
// 占空比是 PULSE / （PERIOD+1）
#define            GENERAL_TIM_PERIOD             (8000-1)
#define            GENERAL_TIM_PSC               (9-1)
#define            GENERAL_TIM_CH1_PULSE         2000
#define            GENERAL_TIM_CH2_PULSE         2000
 
#define            GENERAL_TIM_IRQ               TIM3_UP_IRQn
#define            GENERAL_TIM_IRQHandler        TIM3_UP_IRQHandler
 
//输出通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6
//输出通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7
//对PA0初始化---AIN1
#define            AIN1_GPIO_CLK                 RCC_APB2Periph_GPIOA
#define            AIN1_GPIO_PORT				 GPIOA
#define 	   	   AIN1_GPIO_PIN                 GPIO_Pin_4
//对PA1初始化---AIN2
#define            AIN2_GPIO_CLK				 RCC_APB2Periph_GPIOA
#define            AIN2_GPIO_PORT                GPIOA
#define 		   AIN2_GPIO_PIN                 GPIO_Pin_5
 
//对PB0初始化---BIN1
#define            BIN1_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define            BIN1_GPIO_PORT				 GPIOC
#define 		   BIN1_GPIO_PIN                 GPIO_Pin_4
//对PB1初始化---BIN2
#define            BIN2_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define            BIN2_GPIO_PORT				 GPIOC
#define 		   		 BIN2_GPIO_PIN                 GPIO_Pin_5
 
void AIN_GPIO_Config2(void);
void GENERAL_TIM_Init2(void);

//改变速度函数
void GENERAL_TIM_Change_PULSE2(int lun, int direction, int input_PULSE);
 
#endif


