#ifndef DTH11_H
#define DTH11_H


struct DTH11 {
	int temp_z;//温度整数部分
	int temp_f;//温度小数部分
	int rh_z;//湿度整数部分
	int rh_f;//湿度小数部分
};


/*DATA----->GPIOA7*/
void dht11_init(void);//DTH1初始化
struct DTH11 dht11_read(void);


#endif

