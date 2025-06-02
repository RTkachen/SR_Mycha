#include "usbhid.h"
//#include "bu"

extern USBD_HandleTypeDef hUsbDeviceFS;

/**
 * AccToMouse_Process
 * -------------------
 * Przekształca przefiltrowane wychylenia z akcelerometru (accFilt[0]=X, accFilt[1]=Y)
 * w raport HID myszy:
 * 1) porównuje dx, dy z progiem MOUSE_THRESHOLD,
 * 2) przelicza nadwyżkę ponad próg na krok w pikselach: (|dx|-thr)/1000 + MOUSE_STEP_MIN,
 * 3) ogranicza krok do ±MOUSE_STEP_MAX,
 * 4) ustawia pola mouse_x, mouse_y i wysyła raport USB.
 * 5) reaguje na zmianę wartości DPI
 * Parametry:
 *   mousehid – struktura do wypełnienia i wysłania,
 *   accFilt  – tablica int16_t[3] z wycentrowanymi, przefiltrowanymi wartościami.
 *   dpi 	  - wskaźnik do zmiennej int8_t zawierającej mnożnik DPI
 */
void AccToMouse_Process(mouseHID mousehid, int16_t accFilt[3], int8_t* dpi)
{
    // accFilt jest już skalibrowane (offset usunięty) i przefiltrowane
    int16_t dx = accFilt[0];
    int16_t dy = accFilt[1];
    int8_t  mx = 0;
    int8_t  my = 0;

    // Zmiana dpi
    *dpi = buttons_changeDPI(dpi);

    int16_t MOUSE_THRESHOLD = 2000;   // próg detekcji
    int8_t  MOUSE_STEP_MIN  = 1;      // minimalny krok
    int8_t  MOUSE_STEP_MAX  = 20;     // maksymalny krok

    // Oś X
    if (dx < -MOUSE_THRESHOLD) {
        mx = (int8_t)(((-dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx > MOUSE_STEP_MAX) mx = MOUSE_STEP_MAX;
    } else if (dx > MOUSE_THRESHOLD) {
        mx = -(int8_t)(((dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx < -MOUSE_STEP_MAX) mx = -MOUSE_STEP_MAX;
    }

    // Oś Y (inwersja dla kursora)
    if (dy > MOUSE_THRESHOLD) {
        my = -(int8_t)(((dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my < -MOUSE_STEP_MAX) my = -MOUSE_STEP_MAX;
    } else if (dy < -MOUSE_THRESHOLD) {
        my = (int8_t)(((-dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my > MOUSE_STEP_MAX) my = MOUSE_STEP_MAX;
    }


    // Przygotowanie raportu i wysyłka
    mousehid.buttons = buttons_getState();
    mousehid.mouse_x = mx * *dpi;
    mousehid.mouse_y = my * *dpi;
    mousehid.wheel   = 0;
    USBD_HID_SendReport(&hUsbDeviceFS,
                        (uint8_t*)&mousehid,
                        sizeof(mousehid));
}
