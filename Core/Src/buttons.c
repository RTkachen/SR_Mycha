#include "buttons.h"
// GPIO piny z CubeMX: PA1 (left), PA2 (right)
#define BTN_LEFT_PIN   GPIO_PIN_1
#define BTN_RIGHT_PIN  GPIO_PIN_2
#define BTN_GPIO_PORT  GPIOA

// czas debounca w ms
#define DEBOUNCE_DELAY 50

static uint8_t  lastRawState = 0;      // surowy odczyt z ostatniego wezwania
static uint32_t lastChangeTick = 0;    // HAL_GetTick() czasu ostatniej zmiany
static uint8_t  stableState = 0;       // oddebouncowany stan

void buttons_init(void)
{
    lastRawState    = 0;
    stableState     = 0;
    lastChangeTick  = HAL_GetTick();
}

uint8_t buttons_getState(void)
{
    // 1) Odczyt surowy: 1 = wciśnięty, 0 = puszczony
    uint8_t raw = 0;
    if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_LEFT_PIN)  == GPIO_PIN_SET) raw |= 1 << 1;
    if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_RIGHT_PIN) == GPIO_PIN_SET) raw |= 1 << 0;

    // 2) Jeśli zmiana stanu surowego – resetujemy timer
    if (raw != lastRawState) {
        lastRawState   = raw;
        lastChangeTick = HAL_GetTick();
    }
    // 3) Po upływie DEBOUNCE_DELAY aktualizujemy stan stabilny
    else if ((HAL_GetTick() - lastChangeTick) >= DEBOUNCE_DELAY) {
        stableState = raw;
    }

    // 4) Zwracamy oddebouncowany stan (bit-maskę)
    return stableState;
}
