/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file           : main.c
	* @brief          : Main program body
	******************************************************************************
	* @attention
	*
	* <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "i2c.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define APP_TASK_START_STK_SIZE 128u
/* Task Priority */
#define APP_TASK_START_PRIO 1u

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Task Control Block */
static OS_TCB AppTaskStartTCB;
/* Task Stack */
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void AppTaskStart(void *p_arg);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*int main(void) {
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	while(1) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
		HAL_Delay(500);
	}
}*/
int main(void)
{
  /* To store error code */
  OS_ERR os_err;

  /* Initialize uC/OS-III */
  OSInit(&os_err);

  if (os_err != OS_ERR_NONE)
  {
	while (DEF_TRUE)
	  ;
  }

  OSTaskCreate(
	  /* pointer to task control block */
	  (OS_TCB *)&AppTaskStartTCB,
	  /* task name can be displayed by debuggers */
	  (CPU_CHAR *)"App Task Start",
	  /* pointer to the task */
	  (OS_TASK_PTR)AppTaskStart,
	  /* pointer to an OPTIONAL data area */
	  (void *)0,
	  /* task priority: the lower the number, the higher the priority */
	  (OS_PRIO)APP_TASK_START_PRIO,
	  /* pointer to task's stack base addr */
	  (CPU_STK *)&AppTaskStartStk[0],
	  /* task's stack limit to monitor and ensure that the stack 
	   * doesn't overflow (10%) */
	  (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10,
	  /* task's stack size */
	  (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
	  /* max number of message that the task can receive through 
	   * internal message queue (5) */
	  (OS_MSG_QTY)5u,
	  /* amount of clock ticks for the time quanta 
	   * when round robin is enabled */
	  (OS_TICK)0u,
	  /* pointer to an OPTIONAL user-supplied memory location 
	   * use as a TCB extension */
	  (void *)0,
	  /* contain task-specific option 
	   * OS_OPT_TASK_STK_CHK: allow stack checking 
	   * OS_OPT_TASK_STK_CLR: stack needs to be cleared */
	  (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
	  /* pointer to a variable that will receive an error code */
	  (OS_ERR *)&os_err);

  if (os_err != OS_ERR_NONE)
  {
	while (DEF_TRUE)
	  ;
  }

  /* Start Mulitasking */
  OSStart(&os_err);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */
static void AppTaskStart(void *p_arg) {
	OS_ERR os_err;
	char type;
	int address, data;
	float temp=1, hum=2;

	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_I2C1_Init();
	//HAL_UART_MspInit(&huart1);

	//Modbus initialization
	MBInitSlave();

	struct bme280_dev dev;
	bme280_start(&dev);

	while (DEF_TRUE) {
		bme280_read(&temp, &hum, &dev);
		
		if (MBReceive(1, &type, &address, &data)) {
			//MBRespond(1, (int)temp);
			HAL_Delay(10);
			if (type == 4) {
				if (address == 1 && data == 1) {
					MBRespond(1, (int)temp); //send temperature
				} else if (address == 2 && data == 1) {
					MBRespond(1, (int)hum); //send humidity
				}
			}
		}
		HAL_Delay(10);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
		 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
