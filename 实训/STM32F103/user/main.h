#ifndef _MAIN_H_
#define _MAIN_H_

#include "gpio.h"
#include "stm32f10x.h"
#include "delay.h"
#include "pwm.h"
#include "sysTick.h"
#include "stdio.h"
#include "beep.h"
#include "key.h"
#include "uart.h"
#include "lcd.h"
#include "zi.h"
#include "dht11.h"
#include "bit.h"
#include "NRF24L01.h"
#include "stdio.h"
#include "math.h"

typedef enum bool{
	false = 0x0,
	true,
}bool;

typedef struct LED {
	char name[5];
	bool led_flag;
	unsigned int time;
}STR_LED;

typedef struct KEY {
	char name[5];
	bool press;
	bool left;
	bool Aleft;//按键真实按下并松开
	unsigned int leftTime;
	unsigned int time;
	unsigned int pressTime;
	unsigned int clickNum;
}STR_KEY;

void mystrcpy(char * a, char * b);

#endif

