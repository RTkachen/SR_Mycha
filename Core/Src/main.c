/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
<<<<<<< Updated upstream
=======

#include "accelerometer.h"
#include "gyroscope.h"
#include "usbhid.h"
>>>>>>> Stashed changes
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define XL_CS_PIN GPIO_PIN_0
#define XL_CS_PORT GPIOE
#define GYRO_CS_PIN GPIO_PIN_7
#define GYRO_CS_PORT GPIOD
#define WHO_AM_I_REGISTER 0x0F
#define WHO_AM_I_EXPECTED 0x41
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 100);
    return len;
}

<<<<<<< Updated upstream
void Accel_Init(void) {
    uint8_t regAddr = 0x20;
    uint8_t value = 0x57;
    HAL_GPIO_WritePin(XL_CS_PORT, XL_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &regAddr, 1, 100);
    HAL_SPI_Transmit(&hspi2, &value, 1, 100);
    HAL_GPIO_WritePin(XL_CS_PORT, XL_CS_PIN, GPIO_PIN_SET);
}

uint8_t readWhoAmI(void) {
    uint8_t txData = WHO_AM_I_REGISTER | 0x80;
    uint8_t rxData = 0;
    printf("Akcelerometr: CS LOW\n");
    HAL_GPIO_WritePin(XL_CS_PORT, XL_CS_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_SPI_TransmitReceive(&hspi2, &txData, &rxData, 1, 100);
    printf("Akcelerometr: Odebrano 0x%X\n", rxData);
    HAL_GPIO_WritePin(XL_CS_PORT, XL_CS_PIN, GPIO_PIN_SET);
    printf("Akcelerometr: CS HIGH\n");
    return rxData;
}

uint8_t readGyroWhoAmI(void) {
    uint8_t txData = WHO_AM_I_REGISTER | 0x80;
    uint8_t rxData = 0;
    printf("Żyroskop: CS LOW\n");
    HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_SPI_TransmitReceive(&hspi2, &txData, &rxData, 1, 100);
    printf("Żyroskop: Odebrano 0x%X\n", rxData);
    HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_SET);
    printf("Żyroskop: CS HIGH\n");
    return rxData;
}
=======
//float dataGyro[3];
float filteredGyro[3] = {0};
int16_t dataAcc[3];
float filteredAcc[3] = {0}; // przefiltrowane X, Y, Z

mouseHID mousehid = {0,0,0,0};

>>>>>>> Stashed changes
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
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  Accel_Init();
      uint8_t sensor_id = readWhoAmI();
      if (sensor_id == WHO_AM_I_EXPECTED) {
          printf("Akcelerometr poprawnie podłączony! WHO_AM_I: 0x%X\n", sensor_id);
      } else {
          printf("Błąd! Otrzymano: 0x%X, spodziewano się: 0x%X\n", sensor_id, WHO_AM_I_EXPECTED);
      }

<<<<<<< Updated upstream
      uint8_t gyro_id = readGyroWhoAmI();
      printf("Żyroskop WHO_AM_I: 0x%X (spodziewano się 0xD4)\n", gyro_id);
=======
  printf(" - - Start programu - - \r\n");

  if(!gyroInit()){Error_Handler();}
  if(!accInit()){Error_Handler();}

>>>>>>> Stashed changes
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
<<<<<<< Updated upstream
=======
	  gyroGetData(filteredGyro);
	  accGetData(filteredAcc);
	  AccToMouse_Process(mousehid,filteredAcc);

	  HAL_Delay(20);

>>>>>>> Stashed changes
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	HAL_Delay(500);

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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
