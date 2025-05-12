#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "lsm303c.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_compass.h"
#include <stdio.h>
#include "main.h"

uint8_t accInit();
void accGetData(float accDataFiltered[3]);

#ifdef __cplusplus
}
#endif

#endif /* INC_ACCELEROMETER_H_ */
