#include <SparkFunAutoDriver.h>
#include <initL6470EvalBoard.h>

AutoDriver myStepper(0, CS_PIN, RESET_PIN);
AutoDriver nullBoard(1, CS_PIN, RESET_PIN);

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World!");
    setUpSPI();
    configureStepper(myStepper);
}

void loop() {

}