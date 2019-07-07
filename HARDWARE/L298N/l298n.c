#include "l298n.h"
#include "main.h"
#include "tim.h"

uint16_t pwm = 1000;

void Forword(uint16_t speed)//前进
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //使能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //使能B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}

void Back_Off(uint16_t speed)//后退
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //使能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //使能B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_SET);
}

void Right(void)//右转
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 300);//使能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);//失能B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}

void Left(void)//左转
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//失能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 300);//使能B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}
void Stop(void)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);	  //使能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);	  //使能B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}
void Change_Speed(uint16_t speed)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //使能A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //使能B
	return ;
}

