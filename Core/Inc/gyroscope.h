#ifndef INC_GYROSCOPE_H_
#define INC_GYROSCOPE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdio.h>
#include "l3gd20.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_gyroscope.h"

uint8_t gyroInit();
void gyroGetData(float gyroDataFiltered[3]);
//void gyroFilterData()








#ifdef __cplusplus
}
#endif

#endif /* INC_GYROSCOPE_H_ */
