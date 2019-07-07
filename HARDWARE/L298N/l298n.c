#include "l298n.h"
#include "main.h"
#include "tim.h"

uint16_t pwm = 1000;

void Forword(uint16_t speed)//ǰ��
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //ʹ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //ʹ��B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}

void Back_Off(uint16_t speed)//����
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //ʹ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //ʹ��B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_SET);
}

void Right(void)//��ת
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 300);//ʹ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);//ʧ��B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}

void Left(void)//��ת
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//ʧ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 300);//ʹ��B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}
void Stop(void)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);	  //ʹ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);	  //ʹ��B
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin, GPIO_PIN_RESET);
}
void Change_Speed(uint16_t speed)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);	  //ʹ��A
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);	  //ʹ��B
	return ;
}

