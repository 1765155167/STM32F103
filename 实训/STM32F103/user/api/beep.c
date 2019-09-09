#include "main.h"
//PB8
void beepInit(void)
{
	RCC->APB2ENR |= (0x1 << 3);
	
	GPIOB->CRH &= ~(0xF << 0 * 4);
	GPIOB->CRH |= (0x1 << 0*4);
	GPIOB->ODR &= ~(0x1 << 8);
	return ;
}
