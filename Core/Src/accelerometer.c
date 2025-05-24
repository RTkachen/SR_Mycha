static short int acc_prev[3]    = {0, 0, 0};
static short int acc_offset[3]  = {0, 0, 0};
#define LPF_ALPHA_I   122        // ~0.5 w skali 0–256: 0.3*256 ≈ 77
#include "accelerometer.h"

uint8_t accInit(){
	uint8_t idAcc = LSM303C_AccReadID();
	if(idAcc != LMS303C_ACC_ID){
		printf("ERR, acc id: 0x%X\r\n",idAcc);
		return 1;
	}

	COMPASS_StatusTypeDef stanAcc = BSP_COMPASS_Init();
	if(stanAcc == COMPASS_ERROR){
		printf("ERR acc init\r\n");
		return 2;
	}
	return 0;
}

void accel_calibrate(int16_t offset_cb[3], uint16_t samples){
    int32_t sum[3] = {0,0,0};
    int16_t buf[3];
    for(uint16_t i = 0; i < samples; ++i){
        LSM303C_AccReadXYZ(buf);
        sum[0] += buf[0];
        sum[1] += buf[1];
        sum[2] += buf[2];
        HAL_Delay(1);
    }
    // średnia jako offset
    offset_cb[0] = (int16_t)(sum[0] / samples);
    offset_cb[1] = (int16_t)(sum[1] / samples);
    offset_cb[2] = (int16_t)(sum[2] / samples);
    // zmienna lokalna:
    acc_offset[0] = offset_cb[0];
    acc_offset[1] = offset_cb[1];
    acc_offset[2] = offset_cb[2];
}

int16_t accel_lpf_int(int16_t in, int16_t *prev, uint8_t alpha){
    // y[n] = y[n-1] + alpha*(x[n] - y[n-1]) ; alpha w [0..256]
    int32_t diff = (int32_t)in - *prev;
    int32_t delta = (diff * alpha) >> 8;  // podziel przez 256
    *prev = (int16_t)((int32_t)*prev + delta);
    return *prev;
}

void accGetData(int16_t out[3]){
    int16_t raw[3];
    LSM303C_AccReadXYZ(raw);
    for(int i = 0; i < 3; ++i){
        int16_t centered = raw[i] - acc_offset[i];
        out[i] = accel_lpf_int(centered, &acc_prev[i], LPF_ALPHA_I);
    }
}
