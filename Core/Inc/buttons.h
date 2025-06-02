#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdint.h>
#include "usbhid.h"
#include "stm32l4xx_hal.h"

/** Inicjalizacja tylko wewnętrznych struktur (GPIO z CubeMX). */
void buttons_init(void);

/**
 * Debounce’owany odczyt wszystkich przycisków.
 * @return maska: bit0 = lewy (PA1), bit1 = prawy (PA2)
 */
uint8_t buttons_getState();

int8_t buttons_changeDPI(int8_t* DPI_state);

#endif /* INC_BUTTONS_H_ */
