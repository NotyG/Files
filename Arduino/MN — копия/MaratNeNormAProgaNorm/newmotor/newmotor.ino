#include <QTRSensors.h>

#define END_OUT 50
#define NUM_SENSORS 8
#define gray 200 //400
#define TIMEOUT 2500
#define EMITTER_PIN 35
#define AIN1 11
#define AI2  12
#define PWMA 13
#define BIN1
#define BIN2
#define PWMB
#define MOTORA true
#define MOTORB false
#define FORWARD true
#define BACKWARD false

unsigned long rightCount = 0, leftCount = 0;
float error_old = 0, It_old = 0, speedDC = 100, maxSpeed = 150, error = 0;
float Kp = 80;
float Ki = 0.005;
float Kd = 600;

QTRSensorsRC qtrrc((unsigned char[]) {
  37, 39, 41, 43, 45, 47, 49, 51
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);

void setup() {
  pinMode(END_OUT, INPUT);
  attachInterrupt(4, rightMotor, CHANGE);
  attachInterrupt(5, leftMotor, CHANGE);
  pinMode(AIN1, OUTPUT);
  pinMode (AI2, OUTPUT);
  pinMode (PWMA, OUTPUT);
  pinMode (PWMB, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode (BIN1, OUTPUT);
  
}

void loop() {
  

}

void motorSetSpeed(bool motor, int v) {
  if (motor == 1) {
    digitalWrite(PWMA, v);
    )
    else if (motor == 2) {
    analogWrite(PWMB, v);
    }
  }

  void motorDir(bool motor, bool dir ) {
    if (motor == true) {
      if (dir == true) {
        digitalWrite(AIN1, 1);
        digitalWrite(AIN2, 0);
      }
      else if (dir == false){
        digitalWrite(AIN1, 0);
        digitalWrite(AIN2, 1);
      }
    }
    else if (motor == false) {
      if (dir == true) {
        digitalWrite(BIN1, 1);
        digitalWrite(BIN2, 0);
      }
      else if (dir == false) {
        digitalWrite(AIN1, 0);
        digitalWrite(AIN2, 1);
      }
    }
  }

  void robotStop() {
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 1);
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 1);
  }
