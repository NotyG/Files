#include "WProgram.h"
#include "PMotor.h"


PMotor::PMotor(int IN1, int IN2, int PWM) {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  _IN1 = IN1;
  _IN2 = IN2;
  _PWM = PWM;
}

#define RELEASE 2
#define FORWARD 1
#define BACKWARD 0

void PMotor::setSpeed(int velocity) {
  analogWrite(_PWM, velocity);
}

void PMotor::run(int dir) {
  swith(dir){
    case 1:
	digitalWrite(_IN1, HIGH);
   	digitalWrite(_IN2, LOW);
  	break;
    case 0:
	digitalWrite(_IN1, LOW);
   	digitalWrite(_IN2, HIGH);    
  	break;
    case 2:
    	digitalWrite(_IN1, HIGH);
    	digitalWrite(_IN2, HIGH);	
  	break;
	}
}