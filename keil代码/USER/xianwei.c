#include "stm32f10x.h"                  // Device header
#include "xianwei.h"
#include "delay.h"
void Xianwei_init()//PE0 PE1 PE2
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//上拉，下拉为GPIO_Mode_IPD可能要改
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	delay_init();
}

uint8_t read_Value(int i)//此函数在中断中调用
{
	if(i==0)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==SET)
		{
			delay_ms(10);
			return 1;
		}
		
	}
	if(i==1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==SET)
		{
			delay_ms(10);
			return 1;
		}
		
	}
	if(i==2)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==SET)
		{
			delay_ms(10);
			return 1;
		}
		
	}
}