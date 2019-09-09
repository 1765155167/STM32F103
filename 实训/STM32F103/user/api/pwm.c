#include "main.h" 

extern uint32_t runtime;//

void heart_led(int f)
{
	if(runtime%1000 > f)
	{
		LED1(1);
	}else
	{
		LED1(0);
	}
}

