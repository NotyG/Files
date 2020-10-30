/*программа на заряд 8.2v

*/
#include <QTRSensors.h>
#include <AFMotor.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <TimerThree.h>
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo hand;
#define END_IN 30
#define END_OUT 32
#define NUM_SENSORS 8
#define gray 400 //400
#define RED 33
#define GREEN 31
#define BLUE 35
#define CLOSE 7//7
#define OPEN 175
#define TIMEOUT 2500 // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN 15 // emitter is controlled by digital pin 2
enum TypeCube {
  BIG_WHITE, //большой белый
  BIG_BLACK,//большой черный
  SMALL_WHITE,//маленький белый
  SMALL_BLACK,//маленький черный
  SMALL,
};

enum mode {FAST, SLOW};
enum direction {OUT, IN};
unsigned long rightCount = 0, leftCount = 0;

float error_old = 0, It_old = 0, speedDC = 100, maxSpeed = 150, error = 0;
float Kp = 80;
float Ki = 0.005;
float Kd = 600;
float slow = 1.2;
AF_DCMotor motorRight(1);
AF_DCMotor motorLeft(2);
AF_DCMotor balka(4);
QTRSensorsRC qtrrc((unsigned char[]) {
  37, 39, 41, 43, 45, 47, 49, 51
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
TypeCube cubes[10];
int x = 0;
int y = 0;

boolean stopCross = false;
boolean stopCube = false;

void preSetup();

void setup() {

  preSetup();
  /*while(1){
    getTypeCube();
    //delay(1000);
    }*/

  balkaMove(OUT);
  kalibrovka();
  while (!digitalRead(END_IN)) {
    ;
  }

  //goOutStart();

  lineDetectLeft();
  //method1(BIG_WHITE);
  //  for (int i = 0; i < 10; ++i) {
  //    goToCubeLeft();
  //    stopLeft(SLOW);
  //    goDistLineLeft(10);
  //    while (getCubeLeft()) {
  //      lineDetectLeft();
  //    }
  //    stopLeft(FAST);
  //    getTypeCube();
  //    delay(1000);
  //    goDistLineLeft(20);
  //  }
  // method2(BIG_WHITE); //возит по два цвета
  //method2(BIG_BLACK);
}


void loop() {
  ;
}

TypeCube getTypeCube() {
  uint16_t clear, red, green, blue;
  delay(100);
  tcs.getRawData(&red, &green, &blue, &clear);
  //  Serial2.print("c1=");
  //  Serial2.print(clear);

  uint16_t clear_new, red_new, green_new, blue_new;

  for (int i = 0; i < 4; i++) {
    tcs.getRawData(&red_new, &green_new, &blue_new, &clear_new);
    clear = 0.5 * clear + 0.5 * clear_new;
    red = 0.5 * red + 0.5 * red_new;
    green = 0.5 * green + 0.5 * green_new;
    blue = 0.5 * blue + 0.5 * blue_new;
  }
  Serial.print("  c2=");
  Serial.println(clear);
  if (clear < 250) {
    //blink(RED, 100);
    return SMALL_BLACK;
  }
  if (clear < 900) {
    blink(GREEN, 1000);
    return BIG_BLACK;
  }
  if (clear < 2000) {
    blink(RED, 1000);
    return SMALL_WHITE;
  }

  blink(BLUE, 1000);
  return BIG_WHITE;

}

void goOutStart() {
  handClose();
  delay(1000);
  goDistLeft(100);
  delay(500);
  goToCrossLeft();
  delay(500);
  goDistLineLeft(90);
  stopLeft(FAST);
  delay(500);
  turn(90);
  goDistLineLeft(90);
  stopLeft(FAST);
}

void handClose() {
  for (int i = OPEN; i > CLOSE; i--) {
    hand.write(i);
    delay(2);
  }
  delay(80);
  //hand.detach();
}

void preSetup() {
  pinMode(END_IN, INPUT);
  pinMode(END_OUT, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, 1);
  digitalWrite(GREEN, 1);
  digitalWrite(BLUE, 1);


  attachInterrupt(4, rightMotor, CHANGE);
  attachInterrupt(5, leftMotor, CHANGE);
  Serial.begin(9600);
  Serial2.begin(9600);
  tcs.begin();
  hand.attach(10);
  handOpen();
}

void takeFirst() {
  handOpen();
  balkaMove(IN);
  handClose();
  balkaMove(OUT);
}

void pop() {
  balkaMove(IN);
  handOpen();
  balkaMove(OUT);
}

void method1(TypeCube type) {
  int count = 0;
  stopCross = false;
  stopCube = false;
  while (!stopCross) {
    stopCross = false;
    stopCube = false;
    speedDC = 150;
    lineDetectLeft();
    goToCrossCubeLeft();
    if (stopCube) {
      stopLeft(SLOW);
      goDistLineLeft(10);
      while (getCubeLeft()) {
        lineDetectLeft();
      }
      stopLeft(FAST);
      if (getTypeCube() == type) {
        count++;
        if (count == 1) {
          takeFirst();
          goDistLineLeft(20);
          stopCube = false;
        } else {
          takeFirst();
          maxSpeed = 255;
          goToCrossLeft();
          goDistLineLeft(90);
          turn(-120);
          delay(1000);
          goToCrossLeft();
          turn(-90);
          delay(1000);
          pop();
          delay(1000);
          turn(-90);
          delay(1000);
          goToCrossLeft();
          goDistLineLeft(90);
          turn(-130);
          delay(1000);
          maxSpeed = 120;
          goDistLineLeft(90);
          handClose();
          stopCross = false;
          stopCube = false;
          count = 0;
        }
      } else {
        goDistLineLeft(90);
      }
    } else {
      if (count > 0) {
        goDistLineLeft(90);
        turn(-120);
        delay(1000);
        goToCrossLeft();
        turn(-90);
        delay(1000);
        pop();
        delay(1000);
        turn(-90);
        delay(1000);
        goToCrossLeft();
        goDistLineLeft(90);
        turn(-130);
        delay(1000);
        maxSpeed = 120;
        goDistLineLeft(90);
        handClose();
      }
      stopCross = true;
      stopCube = true;
    }
  }
}
void rightMotor()
{
  rightCount++;
}

void leftMotor()
{
  leftCount++;
}

void zeroMotor() {
  rightCount = 0;
  leftCount = 0;
}

void handOpen() {
  for (int i = CLOSE; i < OPEN; i++) {
    hand.write(i);
    delay(5);
  }
  // delay(50);
}

void balkaMove(direction d) {
  switch (d) {
    case OUT:
      balka.run(FORWARD);
      balka.setSpeed(255);
      while (!digitalRead(END_OUT)) {
        ;
      }
      break;
    case IN:
      balka.run(BACKWARD);
      balka.setSpeed(255);
      while (!digitalRead(END_IN)) {
        ;
      }
      break;
  }
  delay(200);
  balka.run(RELEASE);
}

void testStart() {

  // test();

  //testPidLeft();
  //testLed();
  //  while (1) {
  //    lineDetectLeft();
  //  }
  //goToCrossCubeLeft();
  //testColorSensor();
  // test();
  // motorTest();
}

void lineDetectLeft() {

  float du = pidLeft();
  //  speedDC = speedDC - 0.01 * abs(du);
  //  if (speedDC < 90) speedDC = 90;
  //  if (speedDC < maxSpeed) speedDC = speedDC + 1.2;

  double v1 = speedDC - du;
  double v2 = speedDC + du;
  if (v1 < 10) v1 = 10;
  if (v2 < 10) v2 = 10;
  if (v1 > maxSpeed) v1 = maxSpeed;
  if (v2 > maxSpeed) v2 = maxSpeed;
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  motorRight.setSpeed(v1);
  motorLeft.setSpeed(v2);
}

float pidLeft() {
  float Pt = 0, It = 0, Dt = 0;
  boolean flag = true;
  error = qtrrc.readLine(sensorValues) / 1000.0 - 3.5;
  while ((sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray && sensorValues[4] < gray && sensorValues[5] < gray && sensorValues[6] < gray && sensorValues[7] < gray)) {
    if (error_old > 0) {
      motorRight.run(BACKWARD);
      motorLeft.run(FORWARD);
      motorLeft.setSpeed(150);
      motorRight.setSpeed(150);
    }
    else {
      motorRight.run(FORWARD);
      motorLeft.run(BACKWARD);
      motorLeft.setSpeed(150);
      motorRight.setSpeed(150);
    }
    error = qtrrc.readLine(sensorValues);

    It_old = 0;
    flag = false;
  }
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  Pt = Kp * error;
  It = It_old + Ki * error;
  if (It > 100) {
    It = 100;
  }
  if (It < -100) {
    It = -100;
  }
  It_old = It;
  Dt = Kd * (error - error_old);
  error_old = error;
  return Pt + It + Dt;
}
void blink(byte pin,  int t) {
  ledTurn(pin, 0);
  delay(t);
  ledTurn(pin, 1);
  delay(t);
}

void testLed() {
  while (1) {
    ledTurn(RED, LOW);
    delay(1000);
    ledTurn(RED, HIGH);
    delay(1000);

    ledTurn(GREEN, LOW);
    delay(1000);
    ledTurn(GREEN, HIGH);
    delay(1000);

    ledTurn(BLUE, LOW);
    delay(1000);
    ledTurn(BLUE, HIGH);
    delay(1000);
  }
}
void ledTurn(byte pin, boolean value) {
  digitalWrite(pin, value);
}
void kalibrovka() {
  blink(GREEN, 1000);
  blink(RED, 1000);
  for (int i = 0; i < 300; i++) // make the calibration take about 10 seconds
  {
    qtrrc.calibrate(); // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  blink(GREEN, 2000);

}

void goToCrossCubeLeft() {
  stopCube = false;
  stopCross = false;
  lineDetectLeft();
  lineDetectLeft();
  lineDetectLeft();

  while (!stopCube && !stopCross) {
    lineDetectLeft();
    stopCross = getCrossLeft();
    stopCube = getCubeLeft();
  }
  stopLeft(FAST);
}


void goToCrossLeft() {
  lineDetectLeft();
  lineDetectLeft();
  stopCross = false;
  while (!stopCross) {
    lineDetectLeft();
    stopCross = getCrossLeft();
    // stopCube = getCubeLeft();
  }

  stopLeft(FAST);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
}


void goToCubeLeft() {
  lineDetectLeft();
  lineDetectLeft();
  stopCube = false;
  while (!stopCube) {
    lineDetectLeft();
    stopCross = getCrossLeft();
    stopCube = getCubeLeft();
  }
}




boolean getCrossLeft() {
  qtrrc.readCalibrated(sensorValues);
  int s = 0;
  for (int i = 0; i < 8; i++) {
    s += sensorValues[i];
  }
  if (s > 7500) return true;
  else return false;
}

boolean getCubeLeft() {

  x = 0.5 * x + 0.5 * analogRead(A15);
  return  x > 80;
}

void stopLeft(mode m) {
  if (m == SLOW) {
    motorRight.setSpeed( speedDC / 3);
    motorLeft.setSpeed( speedDC / 3);
    for (int i = speedDC / 3; i > 0; i--) {
      motorRight.setSpeed(i);
      motorLeft.setSpeed(i);
      delay(2);
    }
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(10);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
  } else {
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
    motorRight.setSpeed(100);
    motorLeft.setSpeed(100);
    delay(30);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
  }
}


void turn(float alfa) {
  leftCount = 0;
  rightCount = 0;

  if (alfa > 0) {
    motorRight.run(FORWARD);
    motorLeft.run(BACKWARD);
  } else {
    motorRight.run(BACKWARD);
    motorLeft.run(FORWARD);
  }
  double v = 0; double t = 0;
  //  double k =  atan((130.0 - 60.0) / (alfa * 5.1 * 0.5));
  while ((leftCount < abs(alfa) * 7.3) && (rightCount < abs(alfa) * 7.3)) {
    //    if ((rightCount + leftCount) / 2.0 < alfa * 5.1 / 2.0) {
    //      v = 60 + ((rightCount + leftCount) / 2) * k;
    //    } else {
    //      v = 200 - ((rightCount + leftCount) / 2) * k;
    //    }
    //    if (v < 70)v = 70;
    //    if (v > 160)v = 160;

    motorRight.setSpeed(50);
    motorLeft.setSpeed(50);
  }

  if (alfa > 0) {
    motorRight.run(BACKWARD);
    motorLeft.run(FORWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(30);
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
  } else {
    motorRight.run(FORWARD);
    motorLeft.run(BACKWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(30);
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
  }



  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
  leftCount = 0;
  rightCount = 0;

  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
}

void goDistLeft(int s) {

  leftCount = 0;
  rightCount = 0;

  if (s > 0) {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
  } else {
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
  }
  double v = 0; double t = 0;
  s = abs(s);
  //  double k =  atan((130.0 - 60.0) / (alfa * 5.1 * 0.5));
  while ((leftCount < s * 8.8) && (rightCount < s * 8.8)) {
    //    if ((rightCount + leftCount) / 2.0 < alfa * 5.1 / 2.0) {
    //      v = 60 + ((rightCount + leftCount) / 2) * k;
    //    } else {
    //      v = 200 - ((rightCount + leftCount) / 2) * k;
    //    }
    //    if (v < 70)v = 70;
    //    if (v > 160)v = 160;
    motorRight.setSpeed(50);
    motorLeft.setSpeed(50);
  }

  if (s > 0) {
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(30);
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
  } else {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(30);
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
  }



  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
  leftCount = 0;
  rightCount = 0;

  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);




}


void goDistLineLeft(int s) {

  leftCount = 0;
  rightCount = 0;

  double v = 0; double t = 0;
  s = abs(s);
  //  double k =  atan((130.0 - 60.0) / (alfa * 5.1 * 0.5));
  while ((leftCount < s * 8.8) && (rightCount < s * 8.8)) {
    //    if ((rightCount + leftCount) / 2.0 < alfa * 5.1 / 2.0) {
    //      v = 60 + ((rightCount + leftCount) / 2) * k;
    //    } else {
    //      v = 200 - ((rightCount + leftCount) / 2) * k;
    //    }
    //    if (v < 70)v = 70;
    //    if (v > 160)v = 160;
    lineDetectLeft();
  }
}
