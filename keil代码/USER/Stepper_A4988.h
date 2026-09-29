#ifndef _Stepper_A4988_H
#define _Stepper_A4988_H

#include "delay.h"


#define Motor_GPIO GPIOF				//PF
#define Motor_RCC RCC_APB2Periph_GPIOF

//第一个步进电机A4988的接线
#define Motor1_STEP	GPIO_Pin_12	//STEP - PF12
#define Motor1_DIR	GPIO_Pin_13	//DIR  - PF13
//第二个步进电机A4988的接线	//PB
#define Motor2_STEP	GPIO_Pin_14	//STEP - PF14
#define Motor2_DIR	GPIO_Pin_15	//DIR  - PF15  

#define Motor_GPIO1 GPIOC
#define Motor_RCC1 RCC_APB2Periph_GPIOC

//第三个步进电机A4988的接线
#define Motor3_STEP	GPIO_Pin_8	//STEP - PC8
#define Motor3_DIR	GPIO_Pin_9	//DIR  - PC9
//第四个步进电机A4988的接线	//PB
#define Motor4_STEP	GPIO_Pin_10	//STEP - PC10
#define Motor4_DIR	GPIO_Pin_11	//DIR  - PC11


void MOTOR_Init(void);
//void motor(unsigned int motor1_dir, unsigned int motor1_step, unsigned int motor2_dir, unsigned int motor2_step);
void Stepgo(unsigned int motor_num,unsigned int motor_dir,unsigned int motor_step);

#endif

