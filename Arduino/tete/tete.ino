#include <AFMotor.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>
#include <Servo.h>
#define NUM_SENSORS   4    // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {
  18, 17, 16, 15
},
NUM_SENSORS, TIMEOUT);
unsigned int sensorValues[NUM_SENSORS];

AF_DCMotor motorL(1);
AF_DCMotor motorR(2);
Ultrasonic ultrasonic(14, 13);
Servo handLeft, handRight;
int distance;
float error_old = 0, It_old = 0, speedDC = 80, maxSpeed = 100, error = 0; //+60
boolean flag = true;
float Kp = 40;
float Ki = 0.005;
float Kd = 300;
float slow = 0.1;
float pidLeft();
unsigned long count = 0;
boolean stopCross = false;
boolean stopWhite = false;
boolean stopBanka = false;
int gray  = 300;
void lineDetect(boolean helpNeed = true);
float pidLeft(boolean helpNeed = true);
void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, motor, CHANGE);
  handLeft.attach(10);
  handRight.attach(9);
  zahvatOpen();
  kalibrovka();
  zahvatClose();
  zahvatOpen();

  delay(1000);

  Serial.begin(9600);
  delay(2500);

  distance = ultrasonic.read();
  distance = ultrasonic.read();
  distance = ultrasonic.read();
  while (distance > 6) {
    distance = ultrasonic.read();
  }


  forward(200); //возможно backward
  robotStop();
  delay(200);

  goDistLine(1200);
  goToCross();
  delay(3000);

  goDistLine(50);//на 50 мм по линии
  delay(3000);
  speedDC = 60, maxSpeed = 120;
  task();
  goToCross();
  goDistLine(50);//на 50 мм по линии
  task();
  goToCross();
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  motorR.setSpeed(140);
  motorL.setSpeed(140);
  delay(500);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  zahvatClose();

}


void task() {
  turn(90);//поворот на 90 влево
  delay(2000);
  //turnToBlack(true);
  delay(200);
  goToWhiteBanka();
  delay(200);
  if (stopBanka == true) {
    goToWhite();
    zahvatClose();
    turn(180);
    turnToBlack(true);
    goToCross();
    goToWhite();
    zahvatOpen();
    backward(200);
    delay(300);
    turn(180);
    turnToBlack(true);
    goToCross();
    goDistLine(50);
    turn(-70);
    turnToBlack(false);
  } else {
    turn(190);
    turnToBlack(true);
    goToCross();
    goToWhite();
    zahvatClose();
    delay(200);
    turn(180);
    turnToBlack(true);
    goToCross();
    goToWhite();
    zahvatOpen();
    delay(200);
    backward(200);
    delay(300);
    turn(180);
    turnToBlack(true);
    goToCross();
    goDistLine(50);
    turn(70);
    turnToBlack(true);
  }
}

void forward(int t) {
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  motorR.setSpeed(160);
  motorL.setSpeed(160);
  delay(t);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}

void backward(int t) {
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
  motorR.setSpeed(160);
  motorL.setSpeed(160);
  delay(t);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}


void motor() {
  count++;
}

void zahvatOpen() {
  handLeft.attach(10);
  handRight.attach(9);
  handLeft.write(150);
  handRight.write(30);
  delay(1000);
}

void zahvatClose() {
  handLeft.write(0);
  handRight.write(160);
  delay(1000);
  handLeft.detach();
  handRight.detach();

}
void loop()
{



}

void kalibrovka() {

  for (int i = 0; i < 400; i++) {
    qtrrc.calibrate();
  }
}

void turnToBlack(boolean direction) {
  if (direction == true) {
    motorR.run(FORWARD);
    motorL.run(BACKWARD);
  } else {
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
  }
  motorR.setSpeed(150);
  motorL.setSpeed(150);
  qtrrc.readCalibrated(sensorValues);
  while (sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray) {
    qtrrc.readCalibrated(sensorValues);
    motorR.setSpeed(150);
    motorL.setSpeed(150);
  }

  if (direction > 0) {
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  } else {
    motorR.run(FORWARD);
    motorL.run(BACKWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  }

  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorR.run(FORWARD);
  motorL.run(FORWARD);
}

void turn(float alfa) {
  count = 0;

  if (alfa > 0) {
    motorR.run(FORWARD);
    motorL.run(BACKWARD);
  } else {
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
  }
  double v = 0; double t = 0;
  while (count < abs(alfa) * 4.35) {
    motorR.setSpeed(150);
    motorL.setSpeed(150);
    Serial.println(count);
  }

  if (alfa > 0) {
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  } else {
    motorR.run(FORWARD);
    motorL.run(BACKWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  }

  count = 0;

  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorR.run(FORWARD);
  motorL.run(FORWARD);
}


void goDistLine(int s) {

  count = 0;


  if (s > 0) {
    motorR.run(FORWARD);
    motorL.run(FORWARD);
  } else {
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);
  }
  double v = 0; double t = 0;
  s = abs(s);
  while (count < s * 5.5) {
    lineDetect();
  }

  if (s > 0) {
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  } else {
    motorR.run(FORWARD);
    motorL.run(FORWARD);
    motorR.setSpeed(90);
    motorL.setSpeed(90);
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
  }



  motorR.run(RELEASE);
  motorL.run(RELEASE);
  count = 0;

  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorR.run(FORWARD);
  motorL.run(FORWARD);




}





void goToCross() {
  stopCross = false;
  while (!stopCross) {
    lineDetect();
    stopCross = getCross();
  }
  robotStop();
}

void goToWhite() {
  stopWhite = false;
  while (!stopWhite) {
    lineDetect(false);
    stopWhite = getWhite();
  }
  robotStop();
}

void goToWhiteBanka() {
  stopWhite = false;
  stopBanka = false;
  while (!stopWhite && !stopBanka) {
    lineDetect(false);
    stopWhite = getWhite();
    stopBanka = getBanka();
  }
  robotStop();
}



void printCalibrated() {

  qtrrc.readCalibrated(sensorValues);

  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);

}

void lineDetect(boolean helpNeed) {
  float du = pidLeft(helpNeed);
  //  speedDC = speedDC - slow * abs(du);
  //  if (speedDC < 60) speedDC = 60;
  //  if (speedDC < maxSpeed) speedDC = speedDC + 1.2;
  double v1 = speedDC - du;
  double v2 = speedDC + du;
  if (v1 < 0) v1 = 0;
  if (v2 < 0) v2 = 0;
  if (v1 > maxSpeed) v1 = maxSpeed;
  if (v2 > maxSpeed) v2 = maxSpeed;
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  motorR.setSpeed(v1);
  motorL.setSpeed(v2);
}

float pidLeft(boolean helpNeed) {
  float Pt = 0, It = 0, Dt = 0;
  flag = true;
  error = qtrrc.readLine(sensorValues) / 1000.0 - 1.5;
  if (helpNeed) {
    help();
  }
  motorR.run(FORWARD);
  motorL.run(FORWARD);
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

void robotStop() {
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
  motorR.setSpeed(100);
  motorL.setSpeed(100);
  delay(30);
  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}


boolean getCross() {
  int s = 0;
  for (int i = 0; i < 4; i++) {
    s += sensorValues[i];
  }
  if (s > 3000) return true;
  else return false;
}

boolean getWhite() {
  if (sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray) return true;
  else return false;
}

boolean getBanka() {
  distance = ultrasonic.read();
  if (distance < 15)return true;
  return false;
}

void help() {
  while ((sensorValues[0] < gray && sensorValues[1] < gray && sensorValues[2] < gray && sensorValues[3] < gray)) {
    if (error_old > 0) {
      motorR.run(BACKWARD);
      motorL.run(FORWARD);
      motorR.setSpeed(150);
      motorL.setSpeed(150);
    }
    else {
      motorR.run(FORWARD);
      motorL.run(BACKWARD);
      motorR.setSpeed(150);
      motorL.setSpeed(150);
    }
    error = qtrrc.readLine(sensorValues);
    It_old = 0;
    flag = false;
  }
}
