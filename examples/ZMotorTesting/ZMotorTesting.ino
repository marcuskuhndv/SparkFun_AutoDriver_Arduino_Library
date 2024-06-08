#include <SparkFunAutoDriver.h>
#include <initL6470EvalBoard.h>
#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"
#include "motionRoutines.h"
#include <stdio.h>

AutoDriver myStepper(0, CS_PIN, RESET_PIN);
AutoDriver nullBoard(1, CS_PIN, RESET_PIN);

#define CLI_BUFFER_SIZE 324
#define CLI_RX_BUFFER_SIZE 32
#define CLI_CMD_BUFFER_SIZE 64
#define CLI_HISTORY_SIZE 32
#define CLI_BINDING_COUNT 10

char buffer[100];

EmbeddedCli *cli;

CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];

void onCommand(EmbeddedCli *embeddedCli, CliCommand *command);
void writeChar(EmbeddedCli *embeddedCli, char c);
void onHello(EmbeddedCli *cli, char *args, void *context);
void onHome(EmbeddedCli *cli, char *args, void *context);
void onSetPower(EmbeddedCli *cli, char *args, void *context);
void onSetFeedrate(EmbeddedCli *cli, char *args, void *context);
void onM98(EmbeddedCli *cli, char *args, void *context);

void setup() {
  Serial.begin(115200);
  while(!Serial){}       // Loop until USB is ready

  EmbeddedCliConfig *config = embeddedCliDefaultConfig();
  config->cliBuffer = cliBuffer;
  config->cliBufferSize = CLI_BUFFER_SIZE;
  config->rxBufferSize = CLI_RX_BUFFER_SIZE;
  config->cmdBufferSize = CLI_CMD_BUFFER_SIZE;
  config->historyBufferSize = CLI_HISTORY_SIZE;
  config->maxBindingCount = CLI_BINDING_COUNT;
  cli = embeddedCliNew(config);

  // if (cli == NULL) {
  //     Serial.println(F("Cli was not created. Check sizes!"));
  //     return;
  // }
  // Serial.println(F("Cli has started. Enter your commands."));

  embeddedCliAddBinding(cli, {
          "hello",                // command name (spaces are not allowed)
          "Print hello message",  // optional help for a command (NULL for no help)
          true,                   // flag whether to tokenize arguments
          (void *) "World",       // optional pointer to any application context
          onHello                 // binding function name
  });
  embeddedCliAddBinding(cli, {
          "home",
          "Home motor to 0mm",
          true,
          nullptr,
          onHome
  });
  embeddedCliAddBinding(cli, {
          "setPower",
          "Set motor Acc, Dec and Run Kvals",
          true,
          nullptr,
          onSetPower
  });
  embeddedCliAddBinding(cli, {
          "setFeedrate",
          "Set motor Feedrate [MAX_SPEED Register]",
          true,
          nullptr,
          onSetFeedrate
  });
  embeddedCliAddBinding(cli, {
          "M98",
          "Enter M98 command in this order: M98 [distance] [feedrate] [starting power] [interstroke delay] ",
          true,
          nullptr,
          onM98
  });

  cli->onCommand = onCommand;
  cli->writeChar = writeChar;

  setUpSPI();
  configureStepper(myStepper);

  int temp;

  temp = myStepper.getParam(CONFIG);
  Serial.print(F("test CONFIG value: "));
  Serial.println(temp, HEX);
  // sanity check that we can read the CONFIG register on the chip. Should be 0x2E88 on bootup
  
  myStepper.run(FWD, convertToFeedRate(200));

}

void loop() {

  //if (cli == NULL) {
  //  return;
  //}

  // provide all chars to cli
  // while (Serial.available() > 0) {
  //     embeddedCliReceiveChar(cli, Serial.read());
  // }
  
  //embeddedCliProcess(cli);
  //
  
  // myStepper.move(FWD, 200 * 64);
  // while (myStepper.busyCheck());
  // myStepper.softStop();
  // delay(1000);
  // myStepper.move(REV, 200 * 128);
  // while (myStepper.busyCheck());
  // myStepper.softStop();
  // delay(1000);
}

unsigned int convertToFeedRate(int mmPerMin) {
  return mmPerMin * 5.4680665;
}

void onM98(EmbeddedCli *, char *args, void *) {
  
  double testStrokeDistance, testFeedRate, testStartingPower, testDelay;

  testStrokeDistance = atof(embeddedCliGetToken(args, 1));
  testFeedRate = atof(embeddedCliGetToken(args, 2));
  testStartingPower = atof(embeddedCliGetToken(args, 3));
  testDelay = atof(embeddedCliGetToken(args, 4));

  //Serial.print(F("Homing system before motion test..."));
  
  #pragma message("add homing routine here")
  // if (!homeZAxis()) {
  //     Serial.println("Failed to home before motion test");
  //     return;
  // }
  if (testStrokeDistance == 0.0f) {
      testStrokeDistance = DEFAULT_STROKE_LENGTH;
  }

  if (testFeedRate == 0.0f) {
      testFeedRate = Z_TEST_SPEED_DEFAULT;
  }

  if (testStartingPower == 0.0f) {
      testStartingPower = DEFAULT_STARTING_POWER;
  }

  if (testDelay == 0.0f) {
      testDelay = DEFAULT_INTERSTROKE_DELAY;
  }
  
  Serial.print("Starting M98 test with: Z: ");
  Serial.print(testStrokeDistance);
  Serial.print("mm F: ");
  Serial.print(testFeedRate);
  Serial.print("mm/min S: ");
  Serial.print(testStartingPower);
  Serial.print("% X: ");
  Serial.println(testDelay);
  
  // runMotionTest(testStrokeDistance, testFeedRate, testStartingPower, testDelay);

  // if (!homeZAxis()) {
  //         Serial.print("Failed to home after motion test");
  //         return;
  // }
  

}
void onSetFeedrate(EmbeddedCli *, char *args, void *) {
  Serial.print(F("Setting motor feedrate to: "));
  Serial.println(embeddedCliGetToken(args, 1));
  myStepper.setMaxSpeed(atof(embeddedCliGetToken(args, 1)) * STEP_SEC_PER_MM_MIN);
}

void onSetPower(EmbeddedCli *, char *args, void *) {
  Serial.print(F("Setting motor power to: "));
  Serial.println(embeddedCliGetToken(args, 1));
  setPowerKvals(atoi(embeddedCliGetToken(args, 1)));
}

void onHome(EmbeddedCli *, char *args, void *) {
  Serial.println(F("Homing Axis "));
  homeZAxis();
  Serial.print("\r\n");   
}

void onCommand(EmbeddedCli *, CliCommand *command) {
  Serial.println(F("Received command:"));
  Serial.println(command->name);
  embeddedCliTokenizeArgs(command->args);
  for (uint8_t i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) {
    Serial.print(F("arg "));
    Serial.print((char) ('0' + i));
    Serial.print(F(": "));
    Serial.println(embeddedCliGetToken(command->args, i));
  }
}

void onHello(EmbeddedCli *, char *args, void *context) {
  Serial.print(F("Hello "));
  if (embeddedCliGetTokenCount(args) == 0)
    Serial.print((const char *) context);
  else
    Serial.print(embeddedCliGetToken(args, 1));
  Serial.print("\r\n");
}

void writeChar(EmbeddedCli *, char c) {
  Serial.write(c);
}