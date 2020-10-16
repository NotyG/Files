#ifndef PMotor_h
#define PMotor_h

#include <Arduino.h>

#define RELEASE 0
#define FORWARD 1
#define BACKWARD 2

class PMotor{
  public:
    PMotor(int IN1,int IN2, int PWM);
    void run(int dir);
    void setSpeed(int velocity);
  private:
    int _IN1;
    int _IN2;
    int _PWM;
};

#endif
