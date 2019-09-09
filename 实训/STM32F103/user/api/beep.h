#ifndef _BEEP_H_
#define _BEEF_H_

#define BEEP(x) x ? (GPIOB->ODR |= (0x1 << 8)):(GPIOB->ODR &= ~(0x1 << 8))
void beepInit(void);
	
#endif

