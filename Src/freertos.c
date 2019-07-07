/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "dht11.h"
#include "tim.h"
#include "l298n.h"
#include "adc.h"
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
/* USER CODE BEGIN Variables */
extern float UltrasonicWave_Distance; //超声波计算出的距离
extern uint16_t Car_Flog;//小车状态
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  默认任务:小车避障
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  /*避障算法 Start*/
	  if(Car_Flog == FORWORD)
	  {
		  if(haveObstacles() == YES)
		  {
			  printf("存在障碍物\r\n");
			  if(haveObstaclesLeft()==YES && haveObstaclesRight()==YES)//左右两端都存在障碍物
			  {
				  Back_Off(500);//后退
				  osDelay(1000);
				  Right();//大角度右转
				  osDelay(2000);
				  Forword(1000);
			  }else if(haveObstaclesLeft()==NO)//左边没有障碍物
			  {
				  Left();//左转
				  osDelay(1000);
			  }else if(haveObstaclesRight()==NO)//右边没有障碍物
			  {
				  Right();//右转
				  osDelay(1000);
			  }
		  }
	  }
      /*避障算法 End*/
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief 任务函数2用户读取温湿度
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	struct DTH11 dth;	
  /* Infinite loop */
  for(;;)
  {
	  /* 读取温湿度 start */
	  vTaskSuspendAll(); //开启调度锁
	  dth =  dht11_read_temp_rh();//读取温度和湿度
	  if(!xTaskResumeAll())      /* 关闭调度锁，如果需要任务切换，此函数返回pdTRUE，否则返回pdFALSE */
	  {
		  taskYIELD ();
	  }
	  if(dth.temp !=0 || dth.rh != 0)
	  {
		vTaskSuspendAll(); //开启调度锁
	    printf("Temp : %d \r\n", dth.temp);
	    printf("Humi : %d \r\n", dth.rh);
		if(!xTaskResumeAll())      /* 关闭调度锁，如果需要任务切换，此函数返回pdTRUE，否则返回pdFALSE */
	    {
		   taskYIELD ();
	    }
	  }
	  /*读取温湿度 end*/
    osDelay(2000);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief 任务函数三:
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	uint16_t ADC1_Value;
	uint16_t ADC2_Value;  
  /* Infinite loop */
  for(;;)
  {
	/*SR501人体红外感应 START*/
	if(HAL_GPIO_ReadPin(SR501_GPIO_Port,SR501_Pin) == 1)
	{
		vTaskSuspendAll(); //开启调度锁
		printf("Someone was detected to be active nearby.\r\n");
		if(!xTaskResumeAll())      /* 关闭调度锁，如果需要任务切换，此函数返回pdTRUE，否则返回pdFALSE */
		{
		  taskYIELD ();
		}
	}
	/*SR501人体红外感应 END*/
	/*读取ADC1_INT0(PA0) MQ-2值 start*/
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		ADC1_Value = HAL_ADC_GetValue(&hadc1);
		vTaskSuspendAll(); //开启调度锁
		#ifdef DEBUG
		printf("ADC1(PA0) Reading : %d \r\n", ADC1_Value);
		#endif
		printf("MQ-2(PA0) Value : %.2fppm \r\n", ADC1_Value*15000.0/4095 + 5000);
		if(!xTaskResumeAll())      /* 关闭调度锁，如果需要任务切换，此函数返回pdTRUE，否则返回pdFALSE */
		{
		  taskYIELD ();
		}
	}
	/*读取ADC1_INT0(PA0) MQ-2值 end*/
	/*读取ADC2_INT1(PA1) 火焰值 start*/
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, 50);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC))
	{
		ADC2_Value = HAL_ADC_GetValue(&hadc2);
		vTaskSuspendAll(); //开启调度锁
		printf("Fire : ADC2(PA1) Reading : %d \r\n", ADC2_Value);
		if(!xTaskResumeAll())      /* 关闭调度锁，如果需要任务切换，此函数返回pdTRUE，否则返回pdFALSE */
		{
			taskYIELD ();
		}
	}
	/*读取ADC2_INT1(PA1) 火焰值 end*/
    osDelay(1000);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
