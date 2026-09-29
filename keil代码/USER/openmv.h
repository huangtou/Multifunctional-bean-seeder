#ifndef __OPENMV_H_
#define __OPENMV_H_
#include "stm32f10x.h"

extern u16 USART1_RX_STA;         		//接受状态标记	


extern u8 state;
extern uint8_t temp1;
void USART2_Init(void);//串口2初始化并启动
#endif
