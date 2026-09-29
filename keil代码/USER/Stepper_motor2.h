#ifndef __stepper_motor2_H
#define __stepper_motor2_H	
#include "stm32f10x.h"                  // Device header


void Driver_Init(void);
void EN_Step_Motor(int motor_num,int EN);
void Dir_change(int motor_num,int Dir);
void pulse(int motor_num,int angle);
void change_pulse(int motor_num,int pul);
void Stop_Stepper(int motor_num,u16 arr);
#endif