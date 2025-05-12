#include "gyroscope.h"

#define LPF_ALPHA 0.1f

uint8_t gyroInit(){
	uint8_t idGyro = L3GD20_ReadID();
	if(idGyro != I_AM_L3GD20){
		printf("ERR, gyro id: 0x%X\r\n",idGyro);
		return 1;
	}

	uint8_t stanGyro = BSP_GYRO_Init();
//	uint16_t gyroInit = 0b0001000000001111;
//	L3GD20_Init(gyroInit);
	if(stanGyro == GYRO_ERROR){
		printf("ERR gyro init\r\n");
		return 2;
	}
	return 0;
}

void gyroGetData(float gyroDataFiltered[3]){
	float gyroDataRaw[3] = {0};
	L3GD20_ReadXYZAngRate(gyroDataRaw);
	for (int i = 0; i < 3; ++i) {
		gyroDataFiltered[i] = LPF_ALPHA * gyroDataRaw[i] + (1.0f - LPF_ALPHA) * gyroDataFiltered[i];
	}
	printf("Gyroscope : X: %f,Y: %f,Z: %f\r\n",gyroDataFiltered[0],gyroDataFiltered[1],gyroDataFiltered[2]);
}
