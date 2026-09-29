#ifndef _MOTOR_PWM_H
#define _MOTOR_PWM_H
 
#include "stm32f10x.h"
 
// 这里我们使用通用定时器TIM2


#include "stm32f10x.h"
 
// 这里我们使用通用定时器TIM2
 
#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
// 占空比是 PULSE / （PERIOD+1）
#define            GENERAL_TIM_PERIOD             (8000-1)
#define            GENERAL_TIM_PSC               (9-1)
#define            GENERAL_TIM_CH1_PULSE         2000
#define            GENERAL_TIM_CH2_PULSE         2000
 
#define            GENERAL_TIM_IRQ               TIM2_UP_IRQn
#define            GENERAL_TIM_IRQHandler        TIM2_UP_IRQHandler
 
//输出通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_0
//输出通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_1
//对PA0初始化---AIN1
#define            AIN1_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define            AIN1_GPIO_PORT				 GPIOB
#define 	   	   AIN1_GPIO_PIN                 GPIO_Pin_14
//对PA1初始化---AIN2
#define            AIN2_GPIO_CLK				 RCC_APB2Periph_GPIOB
#define            AIN2_GPIO_PORT                GPIOB
#define 		   AIN2_GPIO_PIN                 GPIO_Pin_15
 
//对PB0初始化---BIN1
#define            BIN1_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define            BIN1_GPIO_PORT				 GPIOB
#define 		   BIN1_GPIO_PIN                 GPIO_Pin_13
//对PB1初始化---BIN2
#define            BIN2_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define            BIN2_GPIO_PORT				 GPIOB
#define 		   		 BIN2_GPIO_PIN                 GPIO_Pin_12
 
void AIN_GPIO_Config(void);
void GENERAL_TIM_Init(void);

//改变速度函数
void GENERAL_TIM_Change_PULSE(int lun, int direction, int input_PULSE);
#endif

