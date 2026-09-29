#ifndef _MOTOR3_H
#define _MOTOR3_H

#include "stm32f10x.h"
 
// 这里我们使用通用定时器TIM1
 
#define            GENERAL_TIM                   TIM1
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB2Periph_TIM1
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
// 占空比是 PULSE / （PERIOD+1）
#define            GENERAL_TIM_PERIOD             (8000-1)
#define            GENERAL_TIM_PSC               (9-1)
#define            GENERAL_TIM_CH1_PULSE         2000
#define            GENERAL_TIM_CH2_PULSE         2000
#define            GENERAL_TIM_CH3_PULSE         2000
#define            GENERAL_TIM_CH4_PULSE         2000

#define            GENERAL_TIM_IRQ               TIM1_UP_IRQn
#define            GENERAL_TIM_IRQHandler        TIM1_UP_IRQHandler
 
//输出通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_8
//输出通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_9

//输出通道3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH3_PORT          GPIOA
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_10

//输出通道4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH4_PORT          GPIOA
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_11



//对PF0初始化---AIN1
#define            AIN1_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            AIN1_GPIO_PORT				 GPIOF
#define 	   	   AIN1_GPIO_PIN                 GPIO_Pin_0
//对PF1初始化---AIN2
#define            AIN2_GPIO_CLK				 RCC_APB2Periph_GPIOF
#define            AIN2_GPIO_PORT                GPIOF
#define 		   AIN2_GPIO_PIN                 GPIO_Pin_1
 
//对PF2初始化---BIN1
#define            BIN1_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            BIN1_GPIO_PORT				 GPIOF
#define 		   BIN1_GPIO_PIN                 GPIO_Pin_2
//对PF3初始化---BIN2
#define            BIN2_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            BIN2_GPIO_PORT				 GPIOF
#define 		   		 BIN2_GPIO_PIN                 GPIO_Pin_3

//对PF4初始化---CIN1
#define            CIN1_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            CIN1_GPIO_PORT				 GPIOF
#define 		   CIN1_GPIO_PIN                 GPIO_Pin_4
//对PF5初始化---CIN2
#define            CIN2_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            CIN2_GPIO_PORT				 GPIOF
#define 		   		 CIN2_GPIO_PIN                 GPIO_Pin_5

//对PF4初始化---DIN1
#define            DIN1_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            DIN1_GPIO_PORT				 GPIOF
#define 		   DIN1_GPIO_PIN                 GPIO_Pin_6
//对PF5初始化---CIN2
#define            DIN2_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define            DIN2_GPIO_PORT				 GPIOF
#define 		   		 DIN2_GPIO_PIN                 GPIO_Pin_7


void AIN_GPIO_Config3(void);
void GENERAL_TIM_Init3(void);

//改变速度函数
void GENERAL_TIM_Change_PULSE3(int lun, int direction, int input_PULSE);
 



#endif