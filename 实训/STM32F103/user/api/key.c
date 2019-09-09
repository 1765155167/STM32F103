#include "main.h"

STR_KEY KEY[4];
extern uint32_t runtime;

//PA0 浮空输入
void key_Init(void)
{
	RCC->APB2ENR |= (0x1 << 2 | 0x1 << 6);
	//S2 PA0 
	GPIOA->CRL &= ~(0xF << 0);
	GPIOA->CRL |=  (0x4 << 0);
	//S3 PE4 
	GPIOE->CRL &= ~(0xF << 4 * 4);
	GPIOE->CRL |=  (0x4 << 4 * 4);
	//S3 PE3 
	GPIOE->CRL &= ~(0xF << 4 * 3);
	GPIOE->CRL |=  (0x4 << 4 * 3);
	//S3 PE2 
	GPIOE->CRL &= ~(0xF << 4 * 2);
	GPIOE->CRL |=  (0x4 << 4 * 2);
	
	for(int i =0; i < 4; i++)
	{
		KEY[i].left = false;
		KEY[i].press = false;
		KEY[i].time = 0;
		KEY[i].pressTime = 0;
		KEY[i].Aleft = false;
		KEY[i].clickNum = 1;
	}
	mystrcpy(KEY[0].name,"S2");
	mystrcpy(KEY[1].name,"S3");
	mystrcpy(KEY[2].name,"S4");
	mystrcpy(KEY[3].name,"S5");
	return ;
}

int scanKey()
{
	//按键引脚输入电平为0并且没有处于按下状态
	if (!(GPIOA->IDR & (0x1 << 0)) && !KEY[0].press)
	{
		if(KEY[0].time == 0) {
			KEY[0].time = runtime;
		} else if(runtime > KEY[0].time + 10) {//消抖后按键按下
			KEY[0].pressTime = runtime;
			KEY[0].press = true;
			KEY[0].time = 0;
		}
	}
	if ((GPIOA->IDR & (0x1 << 0)) == (0x1 << 0) && KEY[0].press == true) {//松开
		if(KEY[0].time == 0) {
			KEY[0].time = runtime;
		} else if(runtime > KEY[0].time + 10) {
			KEY[0].time = 0;
			KEY[0].pressTime = runtime - KEY[0].pressTime;
			KEY[0].press = false;
			KEY[0].left = true;
			KEY[0].leftTime = runtime;
		}
	}

	//S3 PE4
	if (!(GPIOE->IDR & (0x1 << 4)) && !KEY[1].press)
	{
		if(KEY[1].time == 0) {
			KEY[1].time = runtime;
		} else if(runtime > KEY[1].time + 10) {
			KEY[1].pressTime = runtime;
			KEY[1].press = true;
			KEY[1].time = 0;
		}
	}
	if ((GPIOE->IDR & (0x1 << 4)) == (0x1 << 4) && KEY[1].press == true) {
		if(KEY[1].time == 0) {
			KEY[1].time = runtime;
		} else if(runtime > KEY[1].time + 10) {
			KEY[1].time = 0;
			KEY[1].pressTime = runtime - KEY[1].pressTime;
			KEY[1].press = false;
			KEY[1].left = true;
			KEY[1].leftTime = runtime;
		}
	}
	//S4 PE3
	if (!(GPIOE->IDR & (0x1 << 3)) && !KEY[2].press)
	{
		if(KEY[2].time == 0) {
			KEY[2].time = runtime;
		} else if(runtime > KEY[2].time + 10) {
			KEY[2].pressTime = runtime;
			KEY[2].press = true;
			KEY[2].time = 0;
		}
	}
	if ((GPIOE->IDR & (0x1 << 3)) == (0x1 << 3) && KEY[2].press == true) {
		if(KEY[2].time == 0) {
			KEY[2].time = runtime;
		} else if(runtime > KEY[2].time + 10) {
			KEY[2].time = 0;
			KEY[2].pressTime = runtime - KEY[2].pressTime;
			KEY[2].press = false;
			KEY[2].left = true;
			KEY[2].leftTime = runtime;
		}
	}
	//S5 PE2
	if ((GPIOE->IDR & (0x1 << 2)) == (0x1 << 2)&& !KEY[3].press)
	{
		if(KEY[3].time == 0) {
			KEY[3].time = runtime;
		} else if(runtime > KEY[3].time + 10) {
			KEY[3].pressTime = runtime;
			KEY[3].press = true;
			KEY[3].time = 0;
		}
	}
	if (!(GPIOE->IDR & (0x1 << 2))  && KEY[3].press == true) {
		if(KEY[3].time == 0) {
			KEY[3].time = runtime;
		} else if(runtime > KEY[3].time + 10) {
			KEY[3].time = 0;
			KEY[3].pressTime = runtime - KEY[3].pressTime;
			KEY[3].press = false;
			KEY[3].left = true;
			KEY[3].leftTime = runtime;
		}
	}
	//判断是否为多击
	for(int i = 0 ;i < 4; i++)
	{
		if(KEY[i].left == true)//松开后150m判断按键是否又按下
		{
			if(runtime > KEY[i].leftTime + 150)
			{
				KEY[i].left	= false;
				if(KEY[i].press)
				{
					KEY[i].clickNum ++;
				}else {
					KEY[i].Aleft = true;
				}
			}
		}
	}
	return NO_PRESS;
}
