#include "usbhid.h"

#define MOUSE_THRESHOLD   3000    // odchylenie aby wywołać ruch
#define MOUSE_STEP_MIN    1       // minimalny krok w HID
#define MOUSE_STEP_MAX    10      // opcjonalne ograniczenie skalowania

extern USBD_HandleTypeDef hUsbDeviceFS;

void AccToMouse_Process(mouseHID mousehid,float filteredAcc[3])
{
    static int16_t baseX, baseY;
    static uint8_t  calibrated = 0;
    int16_t dx, dy;
    int8_t  mx = 0, my = 0;


    if (!calibrated) {
        baseX = filteredAcc[0];
        baseY = filteredAcc[1];
        calibrated = 1;
        return;
    }

    dx = filteredAcc[0] - baseX;
    dy = filteredAcc[1] - baseY;

    // X-axis
    if (dx < -MOUSE_THRESHOLD) {
        mx = (int8_t)(((-dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx > MOUSE_STEP_MAX) mx = MOUSE_STEP_MAX;
    } else if (dx > MOUSE_THRESHOLD) {
        mx = -(int8_t)(((dx - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (mx < -MOUSE_STEP_MAX) mx = -MOUSE_STEP_MAX;
    }

    // Y-axis
    if (dy > MOUSE_THRESHOLD) {
        my = -(int8_t)(((dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my < -MOUSE_STEP_MAX) my = -MOUSE_STEP_MAX;
    } else if (dy < -MOUSE_THRESHOLD) {
        my = (int8_t)(((-dy - MOUSE_THRESHOLD) / 1000) + MOUSE_STEP_MIN);
        if (my > MOUSE_STEP_MAX) my = MOUSE_STEP_MAX;
    }

    mousehid.buttons = 0;
    mousehid.mouse_x = mx;
    mousehid.mouse_y = my;
    mousehid.wheel = 0;
    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&mousehid, sizeof(mousehid));
}
