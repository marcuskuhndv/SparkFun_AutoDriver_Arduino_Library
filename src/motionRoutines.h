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
#define STEP_SEC_PER_MM_MIN             1.066666667


#define Z_TEST_SPEED_DEFAULT 200.0
#define FEEDRATE_MIN_TO_MS 60000 // convert feedrate from mm/min to mm/ms
#define KVAL_REGISTER_RESOLUTION 0.00390625       // 8 bit register resolution
#define BOUNDARY_PERCENTAGE 10
#define DEFAULT_INTERSTROKE_DELAY 250.0
#define Z_MOTOR_MIN_POWER 0x1
#define DEFAULT_STARTING_POWER 100.0
#define DEFAULT_STROKE_LENGTH 200.0f
#define Z_POWER_NOS_MODE	0x66

#define STEP_FACTOR     64
#define Z_STEPS_PER_REV 200
#define Z_SCREW_PITCH   0.6096   // 3.125 for OG motor

bool homeZAxis(void);
void setPowerKvals(uint8_t configValuePercentage);

bool runMotionTest(float stroke,float feedRate, float startingPower, int dwellMs);


#endif