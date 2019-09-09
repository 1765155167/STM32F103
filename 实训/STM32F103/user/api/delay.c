#include "delay.h"
extern uint32_t runtime;//����ϵͳ������ʱ��

/*
�������ƣ�Delay_Config
�������ܣ��δ�ʱ�ӳ�ʼ��--1ms
������������
��������ֵ����
*/
void Delay_Config(void)
{
	if(SysTick_Config(72000) == 1)//ms
	{
		while(1);
	}
	TIM4_Config(36, 2);  //1us
}

/*
�������ƣ�Delay_ms
�������ܣ�ms��ʱ
����������time
��������ֵ����
*/
void Delay_ms(uint32_t time)
{
	uint32_t time1 = runtime;//���浱ǰϵͳ���е�ʱ��
	while(runtime-time1<time);
}
/*
�������ƣ�TIM4_Config
�������ܣ�us��ʱ
����������psc --��Ƶ   arr --��װ��ֵ
��������ֵ����
*/
void TIM4_Config(uint16_t psc,uint16_t arr)
{
	//��ʱ��TIM4
	RCC->APB1ENR |= (1<<2);
	//����TIM4
	TIM4->CNT = 0;
	TIM4->PSC = psc-1;
	TIM4->ARR = arr-1;

	TIM4->CR1 = 0;
	//ʹ�ܸ����ж�
	TIM4->DIER |= (1<<0);
	//���ȼ�����  ռ��3 ���μ�3  11 11
	NVIC_SetPriority(TIM4_IRQn,0xf);
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM4->CR1 &=~ (1<<0);//ʧ�ܼ�����
}
uint32_t  ustime=0;
void TIM4_IRQHandler(void)
{
	//���ж�
	TIM4->SR &=~ (1<<0);
	if(ustime>0)ustime--;
}
/*
�������ƣ�Delay_us
�������ܣ�us��ʱ
����������time
��������ֵ����
*/
void Delay_us(uint32_t time)
{
	ustime =time;
	TIM4->CNT=0;
	TIM4->CR1 |= (1<<0);//ʹ�ܼ�����
	while(ustime);
	TIM4->CR1 &=~ (1<<0);//ʹ�ܼ�����
}
/*
�������ƣ�Delay_nus
�������ܣ�us��ʱ
����������time
��������ֵ����
*/
void Delay_nus(uint32_t time)
{
	while(time--)
	{
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	}
}
/*
�������ƣ�Delay_nms
�������ܣ�ms��ʱ
����������time
��������ֵ����
*/
void Delay_nms(uint32_t time)
{
	while(time--)
		Delay_nus(1000);
}

