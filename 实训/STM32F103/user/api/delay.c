#include "delay.h"
extern uint32_t runtime;//保存系统的运行时间

/*
函数名称：Delay_Config
函数功能：滴答时钟初始化--1ms
函数参数：无
函数返回值：无
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
函数名称：Delay_ms
函数功能：ms延时
函数参数：time
函数返回值：无
*/
void Delay_ms(uint32_t time)
{
	uint32_t time1 = runtime;//保存当前系统运行的时间
	while(runtime-time1<time);
}
/*
函数名称：TIM4_Config
函数功能：us延时
函数参数：psc --分频   arr --重装载值
函数返回值：无
*/
void TIM4_Config(uint16_t psc,uint16_t arr)
{
	//打开时钟TIM4
	RCC->APB1ENR |= (1<<2);
	//配置TIM4
	TIM4->CNT = 0;
	TIM4->PSC = psc-1;
	TIM4->ARR = arr-1;

	TIM4->CR1 = 0;
	//使能更新中断
	TIM4->DIER |= (1<<0);
	//优先级配置  占先3 ，次级3  11 11
	NVIC_SetPriority(TIM4_IRQn,0xf);
	//使能中断通道
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM4->CR1 &=~ (1<<0);//失能计数器
}
uint32_t  ustime=0;
void TIM4_IRQHandler(void)
{
	//清中断
	TIM4->SR &=~ (1<<0);
	if(ustime>0)ustime--;
}
/*
函数名称：Delay_us
函数功能：us延时
函数参数：time
函数返回值：无
*/
void Delay_us(uint32_t time)
{
	ustime =time;
	TIM4->CNT=0;
	TIM4->CR1 |= (1<<0);//使能计数器
	while(ustime);
	TIM4->CR1 &=~ (1<<0);//使能计数器
}
/*
函数名称：Delay_nus
函数功能：us延时
函数参数：time
函数返回值：无
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
函数名称：Delay_nms
函数功能：ms延时
函数参数：time
函数返回值：无
*/
void Delay_nms(uint32_t time)
{
	while(time--)
		Delay_nus(1000);
}

