#ifndef L298N_H
#define L298N_H
#include "main.h"
/*注意speed范围300-1000*/
void Forword(uint16_t speed);//前进
void Back_Off(uint16_t speed);//后退
void Right(void);//右转
void Left(void);//左转
void Stop(void);//停车
void Change_Speed(uint16_t speed);//变速
#endif

