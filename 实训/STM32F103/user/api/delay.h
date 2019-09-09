#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f10x.h"

void Delay_Config(void);
void TIM4_Config(uint16_t psc,uint16_t arr);
void Delay_nus(uint32_t time);
void Delay_nms(uint32_t time);
void Delay_ms(uint32_t time);
void Delay_us(uint32_t time);

#endif
