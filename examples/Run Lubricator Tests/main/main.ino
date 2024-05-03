#include <SparkFunAutoDriver.h>
#include <initL6470EvalBoard.h>

AutoDriver myStepper(0, CS_PIN, RESET_PIN);
AutoDriver nullBoard(1, CS_PIN, RESET_PIN);


void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  setUpSPI();
  configureStepper(myStepper);
  // sanity check that we can read the CONFIG register on the chip. Should be 0x2E88 on bootup
  int temp = myStepper.getParam(CONFIG);
  Serial.print("Config reg value: ");
  Serial.println(temp, HEX);
}

void loop() {
    myStepper.move(FWD, 50000);
    while (myStepper.busyCheck());
    myStepper.softStop();
    delay(1000);
    myStepper.move(REV, 50000);
    while (myStepper.busyCheck());
    myStepper.softStop();
    delay(1000);
}