#include "openmv.h"
#include "stm32f10x.h"
#include "LCD.h"
uint8_t temp1;
//这个文件是stm32接收蓝牙发送来的数据的
void USART2_Init(void){ //串口2初始化并启动
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure; //串口端口配置结构体变量
		USART_InitTypeDef USART_InitStructure; //串口参数配置结构体变量
		NVIC_InitTypeDef NVIC_InitStructure;//串口中断配置结构体变量
		 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//打开串口复用时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开PC端口时钟

    //USART2 TX  PA2；
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设定IO口的输出速度为50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2
    //USART2 RX  PA3；
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA3

    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    //USART 初始化设置
		USART_InitStructure.USART_BaudRate = 9600;//串口波特率为9600
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口1

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启ENABLE
    USART_Cmd(USART2, ENABLE);   //使能串口2

		//如下语句解决第1个字节无法正确发送出去的问题
		//USART_ClearFlag(USART2, USART_FLAG_TC);       //清串口2发送标志
}

//串口2中断处理函数
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) !=  RESET)//判断中断位
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		temp1 = USART_ReceiveData(USART2); //接收数据
		//USART_SendData(USART2,temp1);//往手机端发送数据
		//LCD_ShowNum(30,10,temp1,3,24);
	}
}
