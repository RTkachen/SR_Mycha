#include "usbhid.h"
//#include "bu"

extern USBD_HandleTypeDef hUsbDeviceFS;

void setDPI(mouseHID mousehid, int8_t min, int8_t max){
	mousehid.step_min = min;
	mousehid.step_min = max;
}

void changeDPI(mouseHID mousehid, uint8_t DPI_level){
	switch(DPI_level){
	case 1:
		setDPI(mousehid,1,20);
		break;
	case 2:
		setDPI(mousehid,1,40);
		break;
	case 3:
		setDPI(mousehid,1,60);
		break;
	case 4:
		setDPI(mousehid,1,80);
		break;
	case 5:
		setDPI(mousehid,1,100);
		break;
	default:
		break;
	}
}

/**
 * AccToMouse_Process
 * -------------------
 * Przekształca przefiltrowane wychylenia z akcelerometru (accFilt[0]=X, accFilt[1]=Y)
 * w raport HID myszy:
 * 1) porównuje dx, dy z progiem MOUSE_THRESHOLD,
 * 2) przelicza nadwyżkę ponad próg na krok w pikselach: (|dx|-thr)/1000 + MOUSE_STEP_MIN,
 * 3) ogranicza krok do ±MOUSE_STEP_MAX,
 * 4) ustawia pola mouse_x, mouse_y i wysyła raport USB.
 * Parametry:
 *   mousehid – struktura do wypełnienia i wysłania,
 *   accFilt  – tablica int16_t[3] z wycentrowanymi, przefiltrowanymi wartościami.
 */
void AccToMouse_Process(mouseHID mousehid, int16_t accFilt[3], uint8_t DPI_level)
{
    // accFilt jest już skalibrowane (offset usunięty) i przefiltrowane
    int16_t dx = accFilt[0];
    int16_t dy = accFilt[1];
    int8_t  mx = 0;
    int8_t  my = 0;

    int16_t MOUSE_THRESHOLD = 2000;   // próg detekcji

    DPI_level = buttons_changeDPI(DPI_level);
    changeDPI(mousehid,DPI_level);

    // Oś X
    if (dx < -MOUSE_THRESHOLD) {
        mx = (int8_t)(((-dx - MOUSE_THRESHOLD) / 1000) + mousehid.step_min);
        if (mx > mousehid.step_max) mx = mousehid.step_max;
    } else if (dx > MOUSE_THRESHOLD) {
        mx = -(int8_t)(((dx - MOUSE_THRESHOLD) / 1000) + mousehid.step_min);
        if (mx < -mousehid.step_max) mx = -mousehid.step_max;
    }

    // Oś Y (inwersja dla kursora)
    if (dy > MOUSE_THRESHOLD) {
        my = -(int8_t)(((dy - MOUSE_THRESHOLD) / 1000) + mousehid.step_min);
        if (my < -mousehid.step_max) my = -mousehid.step_max;
    } else if (dy < -MOUSE_THRESHOLD) {
        my = (int8_t)(((-dy - MOUSE_THRESHOLD) / 1000) + mousehid.step_min);
        if (my > mousehid.step_max) my = mousehid.step_max;
    }

    // Przygotowanie raportu i wysyłka
    mousehid.buttons = buttons_getState();
    mousehid.mouse_x = mx;
    mousehid.mouse_y = my;
    mousehid.wheel   = 0;
    USBD_HID_SendReport(&hUsbDeviceFS,
                        (uint8_t*)&mousehid,
                        sizeof(mousehid));
}
