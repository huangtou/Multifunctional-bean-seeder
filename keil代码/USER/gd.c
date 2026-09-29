#include "stm32f10x.h"                  // Device header


void GD_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 
}

uint8_t GD_Value(int i)
{
	if(i==0)
	{
	return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11);
	}
	if(i==1)
	{
	return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12);
	}
	if(i==2)
	{
	return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13);
	}
}