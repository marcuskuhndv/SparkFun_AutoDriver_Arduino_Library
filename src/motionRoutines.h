#ifndef motionRoutines_h
#define motionRoutines_h

#include "SparkFunAutoDriver.h"
#include <stdint.h>

#define Z_HOMING_SPEED_MM_MIN			100
#define Z_FORWARDS_DIR					0x0
#define Z_BACKWARDS_DIR					0x1
#define MAX_POWER_PERCENTAGE			160.0f
#define KVAL_REGISTER_RESOLUTION		0.00390625       // 8 bit register resolution
#define Z_MOTOR_MAX_POWER				0x40
#define Z_MOTOR_MIN_POWER				0x1

bool homeZAxis(void);
void setPowerKvals(uint8_t configValuePercentage);

#endif