#ifndef _KEY_H_
#define _KEY_H_

enum KEY_FLAG{
	KEY1_PRESS = 0x1,
	KEY2_PRESS,
	KEY3_PRESS,
	KEY4_PRESS,
	NO_PRESS
};

void key_Init(void);
int scanKey(void);

#endif

