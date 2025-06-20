#ifndef INC_USBHID_H_
#define INC_USBHID_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "usbd_hid.h"

typedef struct
{
	uint8_t buttons;
	int8_t mouse_x;
	int8_t mouse_y;
	int8_t wheel;
} mouseHID;

void AccToMouse_Process(mouseHID mousehid,int16_t filteredAcc[3], int8_t *dpi);

#ifdef __cplusplus
}
#endif

#endif /* INC_USBHID_H_ */
