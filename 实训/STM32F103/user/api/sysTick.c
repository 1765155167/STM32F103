#include "main.h"
//滴答定时器不需要开时钟
void configTick()
{
	SysTick->LOAD=9000000;//重装载值
	SysTick->VAL = 0;
	SysTick->CTRL &= ~(0x01 << 2);//选择时钟源内部 0:时钟(9MHZ) 1:外部(72MHZ)
	SysTick->CTRL &= ~(0x01 << 1);//定时完成不产生中断
	SysTick->CTRL |=  (0x01 << 0);//使能SysTick定时器
	while(!(SysTick->CTRL & (0x01 << 16)));
	SysTick->CTRL &= ~(0x01 << 0);
}

