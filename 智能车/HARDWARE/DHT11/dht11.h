#ifndef DTH11_H
#define DTH11_H


struct DTH11 {
	unsigned int temp;//�¶�
	unsigned int rh;//ʪ��
};


/*DATA----->GPIOA7*/
unsigned int dht11_read(void);//��ȡԭʼ����
struct DTH11 dht11_read_temp_rh(void);//��ȡ�¶Ⱥ�ʪ��


#endif

