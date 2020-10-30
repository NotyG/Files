#include "QTRRobo.h"
#include <QTRSensors.h>
#include <PMotor.h>
#include "Servo.h"

PMotor motorRight(8, 9, 7);
PMotor motorLeft(10, 11, 12);

QTRRobo* qtrrcLeft = new QTRRobo((unsigned char[]) {
  39, 41, 43, 45, 47, 49, 51, 53
}, 8, 1000, 52, 100);

Servo hand;

#define PWMB 7
#define BIN2 8
#define BIN1 9

#define PWMA 12
#define AIN2 11
#define AIN1 10

#define BUTTONL 40 //48
#define BUTTONR 42 //50

#define GREEN 40
#define RED 36
#define BLUE 42

#define DIR 5
#define PWM 4

#define NUM_SENSORS   8
#define TIMEOUT       2500
#define EMITTER_PIN 15


#define gray 400
float error_old = 0, It_old = 0, speedDC = 120, maxSpeed = 120;
float Kp = 20;
float Ki = 0.5;
float Kd = 100;
float slow = 1.2;
//QTRSensors qtr((unsigned char[]) {
//  37, 39, 41, 43, 45, 47, 49, 51
//},
//NUM_SENSORS, TIMEOUT, EMITTER_PIN);




unsigned int sensorValues[8];


void setup() {
  presetup();

  while(digitalRead(BUTTONR) != 1){
    ;
  }

  delay(2000);
  //test();
  //kalibrovka();
  //ledTurn(GREEN,1);
  
}

void loop() {

 lineDetectLeft();
 }

void presetup(){
  pinMode(BUTTONL, INPUT);
  pinMode(BUTTONR, INPUT);

  pinMode(PWMA, OUTPUT);                                                        
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);

  pinMode(DIR, OUTPUT);
  pinMode(PWM, OUTPUT);
  Serial.begin(9600);
  pinMode(A14, INPUT);
  
}

//void getValues() {
//  qtr.read(values);
//}
//
//void printValues() {
//  for (int i = 0; i < 8; i++) {
//    Serial.print(values[i]);
//    Serial.print('\t');
//  }
//  Serial.println(" ");
//}
//
//void calibr() {
//  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
//  {
//    qtr.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
//  }
//  Serial.print("max ");
//  for (int i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print(qtr.calibratedMinimumOn[i]);
//    Serial.print(' ');
//  }
//  Serial.println();
//  Serial.print("min");
//
//  for (int i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print(qtr.calibratedMaximumOn[i]);
//    Serial.print(' ');
//  }
//  Serial.println(' ');
//}


void servo() {
  hand.attach(3);
  hand.write(90);
  hand.detach();
}

void motors() {
  forward();
  delay(1000);
  stopMotors();
  delay(2000);
}

void balka() {
  if (digitalRead(BUTTONL) == 0) {
    digitalWrite(DIR, 0);
    analogWrite(PWM, 100);
  }

  else {
    digitalWrite(DIR, 1);
    analogWrite(PWM, 100);
    delay(1500);
    analogWrite(PWM, 0);
  }
}

void forward() {
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 0);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  analogWrite(PWMB, 255);
}

void stopMotors() {
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 1);
  analogWrite(PWMA, 0);

  digitalWrite(BIN1, 0);
  digitalWrite(BIN2, 0);
  analogWrite(PWMB, 0);
}

float pidLeft() {
  float Pt = 0, It = 0, Dt = 0, error = 0;
  boolean flag = true;
  error = qtrrcLeft->error(sensorValues);
  if (sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray && sensorValues[4] < gray && sensorValues[5] < gray  && sensorValues[6] < gray  && sensorValues[7] < gray) {
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    delay(50);
  }
  while ((sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray && sensorValues[4] < gray && sensorValues[5] < gray  && sensorValues[6] < gray  && sensorValues[7] < gray)) {
    if (error_old > 0) {
      motorRight.run(FORWARD);
      motorLeft.run(BACKWARD);
      motorLeft.setSpeed(150);
      motorRight.setSpeed(150);
    }
    else {
      motorRight.run(BACKWARD);
      motorLeft.run(FORWARD);
      motorLeft.setSpeed(150);
      motorRight.setSpeed(150);
    }
  }
  Serial.println(error);
  Pt = Kp * error;
  //It = It_old + Ki * error;
  //It_old = It;
  Dt = Kd * (error - error_old);
  error_old = error;
  return Pt + It + Dt;
  }

void lineDetectLeft() {
  float du = pidLeft();
  speedDC = 150;
  //  speedDC = speedDC - 0.01 * abs(du);
  //  if (speedDC < 90) speedDC = 90;
  //  if (speedDC < maxSpeed) speedDC = speedDC + 1.2;
  //
  double v1 = speedDC  - du;
  double v2 = speedDC  + du;


  if (v1 < 0) v1 = 0;
  if (v2 < 0) v2 = 0;
  if (v1 > 255) v1 = 255;
  if (v2 > 255) v2 = 255;
  Serial.print("  ");
  Serial.print(v1);
  Serial.print("  ");
  Serial.println(v2);


  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  motorRight.setSpeed(v1);
  motorLeft.setSpeed(v2);
}

float irTest(){
  return analogRead(A14);
}

void buttons() {

  Serial.print(digitalRead(BUTTONL));
  Serial.print("\t");
  Serial.println(digitalRead(BUTTONR));
  delay(300);

}

void ledTurn(byte pin, boolean value) {
  digitalWrite(pin, value);
}

void blink(byte pin,  int t) {
  ledTurn(pin, 1);
  delay(t);
  ledTurn(pin, 0);
  delay(t);
}

void kalibrovka() {
  blink(RED, 2000);
  qtrrcLeft->calibrateEEPROM();
  blink(GREEN, 2000);

}

void test() {
  qtrrcLeft->printMinMax();
  //Serial.println('\t');
  //qtrrcRight->printMinMax();
  while (1) {
    Serial.print(digitalRead(BUTTONL));
    Serial.print('\t');
    Serial.println(digitalRead(BUTTONR));
    Serial.print("LeftCalibrated   ");      Serial.print('\t');
    qtrrcLeft->readCalibrated(sensorValues);
    for (int i = 0; i < 8; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }
    Serial.print("Left   ");      Serial.print('\t');
    qtrrcLeft->read(sensorValues);
    for (int i = 0; i < 8; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }

//    Serial.println();
//    Serial.print("RightCalibrated     ");      Serial.print('\t');
//    qtrrcRight->readCalibrated(sensorValues);
//    for (int i = 0; i < 8; i++) {
//      Serial.print(sensorValues[i]);
//      Serial.print('\t');
//    }
//    Serial.print("Right ");      Serial.print('\t');
//    qtrrcRight->read(sensorValues);
//    for (int i = 0; i < 8; i++) {
//      Serial.print(sensorValues[i]);
//      Serial.print('\t');
//    }

    Serial.println();

//    Serial.println();
//    Serial.print("Right=");
//    Serial.print(rightCount);
//    Serial.print('\t');
//    Serial.print("Left=");
//    Serial.print(leftCount);
    Serial.println();
    delay(1000);
  }
}
