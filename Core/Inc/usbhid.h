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
	int8_t step_min;
	int8_t step_max;
} mouseHID;

//enum DPI_enum{
//	very_slow,
//	slow,
//	medium,
//	fast,
//	very_fast,
//};

void AccToMouse_Process(mouseHID mousehid,int16_t filteredAcc[3], uint8_t DPI_level);

void setDPI(mouseHID mousehid, int8_t min, int8_t max);

void changeDPI(mouseHID mousehid, uint8_t DPI_level);

#ifdef __cplusplus
}
#endif

#endif /* INC_USBHID_H_ */
