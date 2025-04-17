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
#include "usart.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct Uart Uart;
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
/* Definitions for Serial_event_Task */
osThreadId_t Serial_event_TaskHandle;
const osThreadAttr_t Serial_event_Task_attributes = {
  .name = "Serial_event_Task",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Process_Task */
osThreadId_t Process_TaskHandle;
const osThreadAttr_t Process_Task_attributes = {
  .name = "Process_Task",
  .stack_size = 150 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Serial_event_Func(void *argument);
void Process_Func(void *argument);

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

  /* creation of Serial_event_Task */
  Serial_event_TaskHandle = osThreadNew(Serial_event_Func, NULL, &Serial_event_Task_attributes);

  /* creation of Process_Task */
  Process_TaskHandle = osThreadNew(Process_Func, NULL, &Process_Task_attributes);

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
		if (Uart.Event_Flag == true) {
			Uart.ptr = Uart.ptr + 1;
			HAL_UART_Transmit(&huart1, Uart.Rx_buffer, 1, 10);
			Uart.buffer[Uart.ptr - 1] = Uart.Rx_buffer[0];
			switch (Uart.Rx_buffer[0]) {
			case 0x0D:
				Uart.ptr = 0;
				HAL_UART_Transmit(&huart1, "\r\n", 2, 10);
				memset(Uart.command, '\0', 20);
				memcpy(Uart.command, Uart.buffer, 20);
				memset(Uart.buffer, '\0', 20);
				Uart.ready = true;
				break;
			case 0x7F:

				break;
			}
			Uart.Event_Flag = false;
			osDelay(1);
		}

	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Serial_event_Func */
/**
* @brief Function implementing the Serial_event_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Serial_event_Func */
void Serial_event_Func(void *argument)
{
  /* USER CODE BEGIN Serial_event_Func */
  /* Infinite loop */
  for(;;)
  {
	  HAL_UART_Receive_IT(&huart1, &Uart.Rx_buffer, sizeof(Uart.Rx_buffer));
    osDelay(10);
  }
  /* USER CODE END Serial_event_Func */
}

/* USER CODE BEGIN Header_Process_Func */
/**
* @brief Function implementing the Process_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Process_Func */
void Process_Func(void *argument)
{
  /* USER CODE BEGIN Process_Func */
  /* Infinite loop */
  for(;;)
  {
	  if (Uart.ready == true) {
		  if (strcmp((char *)Uart.command , "led1-off\r") == 0) {
			  HAL_GPIO_WritePin(Led_1_GPIO_Port, Led_1_Pin, GPIO_PIN_SET);
		}
		  if (strcmp((char *)Uart.command , "led1-on\r") == 0) {
			  HAL_GPIO_WritePin(Led_1_GPIO_Port, Led_1_Pin, GPIO_PIN_RESET);
		}
		  Uart.ready = false;

	}

    osDelay(1);
  }
  /* USER CODE END Process_Func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

