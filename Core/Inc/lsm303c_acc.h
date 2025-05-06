/*
 * lsm303c_acc.h
 *
 *  Created on: May 6, 2025
 *      Author: rvt20
 */

#ifndef INC_LSM303C_ACC_H_
#define INC_LSM303C_ACC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"  // dostosuj do Twojego MCU, np. stm32l4xx_hal.h
#include <stdint.h>

// --- definicje pinów CS (chip-select) ----
#define LSM303CTR_CS_XL_GPIO_Port   GPIOE
#define LSM303CTR_CS_XL_Pin         GPIO_PIN_0

// --- rejestry akcelerometru LSM303C (ACC) ----
#define LSM303C_ACC_WHO_AM_I        0x0F
#define LSM303C_ACC_CTRL_REG1_A     0x20
#define LSM303C_ACC_CTRL_REG4_A     0x23
#define LSM303C_ACC_OUT_X_L_A       0x28
#define LSM303C_ACC_OUT_X_H_A       0x29
#define LSM303C_ACC_OUT_Y_L_A       0x2A
#define LSM303C_ACC_OUT_Y_H_A       0x2B
#define LSM303C_ACC_OUT_Z_L_A       0x2C
#define LSM303C_ACC_OUT_Z_H_A       0x2D

// --- wartość WHO_AM_I dla akcelerometru ---
#define LSM303C_ACC_ID              0x41

// --- flagi SPI ---
#define READ_FLAG                   0x01
#define WRITE_FLAG                  0x00

// --- status zwracany przez init --------
typedef enum {
    COMPASS_OK    = 0,
    COMPASS_ERROR = 1
} COMPASS_StatusTypeDef;

// --- prototypy publicznych funkcji -----
/**
 * @brief  Odczyt identyfikatora czujnika (WHO_AM_I).
 * @retval wartość WHO_AM_I (0x41) lub 0xFF w przypadku błędu
 */
uint8_t LSM303C_AccReadIDT(void);

/**
 * @brief  Inicjalizacja akcelerometru LSM303C do pracy SPI, continuous mode, 50Hz, ±2g.
 * @retval COMPASS_OK lub COMPASS_ERROR
 */
COMPASS_StatusTypeDef BSP_COMPASS_InitT(void);

/**
 * @brief  Odczyt surowych danych X, Y, Z z akcelerometru.
 * @param  pData  wskaźnik na tablicę int16_t[3] do wypełnienia wartościami X, Y, Z
 * @retval COMPASS_OK lub COMPASS_ERROR
 */
COMPASS_StatusTypeDef LSM303C_AccReadXYZT(int16_t *pData);

// --- deklaracja uchwytu SPI używanego przez akcelerometr ----
extern SPI_HandleTypeDef hspi2;

#ifdef __cplusplus
}
#endif



#endif /* INC_LSM303C_ACC_H_ */
