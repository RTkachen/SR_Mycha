#include "buttons.h"
// GPIO piny z CubeMX: PA1 (left), PA2 (right)
#define BTN_LEFT_PIN   	GPIO_PIN_1
#define BTN_RIGHT_PIN  	GPIO_PIN_2
#define BTN_UP_PIN	   	GPIO_PIN_3
#define BTN_DOWN_PIN	GPIO_PIN_5
#define BTN_GPIO_PORT  	GPIOA

// czas debounca w ms
#define DEBOUNCE_DELAY 50

static uint8_t  lastRawState = 0;      // surowy odczyt z ostatniego wezwania
static uint32_t lastChangeTick = 0;    // HAL_GetTick() czasu ostatniej zmiany
static uint8_t  stableState = 0;       // oddebouncowany stan


/**
 * buttons_init
 * -------------
 * Inicjalizuje wewnętrzne zmienne modułu przycisków:
 *   - zeruje debouncowane i surowe stany,
 *   - ustawiane jest początkowe tick (stąd debouncowanie już od startu).
 * GPIO jest skonfigurowane przez CubeMX, więc tutaj tylko reset stanu.
 */
void buttons_init(void)
{
    lastRawState    = 0;
    stableState     = 0;
    lastChangeTick  = HAL_GetTick();
}


/**
 * buttons_getState
 * -----------------
 * Odczytuje surowy stan przycisków (PA1/PA2), debouncuje go czasowo
 * i zwraca jako maskę bitową:
 *   bit0 = prawy przycisk, bit1 = lewy przycisk.
 * Mechanizm:
 *   1) Odczyt raw = aktualny stan GPIO,
 *   2) Jeśli raw zmienił się od ostatniego odczytu, reset timera,
 *   3) Jeśli przez DEBOUNCE_DELAY ms raw pozostaje niezmieniony,
 *      to aktualizowany jest stableState,
 *   4) Zwracany jest stableState.
 */
uint8_t buttons_getState()
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

/**
 * buttons_changeDPI
 * -----------------
 * Odczytuje stan przycisków (PA3/PA4), debouncuje go czasowo
 * i interpretuje jako zmianę wartości DPI
 *   PA3 = joystick up = DPI++, PA4 = joystick down = DPI--.
 * Mechanizm:
 *   1) Odczyt curent(Up/Down)State = aktualny stan GPIO,
 *   2) Jeśli curent(Up/Down)State zmienił się od ostatniego odczytu, reset timera,
 *   3) Jeśli przez DEBOUNCE_DELAY ms curent(Up/Down)State pozostaje niezmieniony,
 *      to aktualizowany jest DPI,
 *   4) Zwracany jest DPI jako wartość.
 */
int8_t buttons_changeDPI(int8_t* DPI_state)
{
    static uint32_t lastUpPressTime = 0;
    static uint32_t lastDownPressTime = 0;

    static uint8_t prevUpState = 1;
    static uint8_t prevDownState = 1;

    uint32_t currentTime = HAL_GetTick();

    // Czytanie obecnych stanów przycisków
    uint8_t currentUpState = HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_UP_PIN);
    uint8_t currentDownState = HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_DOWN_PIN);

    // Obsługa przycisku zwiekszającego DPI (joystick up)
    if (prevUpState == 1 && currentUpState == 0) // zbocze opadające
    {
        if ((currentTime - lastUpPressTime) > DEBOUNCE_DELAY)
        {
        	(*DPI_state)++;
        	if(*DPI_state>5) *DPI_state = 5;	//jesli przekroczono zakres 1-5
            lastUpPressTime = currentTime;
        }
    }

    // Obsługa przycisku zmniejszającego DPI (joystick down)
    if (prevDownState == 1 && currentDownState == 0) // zbocze opadające
    {
        if ((currentTime - lastDownPressTime) > DEBOUNCE_DELAY)
        {
        	(*DPI_state)--;
        	if(*DPI_state<1) *DPI_state = 1;	//jesli przekroczono zakres 1-5
            lastDownPressTime = currentTime;
        }
    }

    // Aktualizacja poprzednich stanów
    prevUpState = currentUpState;
    prevDownState = currentDownState;

    return *DPI_state;
}




























