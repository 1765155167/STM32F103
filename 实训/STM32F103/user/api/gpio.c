#include "main.h"

STR_LED LED[4];

void gpio_Init(void)
{
	RCC->APB2ENR |= 0x3 << 2 | 0x1 << 6;
	GPIOA->CRL &= ~(0xF << 4*5);
	GPIOA->CRL |= (0x1 << 4*5); 
	
	GPIOA->CRL &= ~(0xF << 4*6);
	GPIOA->CRL |= (0x1 << 4*6); 
	
	GPIOB->CRL &= ~(0xF << 4*5);
	GPIOB->CRL |= (0x1 << 4*5); 
	
	GPIOE->CRL &= ~(0xF << 4*5);
	GPIOE->CRL |= (0x1 << 4*5); 
	
	LED1(0);LED2(0);LED3(0);LED4(0);
	
	mystrcpy(LED[0].name, "LED1");
	mystrcpy(LED[1].name, "LED2");
	mystrcpy(LED[2].name, "LED3");
	mystrcpy(LED[3].name, "LED4");
	for(int i = 0; i < 4; i++)
	{
		LED[i].led_flag = false;
	}
	return ;
}

