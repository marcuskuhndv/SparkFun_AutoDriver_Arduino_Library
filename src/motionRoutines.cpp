#include "motionRoutines.h"

extern AutoDriver myStepper;

static uint8_t convertPowerPercentageToKval(float valueToConvert) {

    if (valueToConvert > MAX_POWER_PERCENTAGE) {
        //DV_info("Rounding to full power");
        return Z_MOTOR_MAX_POWER;
    }

     valueToConvert = Z_MOTOR_MAX_POWER * (valueToConvert / 100.0f);

    if (valueToConvert < KVAL_REGISTER_RESOLUTION) {
        //lower bound for the driver
        //DV_info("Lower limit for kval hit, clipping to minimum power: 1.6 percent or 0x1");
        return Z_MOTOR_MIN_POWER;
    }

    return (uint8_t)valueToConvert;
}

static float convertPowerKvalToPercentage(uint8_t valueToConvert) {

    return (float)valueToConvert * 100 / Z_MOTOR_MAX_POWER;
}

bool homeZAxis(void) {

    //const uint32_t startTime = millis();

    //if (z_axis_homed()) {
        Serial.println("Moving out of Z-Axis sensor range");
        myStepper.setMaxSpeed(Z_HOMING_SPEED_MM_MIN);
        myStepper.run(Z_FORWARDS_DIR, Z_HOMING_SPEED_MM_MIN);
        while(myStepper.busyCheck());

        //while (z_axis_homed()) {
        //    if (!isMotionWithinTimeframe(Z_MOTOR_INDEX, startTime, Z_HOMING_TIMEOUT_SHORT_SEC)) { // short timeout since moving away from sensor should be pretty fast
        //        return false;
        //    }
        //}

        myStepper.softStop();
        while (myStepper.busyCheck());
        Serial.println("Cleared Z-Axis sensor range, stopping");
    //}

    //if (!z_axis_homed()) {
        Serial.println("Starting retraction to Z-Axis sensor");
        myStepper.setMaxSpeed(Z_HOMING_SPEED_MM_MIN);
        myStepper.run(Z_BACKWARDS_DIR, Z_HOMING_SPEED_MM_MIN);
        while (myStepper.busyCheck());

        //while (!z_axis_homed()) {
        //    if (!isMotionWithinTimeframe(Z_MOTOR_INDEX, startTime, Z_HOMING_TIMEOUT_DEFAULT_SEC)) {
        //        return false;
        //    }
        //} 

        myStepper.softStop();
        while (myStepper.busyCheck());
        Serial.println("Hit Z-Axis sensor at %.1fmm, moving to 0mm");
    //}

    //if (update_motor_position(g_modals->x, g_modals->y, Z_SENSOR_TRIP_DISTANCE, g_modals->a) && (system_issue_absolute_blocking_move(g_modals->x, g_modals->y, 0, g_modals->a, Z_HOMING_SPEED_MM_MIN))) {
    //    Serial.println("Z homed at 0mm");
    //    return true;
    //}

    return false;
}

void setPowerKvals(uint8_t configValuePercentage) {
    uint8_t configValueKval = convertPowerPercentageToKval(configValuePercentage);
    
    myStepper.setAccKVAL(configValueKval);
    myStepper.setDecKVAL(configValueKval);
    myStepper.setRunKVAL(configValueKval);

}