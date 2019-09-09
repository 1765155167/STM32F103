#include "main.h"

extern uint32_t runtime;//
extern STR_KEY KEY[];
extern STR_LED LED[];
extern const unsigned char gImage_test[153600];

int alarmTempMax = 0;
int alarmTempMin = 0;
int beepTime;
int dht11Time;
int NRF24L01Time;

void key_press(void);
void close(void);
void dht11_show(void);
void mystrcpy(char * a, char * b);

int main()
{
	char data[128];
	alarmTempMax = 28;
	
	Delay_Config();
	uart1Init(72,115200);
	dht11_init();
	gpio_Init();
	beepInit();
	key_Init();
	LCD_Init();
	NRF24L01_Init();
	int a = 0;
	while(NRF24L01_Check() && a < 100)
	{
		a++;
		printf("NRF24L01 Error\r\n");
		Delay_ms(100);
	}
	//	NRF24L01_RX_Mode();
	NRF24L01_TX_Mode();
	Draw_Text_8_32_Str(150,200,GRAYBLUE,BLACK,"�����");
	sprintf(data,"alarmTempMax:%d",alarmTempMax);
	Draw_Text_8_16_Str(0,70,GRAYBLUE,BLACK,(unsigned char *)data);
//	Paint_Bmp(0,0,240,320,gImage_test);
	Delay_ms(1000);
	dht11Time = runtime;
	NRF24L01Time = runtime;
	printf("��ʼ��OK!\r\n");
	while(1)
	{
		if((int)runtime - 1000 > NRF24L01Time)
		{
			NRF24L01_TxPacket("��ã�����");
			NRF24L01Time = runtime;
		}
		dht11_show();
		key_press();
		close();
	}
}

void mystrcpy(char * a, char * b)
{
	while(*b != '\0')
	{
		*a ++ = *b ++;
	}
	return ;
}

void dht11_show()
{
	struct DTH11 dth;
	char data[128];
	
	if((int)runtime - 2000 > dht11Time)
	{
		dht11Time = runtime;
		sprintf(data,"runtime:%d",runtime);
		Draw_Text_8_16_Str(0,90,GRAYBLUE,BLACK,(unsigned char *)data);
		dth = dht11_read();
		if(dth.rh_z != 0)
		{
			sprintf(data,"temp:%d.%d,rh:%d.%d",dth.temp_z,dth.temp_f,dth.rh_z,dth.rh_f);
			Draw_Text_8_16_Str(0,50,GRAYBLUE,BLACK,(unsigned char *)data);
			if(dth.temp_z > alarmTempMax)
			{
				LED[3].time = runtime;
				BEEP(1);
				beepTime = runtime;
			}
		}
	}
}
void key_press()
{
	char data[128];
	scanKey();
	if(KEY[0].Aleft) {
		KEY[0].Aleft = false;
		LED1(1);
		LED[0].time = runtime;
		LCD_PartClear(0,0,200,32,GRAYBLUE);
		if(KEY[0].pressTime <= 1000) {
			if(KEY[0].clickNum == 1) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����һ����");
				alarmTempMax += 5;
				sprintf(data,"alarmTempMax:%d",alarmTempMax);
				Draw_Text_8_16_Str(0,70,GRAYBLUE,BLACK,(unsigned char *)data);
			}
			else if(KEY[0].clickNum == 2) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����һ˫��");
			}
			else {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����һ���");
			}
		}else {
			Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����һ����");
		}
		KEY[0].clickNum = 1;
	}
	if(KEY[1].Aleft) {
		KEY[1].Aleft = false;
		LED2(1);
		LED[1].time = runtime;
		LCD_PartClear(0,0,200,32,GRAYBLUE);
		if(KEY[1].pressTime <= 1000)
		{
			if(KEY[1].clickNum == 1)
			{	
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����������");
			}
			else if(KEY[1].clickNum == 2)
			{
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"������˫��");
			}
			else
			{
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"���������");
			}
		}
		else
		{
			Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����������");
		}
		KEY[1].clickNum = 1;
	}
	if(KEY[2].Aleft) {
		KEY[2].Aleft = false;
		LED3(1);
		LED[2].time = runtime;
		LCD_PartClear(0,0,200,32,GRAYBLUE);
		if(KEY[2].pressTime <= 1000) {
			if(KEY[2].clickNum == 1) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����������");
				alarmTempMax -= 5;
				sprintf(data,"alarmTempMax:%d",alarmTempMax);
				Draw_Text_8_16_Str(0,70,GRAYBLUE,BLACK,(unsigned char *)data);
				
			} else if(KEY[2].clickNum == 2) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"������˫��");
			} else {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"���������");
			}
		}
		else {
			Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"����������");
		}
		KEY[2].clickNum = 1;
	}
	if(KEY[3].Aleft) {
		KEY[3].Aleft = false;
		LED4(1);
		LED[3].time = runtime;
		LCD_PartClear(0,0,200,32,GRAYBLUE);
		if(KEY[3].pressTime <= 1000) {
			if(KEY[3].clickNum == 1) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"�����ĵ���");
			} else if(KEY[3].clickNum == 2) {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"������˫��");
			} else {
				Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"�����Ķ��");
			}
		} else {
			Draw_Text_8_32_Str(0,0,GRAYBLUE,BLACK,"�����ĳ���");
		}
		KEY[3].clickNum = 1;
	}	
}

void close()
{
	int ledTime = 1000;//1000ms
	if(runtime > LED[0].time + ledTime) {
		LED1(0);
	}
	if(runtime > LED[1].time + ledTime) {
		LED2(0);
	}
	if(runtime > LED[2].time + ledTime) {
		LED3(0);
	}
	if(runtime > LED[3].time + ledTime) {
		LED4(0);
	}
	if(runtime > beepTime + 500)
	{
		BEEP(0);
	}
}
