//************************************************************************************
//************************************************************************************
//          @DHT11温湿度传感器驱动程序 
//引脚说明：
//			VCC  3.3V~5.5V 
//			DATA PA7
//************************************************************************************
//************************************************************************************
#include "main.h"

#define DHT11_IN_L !(GPIOA->IDR & (0x1 << 7))
#define DHT11_IN_H ((GPIOA->IDR & (0x1 << 7)) == (0x1 << 7))
#define DHT11(X) X?(GPIOA->ODR |=  (0x1 << 7)):(GPIOA->ODR &= ~(0x1 << 7))

void dht11_init(void)
{
	RCC->APB2ENR |= 0x1 << 2;
	/* Configure Ports */
	GPIOA->CRL &= ~((unsigned int)0xF << 4*7);
	GPIOA->CRL |= ((unsigned int)0x1 << 4*7); 
	DHT11(1);
}

void mode_input(void)
{
	RCC->APB2ENR |= 0x1 << 2;
	/* Configure Ports */
	GPIOA->CRL &= ~((unsigned int)0xF << 4*7);
	GPIOA->CRL |= ((unsigned int)0x8 << 4*7); 
	DHT11(1);
}

void mode_output(void)
{
	RCC->APB2ENR |= 0x1 << 2;
	/* Configure Ports */
	GPIOA->CRL &= ~((unsigned int)0xF << 4*7);
	GPIOA->CRL |= ((unsigned int)0x1 << 4*7); 
	DHT11(1);
}

struct DTH11 dht11_read(void)
{
	struct DTH11 dth;
	unsigned char data[5];
	int timeout;

	DHT11(0);
	Delay_us(18000); //pulldown  for 18ms
	DHT11(1);
	Delay_us(20); //pullup for 30us
	mode_input();
	//等待dht11拉高80us
	timeout = 10;
	while (DHT11_IN_L && (timeout > 0))
	{
		Delay_us(10);
		timeout--; //wait HIGH
	}

	//等待dht11拉低80us
	timeout = 10;
	while (DHT11_IN_H && (timeout > 0))
	{
		Delay_us(10);
		timeout--; //wait LOW
	}
	for(int i = 0; i < 5; i++)
	{
	for(int j = 0; j < 8; j++)
	{
		timeout = 10;
		while (DHT11_IN_L && (timeout > 0))
		{
			Delay_us(10);
			timeout--; //wait HIGH
		}
		Delay_us(28);
		if (DHT11_IN_H)
		{
			data[i] = (data[i] << 1) + 1;
		}
		else
		{
			data[i] <<= 1;
		}
		timeout = 10;
		while (DHT11_IN_H && (timeout > 0))
		{
			Delay_us(10);
			timeout--; //wait LOW
		}
	}
	}

	mode_output();
	DHT11(1);
	if (data[4] == (data[0] + data[1] + data[2] + data[3]))
	{
		dth.rh_z = data[0];
		dth.rh_f = data[1];
		dth.temp_z = data[2];
		dth.temp_f = data[3];
	}
	else
	{
		dth.rh_z = 0;
		dth.rh_f = 0;
		dth.temp_z = 0;
		dth.temp_f = 0;
	}
	return dth;
}


