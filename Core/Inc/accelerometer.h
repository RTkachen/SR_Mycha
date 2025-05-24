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

// inicjalizacja sprzętowa
uint8_t accInit(void);

// kalibracja (ustawia wewnętrzne baseX/baseY)
/*
   offset_cb – wskaźnik na tablicę [3], w której funkcja zapisze offsety
   (np. offset_cb[0] = baseX, offset_cb[1] = baseY, offset_cb[2] = baseZ)
*/
void accel_calibrate(int16_t offset_cb[3], uint16_t samples);

// filtr integerowy IIR
/*
   in     – aktualny surowy pomiar
   prev   – wskaźnik na poprzednią wartość filtra (i tu też wynik będzie przechowywany)
   alpha  – współczynnik (0–256)
   zwraca filtrowaną wartość całkowitą
*/
int16_t accel_lpf_int(int16_t in, int16_t *prev, uint8_t alpha);

// odczyt przefiltrowanych danych (z użyciem powyższych)
void accGetData(int16_t out[3]);

#ifdef __cplusplus
}
#endif

#endif /* INC_ACCELEROMETER_H_ */
