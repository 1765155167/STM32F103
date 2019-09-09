#include "main.h"

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 

void uart1Init(u32 pclk2,u32 bound)
{
	float DIV;
	u32 DIV_M,DIV_F;
	RCC->APB2ENR |= (0x01 << 2);//A�˿ڵ�ʱ��
	RCC->APB2ENR |= (0x01 << 14);//����ʱ��
	GPIOA->CRH &= ~(0xFF << 4 * 1);//����
	GPIOA->CRH |= (0x0b << 4 * 1);//��������
	GPIOA->CRH |= (0x04 << 4 * 2);//����
	
	//����
	USART1->CR1 = 0;
	USART1->CR1 |= (0x03 << 2);//����ʹ�ܺͽ���ʹ��
	USART1->CR2 = 0;

	DIV = pclk2 * 1000000 / (bound * 16.0);
	DIV_M = (u32)DIV;
	DIV_F = (u32)((DIV - DIV_M) * 16);
	USART1->BRR = (DIV_M << 4) + DIV_F;//�����ʵ�����	
	USART1->CR1 |= (0x01 << 13);//ʹ��USART1
}

