//************************************************************************************
//************************************************************************************
//          @DHT11温湿度传感器驱动程序 
//引脚说明：
//			VCC  +5V 
//			DATA PA7
//************************************************************************************
//************************************************************************************
#include "dht11.h"
#include "tim.h"
#include "main.h"

void mode_input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
   
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

void mode_output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
   
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

unsigned int dht11_read(void)
{
    int i;
    long long val;
    int timeout;
	#ifdef DEBUG
	printf("dht11 read start\r\n");
	#endif
	
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);
    HAL_Delay(18); //pulldown  for 18ms
	#ifdef DEBUG
	printf("pulldown  for 18ms start\r\n");
	#endif
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);
    delay_us(30); //pullup for 30us
	
    #ifdef DEBUG
	printf("pullup for 30us\r\n");
	#endif
	mode_input();
    //等待dht11拉高80us
    timeout = 5000;
    while ((!HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) && (timeout > 0))
    {
        timeout--; //wait HIGH
    }
	
    //等待dht11拉低80us
    timeout = 5000;
    while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) && (timeout > 0))
    {
        timeout--; //wait LOW
    }
	
#define CHECK_TIME 28
    for (i = 0; i < 40; i++)
    {
        timeout = 5000;
        while ((!HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) && (timeout > 0))
        {
            timeout--; //wait HIGH
        }

        delay_us(CHECK_TIME);
        if (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))
        {
            val = (val << 1) + 1;
        }
        else
        {
            val <<= 1;
        }
        timeout = 5000;
        while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) && (timeout > 0))
        {
            timeout--; //wait LOW
        }
    }

    mode_output();
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);
    if (((val >> 32) + (val >> 24) + (val >> 16) + (val >> 8) - val) & 0xff)
    {
		#ifdef DEBUG
		printf("dht11 read error\r\n");
		#endif
        return 0; //校验
    }
    else
    {
		#ifdef DEBUG
		printf("dht11 read ok\r\n");
		#endif
        return val >> 8;
    }
}
struct DTH11 dht11_read_temp_rh(void)//读取温度和湿度
{
	struct DTH11 dth;
	unsigned int val = dht11_read();
	dth.rh = (val & 0xFFFF0000) >> 24;
	dth.temp = (val & 0x0000FFFF) >> 8;
	
	return dth;
}


