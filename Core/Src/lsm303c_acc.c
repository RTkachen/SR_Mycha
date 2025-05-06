 /*
 * lsm303c_acc.c
 *
 *  Created on: May 6, 2025
 *      Author: rvt20
 */
#include "lsm303c_acc.h"
// --- funkcja odczytu rejestru przez SPI ---
// (używa dodatkowego bajtu dummy=0x00, by wygenerować zegar podczas odbioru)
static HAL_StatusTypeDef LSM303C_SPI_ReadReg(uint8_t reg_addr, uint8_t *pData)
{
    uint8_t cmd = (reg_addr << 1) | READ_FLAG;
    uint8_t dummy = 0x00;
    HAL_StatusTypeDef st;

    // CS low → start SPI session
    HAL_GPIO_WritePin(LSM303CTR_CS_XL_GPIO_Port, LSM303CTR_CS_XL_Pin, GPIO_PIN_RESET);

    // wyślij adres + tryb read
    st = HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);
    if (st != HAL_OK) goto end;

    // odczytaj dane (wysyłając dummy)
    st = HAL_SPI_TransmitReceive(&hspi2, &dummy, pData, 1, HAL_MAX_DELAY);

end:
    // CS high → koniec
    HAL_GPIO_WritePin(LSM303CTR_CS_XL_GPIO_Port, LSM303CTR_CS_XL_Pin, GPIO_PIN_SET);
    return st;
}

static HAL_StatusTypeDef LSM303C_SPI_WriteReg(uint8_t reg_addr, uint8_t data)
{
    uint8_t cmd = (reg_addr << 1) | WRITE_FLAG;
    HAL_StatusTypeDef st;

    HAL_GPIO_WritePin(LSM303CTR_CS_XL_GPIO_Port, LSM303CTR_CS_XL_Pin, GPIO_PIN_RESET);
    st = HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);
    if (st != HAL_OK) goto end;
    st = HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);

end:
    HAL_GPIO_WritePin(LSM303CTR_CS_XL_GPIO_Port, LSM303CTR_CS_XL_Pin, GPIO_PIN_SET);
    return st;
}

// --- 1) Odczyt identyfikatora czujnika (WHO_AM_I) --------------------------
uint8_t LSM303C_AccReadIDT(void)
{
    uint8_t id = 0xFF;
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_WHO_AM_I, &id) != HAL_OK) {
        return 0xFF;
    }
    return id;
}

// --- 2) Inicjalizacja akcelerometru LSM303C do 50Hz, ±2g, continuous mode ------
COMPASS_StatusTypeDef BSP_COMPASS_InitT(void)
{
    HAL_StatusTypeDef st;

    // CTRL_REG4_A: IF_ADD_INC=1 | I2C_DISABLE=1 | FS=00(±2g) => 0x06
    st = LSM303C_SPI_WriteReg(LSM303C_ACC_CTRL_REG4_A, 0x06);
    if (st != HAL_OK) return COMPASS_ERROR;

    // CTRL_REG1_A: ODR=010(50Hz) | XEN=YEN=ZEN=1 | BDU=0 => 0x27
    st = LSM303C_SPI_WriteReg(LSM303C_ACC_CTRL_REG1_A, 0x27);
    if (st != HAL_OK) return COMPASS_ERROR;

    return COMPASS_OK;
}

// --- 3) Odczyt surowych danych X, Y, Z --------------------------------------
COMPASS_StatusTypeDef LSM303C_AccReadXYZT(int16_t *pData)
{
    uint8_t buf_low, buf_high;
    int16_t value;

    // X
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_X_L_A, &buf_low) != HAL_OK) return COMPASS_ERROR;
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_X_H_A, &buf_high) != HAL_OK) return COMPASS_ERROR;
    value = (int16_t)((buf_high << 8) | buf_low);
    pData[0] = value;

    // Y
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_Y_L_A, &buf_low) != HAL_OK) return COMPASS_ERROR;
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_Y_H_A, &buf_high) != HAL_OK) return COMPASS_ERROR;
    value = (int16_t)((buf_high << 8) | buf_low);
    pData[1] = value;

    // Z
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_Z_L_A, &buf_low) != HAL_OK) return COMPASS_ERROR;
    if (LSM303C_SPI_ReadReg(LSM303C_ACC_OUT_Z_H_A, &buf_high) != HAL_OK) return COMPASS_ERROR;
    value = (int16_t)((buf_high << 8) | buf_low);
    pData[2] = value;

    return COMPASS_OK;
}
