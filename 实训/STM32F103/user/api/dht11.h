#ifndef DTH11_H
#define DTH11_H


struct DTH11 {
	int temp_z;//�¶���������
	int temp_f;//�¶�С������
	int rh_z;//ʪ����������
	int rh_f;//ʪ��С������
};


/*DATA----->GPIOA7*/
void dht11_init(void);//DTH1��ʼ��
struct DTH11 dht11_read(void);


#endif

