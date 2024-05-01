#ifndef initL6470EvalBoard_h
#define initL6470EvalBoard_h

#include "conf_hardware.h"
#include <SPI.h>

#define CS_PIN     10
#define RESET_PIN  4
#define SCLK_PIN   13

void configureStepper(AutoDriver selectedChip);
void setUpSPI(void);

#endif