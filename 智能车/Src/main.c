/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dht11.h"
#include "l298n.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t aTxBuffer[] = "Mr.Hu 1765155167@qq.com";
uint8_t aRxBuffer1[1];//用来接收串口1发送的数据
uint8_t aRxBuffer2[1];//用来接收串口2发送的数据
float UltrasonicWave_Distance; //超声波计算出的距离
uint16_t Car_Flog = STOP;//小车状态
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, aRxBuffer1, 1);//使能USART1 Interrupt
  HAL_UART_Receive_IT(&huart2,aRxBuffer2,1);          // Enable the USART2 Interrupt
  HAL_UART_Transmit(&huart1, aTxBuffer, sizeof(aTxBuffer),100);//使用串口1发送出去
  HAL_UART_Transmit(&huart2, aTxBuffer, sizeof(aTxBuffer),100);
  HAL_TIM_Base_Start_IT(&htim1);//启动并使能定时器中断
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//打开pwm输出 INA
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//打开pwm输出 INB
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//打开pwm输出 DJ
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* TIM1_UP_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_UP_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		HAL_UART_Transmit(&huart1,aRxBuffer1,1,100);    // 接收到数据马上使用串口1发送出去
		switch(aRxBuffer1[0])
		{
			case 'f':
				Forword(1000);
				Car_Flog = FORWORD;
				printf("前进\r\n");
				break;
			case 'b':
				Back_Off(500);
				Car_Flog = BACK;
				printf("后退\r\n");
				break;
			case 'r':Right();
				printf("左转\r\n");
				Car_Flog = RIGHT;
				break;
			case 'l':Left();
				printf("右转\r\n");
				Car_Flog = LEFT;
				break;
			case 's':Stop();
				printf("停车\r\n");
				Car_Flog = STOP;
				break;
			default :break;
		}
        HAL_UART_Receive_IT(&huart1,aRxBuffer1,1);      // 重新使能串口1接收中断
	}
	if(huart->Instance == USART2)
	{
		HAL_UART_Transmit(&huart2,aRxBuffer2,1,100);    // 接收到数据马上使用串口1发送出去
		switch(aRxBuffer2[0])
		{
			case 'f':
				Forword(1000);
				Car_Flog = FORWORD;
				printf("前进\r\n");
				break;
			case 'b':
				Back_Off(500);
				Car_Flog = BACK;
				printf("后退\r\n");
				break;
			case 'r':Right();
				printf("左转\r\n");
				Car_Flog = RIGHT;
				break;
			case 'l':Left();
				printf("右转\r\n");
				Car_Flog = LEFT;
				break;
			case 's':Stop();
				printf("停车\r\n");
				Car_Flog = STOP;
				break;
			default :break;
		}
		HAL_UART_Receive_IT(&huart2,aRxBuffer2,1);      // 重新使能串口2接收中断
	}
}
/*
 *外部中断回调函数 超声波测距
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t i = 0;
	if(GPIO_Pin == ECHO_Pin)//判断时那个引脚出触发的中断
	{
		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==0)
		{
			i++;
			if(i > 72000000)break;
		};//等待高电平
		__HAL_TIM_ENABLE(&htim2);//开启时钟
		__HAL_TIM_SET_COUNTER(&htim2,0);
		i = 0;
		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==1)
		{
			i++;
			if(i > 72000000)break;
		};//等待低电平
		__HAL_TIM_DISABLE(&htim2);//关闭定时器
		UltrasonicWave_Distance = (float)__HAL_TIM_GET_COUNTER(&htim2) / 2000 * 34;//距离计算公式：距离=高电平持续时间*声速/2   
#ifdef DEBUG
		printf("UltrasonicWave_Distance=%.2f\r\n",UltrasonicWave_Distance);
#endif
	}
}
/*
 * 描述:开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 */
void UltrasonicWave_StartMeasure(void)
{
  HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
  delay_us(20);		                      //延时20US
  HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin, GPIO_PIN_RESET);
}
uint8_t haveObstacles(void)//判断前方障碍物是否存在
{
	UltrasonicWave_StartMeasure();
	if(UltrasonicWave_Distance < 20)
	return YES;
	return NO;
}
uint8_t haveObstaclesLeft(void)//判断左方障碍物是否存在
{
	//超声波模块转到左方
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 50);
	UltrasonicWave_StartMeasure();
	if(UltrasonicWave_Distance < 20)
	return YES;
	return NO;
}
uint8_t haveObstaclesRight(void)//判断右方障碍物是否存在
{
	//超声波模块转到右方
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 150);
	UltrasonicWave_StartMeasure();
	if(UltrasonicWave_Distance < 20)
	return YES;
	return NO;
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	if(htim->Instance == TIM1)      // 判断是由哪个定时器触发的中断
	{
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	}
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  printf("Error_Handler\r\n");
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
