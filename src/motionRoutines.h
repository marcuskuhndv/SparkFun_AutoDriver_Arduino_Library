#ifndef motionRoutines_h
#define motionRoutines_h

#include "SparkFunAutoDriver.h"
#include <stdint.h>

#define Z_HOMING_SPEED_MM_MIN 100
#define Z_FORWARDS_DIR        0x0
#define Z_BACKWARDS_DIR		  0x1

bool homeZAxis(void);

#endif