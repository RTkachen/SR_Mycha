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
#include "usbd_hid.h"
#include "l3gd20.h"
#include "lsm303c.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_gyroscope.h"
#include "stm32l476g_discovery_compass.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern USBD_HandleTypeDef hUsbDeviceFS;

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 100);
    return len;
}

float dataGyro[3];
float dataGyroPrev[3] = {0};
int16_t dataAcc[3];
float filteredAcc[3] = {0}; // przefiltrowane X, Y, Z
float filteredGyro[3] = {0};

#define LPF_ALPHA 0.3f       // 0,1 usuwa szumy o częstotliwości wyższej od 0,88 Hz
#define HPF_ALPHA 0.9f
#define MOUSE_THRESHOLD   3000    // odchylenie aby wywołać ruch
#define MOUSE_STEP_MIN    1       // minimalny krok w HID
#define MOUSE_STEP_MAX    10      // opcjonalne ograniczenie skalowania

typedef struct
{
	uint8_t buttons;
	int8_t mouse_x;
	int8_t mouse_y;
	int8_t wheel;
} mouseHID;

mouseHID mousehid = {0,0,0,0};

void AccToMouse_Process(void)
{
    static int16_t baseX, baseY;
    static uint8_t  calibrated = 0;
    int16_t dx, dy;
    int8_t  mx = 0, my = 0;


    if (!calibrated) {
        baseX = filteredAcc[0];
        baseY = filteredAcc[1];
        calibrated = 1;
        return;
    }

    dx = filteredAcc[0] - baseX;
    dy = filteredAcc[1] - baseY;

    // X-axis
    if (dx < -MOUSE_THRESHOLD) {
        mx = (int8_t)(((-dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx > MOUSE_STEP_MAX) mx = MOUSE_STEP_MAX;
    } else if (dx > MOUSE_THRESHOLD) {
        mx = -(int8_t)(((dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx < -MOUSE_STEP_MAX) mx = -MOUSE_STEP_MAX;
    }

    // Y-axis
    if (dy > MOUSE_THRESHOLD) {
        my = -(int8_t)(((dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my < -MOUSE_STEP_MAX) my = -MOUSE_STEP_MAX;
    } else if (dy < -MOUSE_THRESHOLD) {
        my = (int8_t)(((-dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my > MOUSE_STEP_MAX) my = MOUSE_STEP_MAX;
    }

    mousehid.buttons = 0;
    mousehid.mouse_x = mx;
    mousehid.mouse_y = my;
    mousehid.wheel = 0;
    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&mousehid, sizeof(mousehid));
}


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

  printf(" - - Start programu - - \r\n");

  //gyro init
  uint8_t idGyro = L3GD20_ReadID();
  if(idGyro != I_AM_L3GD20){printf("ERR, gyro id: 0x%X\r\n",idGyro);}

  uint8_t stanGyro = BSP_GYRO_Init();
  if(stanGyro == GYRO_ERROR){printf("ERR gyro init\r\n");}


  //acc init
  uint8_t idAcc = LSM303C_AccReadID();
  if(idAcc != LMS303C_ACC_ID){printf("ERR, acc id: 0x%X\r\n",idAcc);}

  COMPASS_StatusTypeDef stanAcc = BSP_COMPASS_Init();
  if(stanAcc == COMPASS_ERROR){printf("ERR acc init\r\n");}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  L3GD20_ReadXYZAngRate(dataGyro);
	  for (int i = 0; i < 3; ++i) {
	  	  filteredGyro[i] = HPF_ALPHA * (filteredGyro[i] + dataGyro[i] - dataGyroPrev[i]);
	  	  dataGyroPrev[i] = dataGyro[i];
	  }
	  printf("Gyroscope: X: %f,Y: %f,Z: %f\r\n",filteredGyro[0],filteredGyro[1],filteredGyro[2]);
	  LSM303C_AccReadXYZ(dataAcc);
	  for (int i = 0; i < 3; ++i) {
	      filteredAcc[i] = LPF_ALPHA * dataAcc[i] + (1.0f - LPF_ALPHA) * filteredAcc[i];
	  }
	  AccToMouse_Process();
	  printf("Accelerometer: X: %f,Y: %f,Z: %f\r\n",filteredAcc[0],filteredAcc[1],filteredAcc[2]);
	  HAL_Delay(20);
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
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
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
