#include "main.h"

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 

void uart1Init(u32 pclk2,u32 bound)
{
	float DIV;
	u32 DIV_M,DIV_F;
	RCC->APB2ENR |= (0x01 << 2);//A端口的时钟
	RCC->APB2ENR |= (0x01 << 14);//串口时钟
	GPIOA->CRH &= ~(0xFF << 4 * 1);//清零
	GPIOA->CRH |= (0x0b << 4 * 1);//复用推挽
	GPIOA->CRH |= (0x04 << 4 * 2);//浮空
	
	//串口
	USART1->CR1 = 0;
	USART1->CR1 |= (0x03 << 2);//发送使能和接收使能
	USART1->CR2 = 0;

	DIV = pclk2 * 1000000 / (bound * 16.0);
	DIV_M = (u32)DIV;
	DIV_F = (u32)((DIV - DIV_M) * 16);
	USART1->BRR = (DIV_M << 4) + DIV_F;//波特率的配置	
	USART1->CR1 |= (0x01 << 13);//使能USART1
}

