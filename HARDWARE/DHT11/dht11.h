#ifndef DTH11_H
#define DTH11_H


struct DTH11 {
	unsigned int temp;//温度
	unsigned int rh;//湿度
};


/*DATA----->GPIOA7*/
unsigned int dht11_read(void);//读取原始数据
struct DTH11 dht11_read_temp_rh(void);//读取温度和湿度


#endif

