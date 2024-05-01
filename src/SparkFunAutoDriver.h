#ifndef AutoDriver_h
#define AutoDriver_h

#include "Arduino.h"
#include <SPI.h>
#include "SparkFundSPINConstants.h"

class AutoDriver
{
  public:
    // Constructors. We'll ALWAYS want a CS pin and a reset pin, but we may
    //  not want a busy pin. By using two constructors, we make it easy to
    //  allow that.
    AutoDriver(int position, int CSPin, int resetPin, int busyPin);
    AutoDriver(int position, int CSPin, int resetPin);

    void SPIPortConnect(SPIClass *SPIPort);
    
    // These are super-common things to do: checking if the device is busy,
    //  and checking the status of the device. We make a couple of functions
    //  for that.
    int busyCheck();
    int getStatus();
    
    // Some users will want to do things other than what we explicitly provide
    //  nice functions for; give them unrestricted access to the parameter
    //  registers.
    void setParam(byte param, unsigned long value);
    long getParam(byte param);
    
    // Lots of people just want Commands That Work; let's provide them!
    // Start with some configuration commands
    void setLoSpdOpt(boolean enable);
    void configSyncPin(byte pinFunc, byte syncSteps);
    void configStepMode(byte stepMode);
    void setMaxSpeed(float stepsPerSecond);
    void setMinSpeed(float stepsPerSecond);
    void setFullSpeed(float stepsPerSecond);
    void setAcc(float stepsPerSecondPerSecond);
    void setDec(float stepsPerSecondPerSecond);
    void setOCThreshold(byte threshold);
    void setPWMFreq(int divisor, int multiplier);
    void setSlewRate(int slewRate);
    void setOCShutdown(int OCShutdown);
    void setVoltageComp(int vsCompMode);
    void setSwitchMode(int switchMode);
    void setOscMode(int oscillatorMode);
    void setAccKVAL(byte kvalInput);
    void setDecKVAL(byte kvalInput);
    void setRunKVAL(byte kvalInput);
    void setHoldKVAL(byte kvalInput);
    void setIntSpeed(float stepsPerSecond);
    void setStSlope(byte slopeInput);
    void setAccFnSlope(byte slopeInput);
    void setDecFnSlope(byte slopeInput);
    void setKTherm(byte kthermInput);
    void setStallThreshold(byte stallThresholdInput);
    void setAlarmMask(byte alarmMaskInput);
    void setIcConfig(byte icConfigInput);



    boolean getLoSpdOpt();
    // getSyncPin
    byte getStepMode();
    float getMaxSpeed();
    float getMinSpeed();
    float getFullSpeed();
    float getAcc();
    float getDec();
    byte getOCThreshold();
    int getPWMFreqDivisor();
    int getPWMFreqMultiplier();
    int getSlewRate();
    int getOCShutdown();
    int getVoltageComp();
    int getSwitchMode();
    int getOscMode();
    byte getAccKVAL();
    byte getDecKVAL();
    byte getRunKVAL();
    byte getHoldKVAL();
    
    // ...and now, operational commands.
    long getPos();
    long getMark();
    void run(byte dir, float stepsPerSec);
    void stepClock(byte dir);
    void move(byte dir, unsigned long numSteps);
    void goTo(long pos);
    void goToDir(byte dir, long pos);
    void goUntil(byte action, byte dir, float stepsPerSec);
    void releaseSw(byte action, byte dir);
    void goHome();
    void goMark();
    void setMark(long newMark);
    void setPos(long newPos);
    void resetPos();
    void resetDev();
    void softStop();
    void hardStop();
    void softHiZ();
    void hardHiZ();
    
    
  private:
    byte SPIXfer(byte data);
    long xferParam(unsigned long value, byte bitLen);
    long paramHandler(byte param, unsigned long value);
    
    // Support functions for converting from user units to L6470 units
    unsigned long accCalc(float stepsPerSecPerSec);
    unsigned long decCalc(float stepsPerSecPerSec);
    unsigned long minSpdCalc(float stepsPerSec);
    unsigned long maxSpdCalc(float stepsPerSec);
    unsigned long FSCalc(float stepsPerSec);
    unsigned long intSpdCalc(float stepsPerSec);
    unsigned long spdCalc(float stepsPerSec);

    // Support functions for converting from L6470 to user units
    float accParse(unsigned long stepsPerSecPerSec);
    float decParse(unsigned long stepsPerSecPerSec);
    float minSpdParse(unsigned long stepsPerSec);
    float maxSpdParse(unsigned long stepsPerSec);
    float FSParse(unsigned long stepsPerSec);
    float intSpdParse(unsigned long stepsPerSec);
    float spdParse(unsigned long stepsPerSec);
 
    int _CSPin;
    int _resetPin;
    int _busyPin;
    int _position;
    static int _numBoards;
    SPIClass *_SPI;
};                                                   

#endif
