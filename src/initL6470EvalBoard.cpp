#include "initL6470EvalBoard.h"

stepperMotorNew zAxisMotorConfig;

void configureStepper(AutoDriver selectedChip) {
	
	selectedChip.setAcc(zAxisMotorConfig.accSpeed);
	selectedChip.setDec(zAxisMotorConfig.decSpeed);
	selectedChip.setMaxSpeed(zAxisMotorConfig.maxSpeed);
	selectedChip.setMinSpeed(zAxisMotorConfig.minSpeed);
	selectedChip.setFullSpeed(zAxisMotorConfig.fullSpeed);
	selectedChip.setHoldKVAL(zAxisMotorConfig.holdKval);
	selectedChip.setRunKVAL(zAxisMotorConfig.runKval);
	selectedChip.setAccKVAL(zAxisMotorConfig.accKval);
	selectedChip.setDecKVAL(zAxisMotorConfig.decKval);
	selectedChip.setIntSpeed(zAxisMotorConfig.intSpeed);
	selectedChip.setStSlope(zAxisMotorConfig.stSlope);
	selectedChip.setAccFnSlope(zAxisMotorConfig.accFnSlope);
	selectedChip.setDecFnSlope(zAxisMotorConfig.decFnSlope);
	selectedChip.setKTherm(zAxisMotorConfig.kTherm);
	selectedChip.setStallThreshold(zAxisMotorConfig.stallThresh);
	selectedChip.configStepMode(zAxisMotorConfig.stepMode);
	selectedChip.setAlarmMask(zAxisMotorConfig.alarmMask);
	selectedChip.setIcConfig(zAxisMotorConfig.icConfig);
}

void setUpSPI(void) {
	pinMode(RESET_PIN, OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(MISO, INPUT);
	pinMode(SCLK_PIN, OUTPUT);
	pinMode(CS_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);

	digitalWrite(RESET_PIN, LOW);
	digitalWrite(RESET_PIN, HIGH);

	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
}