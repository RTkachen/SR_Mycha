#define LPF_ALPHA 0.3f       // 0,1 usuwa szumy o częstotliwości wyższej od 0,88 Hz

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

void accGetData(float accDataFiltered[3]){
	int16_t accDataRaw[3] = {0};
	LSM303C_AccReadXYZ(accDataRaw);
	for (int i = 0; i < 3; ++i) {
		accDataFiltered[i] = LPF_ALPHA * accDataRaw[i] + (1.0f - LPF_ALPHA) * accDataFiltered[i];
	}
	printf("Accelerometer: X: %f,Y: %f,Z: %f\r\n",accDataFiltered[0],accDataFiltered[1],accDataFiltered[2]);
}
