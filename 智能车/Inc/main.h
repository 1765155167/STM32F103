/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void UltrasonicWave_StartMeasure(void);//∂¡»°≥¨…˘≤®æ‡¿Î
uint8_t haveObstacles(void);//≈–∂œ’œ∞≠ŒÔ «∑Ò¥Ê‘⁄
uint8_t haveObstaclesLeft(void);
uint8_t haveObstaclesRight(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOE
#define MQ_2_Pin GPIO_PIN_0
#define MQ_2_GPIO_Port GPIOA
#define Fire_Pin GPIO_PIN_1
#define Fire_GPIO_Port GPIOA
#define DJ_Pin GPIO_PIN_1
#define DJ_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_11
#define IN1_GPIO_Port GPIOE
#define IN2_Pin GPIO_PIN_12
#define IN2_GPIO_Port GPIOE
#define IN3_Pin GPIO_PIN_13
#define IN3_GPIO_Port GPIOE
#define IN4_Pin GPIO_PIN_14
#define IN4_GPIO_Port GPIOE
#define ECHO_Pin GPIO_PIN_7
#define ECHO_GPIO_Port GPIOC
#define ECHO_EXTI_IRQn EXTI9_5_IRQn
#define TRIG_Pin GPIO_PIN_8
#define TRIG_GPIO_Port GPIOC
#define SR501_Pin GPIO_PIN_3
#define SR501_GPIO_Port GPIOD
#define DHT11_Pin GPIO_PIN_4
#define DHT11_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOB
#define INA_Pin GPIO_PIN_6
#define INA_GPIO_Port GPIOB
#define INB_Pin GPIO_PIN_7
#define INB_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define FORWORD (uint8_t)0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define STOP 4
#define YES 5
#define NO 6
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
