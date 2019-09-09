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
extern float UltrasonicWave_Distance; //������������ľ���
extern uint16_t Car_Flog;//С��״̬
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
  * @brief  Ĭ������:С������
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
	  /*�����㷨 Start*/
	  if(Car_Flog == FORWORD)
	  {
		  if(haveObstacles() == YES)
		  {
			  printf("�����ϰ���\r\n");
			  if(haveObstaclesLeft()==YES && haveObstaclesRight()==YES)//�������˶������ϰ���
			  {
				  Back_Off(500);//����
				  osDelay(1000);
				  Right();//��Ƕ���ת
				  osDelay(2000);
				  Forword(1000);
			  }else if(haveObstaclesLeft()==NO)//���û���ϰ���
			  {
				  Left();//��ת
				  osDelay(1000);
			  }else if(haveObstaclesRight()==NO)//�ұ�û���ϰ���
			  {
				  Right();//��ת
				  osDelay(1000);
			  }
		  }
	  }
      /*�����㷨 End*/
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief ������2�û���ȡ��ʪ��
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
	  /* ��ȡ��ʪ�� start */
	  vTaskSuspendAll(); //����������
	  dth =  dht11_read_temp_rh();//��ȡ�¶Ⱥ�ʪ��
	  if(!xTaskResumeAll())      /* �رյ������������Ҫ�����л����˺�������pdTRUE�����򷵻�pdFALSE */
	  {
		  taskYIELD ();
	  }
	  if(dth.temp !=0 || dth.rh != 0)
	  {
		vTaskSuspendAll(); //����������
	    printf("Temp : %d \r\n", dth.temp);
	    printf("Humi : %d \r\n", dth.rh);
		if(!xTaskResumeAll())      /* �رյ������������Ҫ�����л����˺�������pdTRUE�����򷵻�pdFALSE */
	    {
		   taskYIELD ();
	    }
	  }
	  /*��ȡ��ʪ�� end*/
    osDelay(2000);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief ��������:
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
	/*SR501��������Ӧ START*/
	if(HAL_GPIO_ReadPin(SR501_GPIO_Port,SR501_Pin) == 1)
	{
		vTaskSuspendAll(); //����������
		printf("Someone was detected to be active nearby.\r\n");
		if(!xTaskResumeAll())      /* �رյ������������Ҫ�����л����˺�������pdTRUE�����򷵻�pdFALSE */
		{
		  taskYIELD ();
		}
	}
	/*SR501��������Ӧ END*/
	/*��ȡADC1_INT0(PA0) MQ-2ֵ start*/
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		ADC1_Value = HAL_ADC_GetValue(&hadc1);
		vTaskSuspendAll(); //����������
		#ifdef DEBUG
		printf("ADC1(PA0) Reading : %d \r\n", ADC1_Value);
		#endif
		printf("MQ-2(PA0) Value : %.2fppm \r\n", ADC1_Value*15000.0/4095 + 5000);
		if(!xTaskResumeAll())      /* �رյ������������Ҫ�����л����˺�������pdTRUE�����򷵻�pdFALSE */
		{
		  taskYIELD ();
		}
	}
	/*��ȡADC1_INT0(PA0) MQ-2ֵ end*/
	/*��ȡADC2_INT1(PA1) ����ֵ start*/
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, 50);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC))
	{
		ADC2_Value = HAL_ADC_GetValue(&hadc2);
		vTaskSuspendAll(); //����������
		printf("Fire : ADC2(PA1) Reading : %d \r\n", ADC2_Value);
		if(!xTaskResumeAll())      /* �رյ������������Ҫ�����л����˺�������pdTRUE�����򷵻�pdFALSE */
		{
			taskYIELD ();
		}
	}
	/*��ȡADC2_INT1(PA1) ����ֵ end*/
    osDelay(1000);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
