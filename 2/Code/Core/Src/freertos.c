/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "Lib.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct Timer Timer;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Led_Blink_Task */
osThreadId_t Led_Blink_TaskHandle;
const osThreadAttr_t Led_Blink_Task_attributes = {
  .name = "Led_Blink_Task",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Led_2_Task */
osThreadId_t Led_2_TaskHandle;
const osThreadAttr_t Led_2_Task_attributes = {
  .name = "Led_2_Task",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Led_3_Task */
osThreadId_t Led_3_TaskHandle;
const osThreadAttr_t Led_3_Task_attributes = {
  .name = "Led_3_Task",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Timer_Task */
osThreadId_t Timer_TaskHandle;
const osThreadAttr_t Timer_Task_attributes = {
  .name = "Timer_Task",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Led_Blink_Func(void *argument);
void Led_2_Func(void *argument);
void Led_3_Func(void *argument);
void Timer_Func(void *argument);

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Led_Blink_Task */
  Led_Blink_TaskHandle = osThreadNew(Led_Blink_Func, NULL, &Led_Blink_Task_attributes);

  /* creation of Led_2_Task */
  Led_2_TaskHandle = osThreadNew(Led_2_Func, NULL, &Led_2_Task_attributes);

  /* creation of Led_3_Task */
  Led_3_TaskHandle = osThreadNew(Led_3_Func, NULL, &Led_3_Task_attributes);

  /* creation of Timer_Task */
  Timer_TaskHandle = osThreadNew(Timer_Func, NULL, &Timer_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Led_Blink_Func */
/**
* @brief Function implementing the Led_Blink_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Led_Blink_Func */
void Led_Blink_Func(void *argument)
{
  /* USER CODE BEGIN Led_Blink_Func */
  /* Infinite loop */
  for(;;)
  {
		if (Timer.Timer_Flag == true) {
			HAL_GPIO_TogglePin(Led_1_GPIO_Port, Led_1_Pin);
			osDelay(100);

		}

	}
  /* USER CODE END Led_Blink_Func */
}

/* USER CODE BEGIN Header_Led_2_Func */
/**
* @brief Function implementing the Led_2_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Led_2_Func */
void Led_2_Func(void *argument)
{
  /* USER CODE BEGIN Led_2_Func */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(Led_2_GPIO_Port, Led_2_Pin);
		osDelay(280);
  }
  /* USER CODE END Led_2_Func */
}

/* USER CODE BEGIN Header_Led_3_Func */
/**
* @brief Function implementing the Led_3_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Led_3_Func */
void Led_3_Func(void *argument)
{
  /* USER CODE BEGIN Led_3_Func */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(Led_3_GPIO_Port, Led_3_Pin);
		osDelay(170);
  }
  /* USER CODE END Led_3_Func */
}

/* USER CODE BEGIN Header_Timer_Func */
/**
* @brief Function implementing the Timer_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Timer_Func */
void Timer_Func(void *argument)
{
  /* USER CODE BEGIN Timer_Func */
  /* Infinite loop */
  for(;;)
  {
		if (Timer.cnt > 10) {
			Timer.Timer_Flag = true;
			Timer.cnt = 0;
			HAL_TIM_Base_Stop_IT(&htim13);
		}
    osDelay(1);
  }
  /* USER CODE END Timer_Func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

