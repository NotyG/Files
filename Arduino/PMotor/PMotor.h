#ifndef "PMotor.h"
#define "PMotor.h"

#include "WProgram.h"
#include "Arduino.h"

#define RELEASE 2
#define FORWARD 1
#define BACKWARD 0

class PMotor{
  public:
    PMotor(int IN1,int IN2, int PWM);
    void run(bool dir);
    void setSpeed(int velocity);
  private:
    int _IN1;
    int _IN2;
    int _PWM;
};

#endif
