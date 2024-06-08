#ifndef conf_hardware_h
#define conf_hardware_h

#include "SparkFunAutoDriver.h"
#include <stdint.h>

typedef struct stepperMotorStructOG {
    uint16_t    accSpeed = 1050;
    uint16_t    decSpeed = 1050;
    uint16_t    maxSpeed = 1100;
    uint16_t    minSpeed = 0;
    uint16_t    fullSpeed = 3900;
    uint8_t     holdKval = 0x04;
    uint8_t     runKval = 0x06;
    uint8_t     accKval = 0x40;
    uint8_t     decKval = 0x40;
    uint16_t    intSpeed = 218;
    uint8_t     stSlope = 0x24;
    uint8_t     accFnSlope = 0x64;
    uint8_t     decFnSlope = 0x64;
    uint8_t     kTherm = 0x1;
    uint8_t     OCD_Thresh = OCD_TH_4875mA;
    uint8_t     stallThresh = 0x75;
    uint8_t     stepMode = STEP_SEL_1_64;
    uint8_t     alarmMask = 0xFF;
    uint16_t    icConfig = 0x2E88;
} stepperMotorOG;


typedef struct stepperMotorStructNew {
    uint16_t    accSpeed = 1050;
    uint16_t    decSpeed = 1050;
    uint16_t    maxSpeed = 1100;
    uint16_t    minSpeed = 0;
    uint16_t    fullSpeed = 3900;
    uint8_t     holdKval = 0x03;
    uint8_t     runKval = 0x2A;
    uint8_t     accKval = 0x2A;
    uint8_t     decKval = 0x2A;
    uint16_t    intSpeed = 0x1378;
    uint8_t     stSlope = 0x23;
    uint8_t     accFnSlope = 0x47;
    uint8_t     decFnSlope = 0x47;
    uint8_t     kTherm = 0x1;
    uint8_t     OCD_Thresh = OCD_TH_4875mA;
    uint8_t     stallThresh = 0x75;
    uint8_t     stepMode = STEP_SEL_1_128;
    uint8_t     alarmMask = 0xFF;
    uint16_t    icConfig = 0x2E88;
} stepperMotorNew;

#endif