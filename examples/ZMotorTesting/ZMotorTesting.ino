#include <SparkFunAutoDriver.h>
#include <initL6470EvalBoard.h>
#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"
#include "motionRoutines.h"

AutoDriver myStepper(0, CS_PIN, RESET_PIN);
AutoDriver nullBoard(1, CS_PIN, RESET_PIN);



// 164 bytes is minimum size for this params on Arduino Nano
#define CLI_BUFFER_SIZE 166
#define CLI_RX_BUFFER_SIZE 16
#define CLI_CMD_BUFFER_SIZE 32
#define CLI_HISTORY_SIZE 32
#define CLI_BINDING_COUNT 3

EmbeddedCli *cli;

CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];

void onCommand(EmbeddedCli *embeddedCli, CliCommand *command);

void writeChar(EmbeddedCli *embeddedCli, char c);

void onHello(EmbeddedCli *cli, char *args, void *context);

void onLed(EmbeddedCli *cli, char *args, void *context);

void onAdc(EmbeddedCli *cli, char *args, void *context);

void home(EmbeddedCli *cli, char *args, void *context);

void setPower(EmbeddedCli *cli, char *args, void *context);

void setup() {
  Serial.begin(115200);

  EmbeddedCliConfig *config = embeddedCliDefaultConfig();
  config->cliBuffer = cliBuffer;
  config->cliBufferSize = CLI_BUFFER_SIZE;
  config->rxBufferSize = CLI_RX_BUFFER_SIZE;
  config->cmdBufferSize = CLI_CMD_BUFFER_SIZE;
  config->historyBufferSize = CLI_HISTORY_SIZE;
  config->maxBindingCount = CLI_BINDING_COUNT;
  cli = embeddedCliNew(config);

  if (cli == NULL) {
      Serial.println(F("Cli was not created. Check sizes!"));
      return;
  }
  Serial.println(F("Cli has started. Enter your commands."));

  embeddedCliAddBinding(cli, {
          "get-led",
          "Get led status",
          false,
          nullptr,
          onLed
  });
  embeddedCliAddBinding(cli, {
          "get-adc",
          "Read adc value",
          false,
          nullptr,
          onAdc
  });
  embeddedCliAddBinding(cli, {
          "hello",
          "Print hello message",
          true,
          (void *) "World",
          onHello
  });
  embeddedCliAddBinding(cli, {
          "home",               // command name (spaces are not allowed)
          "Home motor to 0mm",  // optional help for a command (NULL for no help)
          true,                 // flag whether to tokenize arguments
          nullptr,              // optional pointer to any application context
          home                  // binding function
  });

  cli->onCommand = onCommand;
  cli->writeChar = writeChar;

  setUpSPI();
  configureStepper(myStepper);
  // sanity check that we can read the CONFIG register on the chip. Should be 0x2E88 on bootup
  int temp = myStepper.getParam(CONFIG);
  Serial.print("Config reg value: ");
  Serial.println(temp, HEX);
}

void loop() {

  if (cli == NULL) {
    return;
  }

  // provide all chars to cli
  while (Serial.available() > 0) {
      embeddedCliReceiveChar(cli, Serial.read());
  }
  
  embeddedCliProcess(cli);
  // myStepper.move(FWD, 50000);
  // while (myStepper.busyCheck());
  // myStepper.softStop();
  // delay(1000);
  // myStepper.move(REV, 50000);
  // while (myStepper.busyCheck());
  // myStepper.softStop();
  // delay(1000);
}

void setPower(EmbeddedCli *cli, char *args, void *context) {
    setPowerKvals(*args);
}

void home(EmbeddedCli *cli, char *args, void *context) {
    Serial.println(F("Homing Axis "));
    homeZAxis();
    Serial.print("\r\n");   
}

void onCommand(EmbeddedCli *embeddedCli, CliCommand *command) {
    Serial.println(F("Received command:"));
    Serial.println(command->name);
    embeddedCliTokenizeArgs(command->args);
    for (int i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) {
        Serial.print(F("arg "));
        Serial.print((char) ('0' + i));
        Serial.print(F(": "));
        Serial.println(embeddedCliGetToken(command->args, i));
    }
}

void onHello(EmbeddedCli *cli, char *args, void *context) {
    Serial.print(F("Hello "));
    if (embeddedCliGetTokenCount(args) == 0)
        Serial.print((const char *) context);
    else
        Serial.print(embeddedCliGetToken(args, 1));
    Serial.print("\r\n");
}

void onLed(EmbeddedCli *cli, char *args, void *context) {
    Serial.print(F("LED: "));
    Serial.print(random(256));
    Serial.print("\r\n");
}

void onAdc(EmbeddedCli *cli, char *args, void *context) {
    Serial.print(F("ADC: "));
    Serial.print(random(1024));
    Serial.print("\r\n");
}

void writeChar(EmbeddedCli *embeddedCli, char c) {
    Serial.write(c);
}