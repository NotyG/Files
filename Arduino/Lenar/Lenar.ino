/*
  / программа на заряд 8.2v
*/
#include "QTRRobo.h"
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
#define CLOSE 7 //7
#define OPEN 164 //175 - было много
enum TypeCube {
  BIG_WHITE, //большой белый
  BIG_BLACK,//большой черный
  SMALL_WHITE,//маленький белый
  SMALL_BLACK,//маленький черный
  SMALL,
};
enum mode {FAST, SLOW};
enum direction {OUT, IN};
long rightCount = 0, leftCount = 0;

float error_old = 0, It_old = 0, speedDC = 65, maxSpeed = 120;
float Kp = 100;
float Ki = 0.5;
float Kd = 3000;
float slow = 1.2;
AF_DCMotor motorRight(1);
AF_DCMotor motorLeft(2);
AF_DCMotor balka(4);
QTRRobo* qtrrcLeft = new QTRRobo((unsigned char[]) {
  50, 48, 46, 44, 42, 40, 38, 36
}, 8, 1000, 52, 100);

QTRRobo* qtrrcRight = new QTRRobo((unsigned char[]) {
  51, 49, 47, 45, 43, 41, 39, 37 //37, 39, 41, 43, 45, 47, 49, 51 - изначальный порядок
}, 8, 1000, 53, 20);

unsigned int sensorValues[NUM_SENSORS];
TypeCube cubes[10];
int x = 0;
int y = 0;
//
void goOutStart();//Выезд из зоны старта

void preSetup();//Программа, выполняемая перед стартом, инициализация датчиков

void takeFirst();//Забирать куб

void goLineTimeLeft(int t);//Ехать по линии левым датчиком, заданное время

void goLineTimeRight(int t);//Ехать по линии правым датчиком, заданное время

void goDistLineLeft(int s); //Ехать по линии левым датчиком, заданное расстояние

void pop();//Выгрузить кубики

void afterCrossLeft();//Подготовка к выгрузке, после перекрёстка левым датчиком

void afterCrossRight();//Подготовка к выгрузке, после перекрёстка правым датчиком

void turn(float alfa);//Повернуться на alfa градусов

void handClose();//Закрыть захват

void handOpen();//Открыть захват

TypeCube getTypeCube();//Определяет цвет(тип) кубика

void testColorSensor();//Проверка датчика цвета

void test(); //проверка концевиков, датчика линии и энкодеров

void blink(byte pin,  int t = 1000);//Моргать пином pin с задержкой в t миллисекунд

void testBalka();//Проверка выезда захвата

void testLed();//Проверка светодиодов

void balkaMove(direction d);//Выдвенуть или задвинуть захват

void lineDetectLeft();//Ехать по линии левым датчиком

void lineDetectRight();//Ехать по линии правым датчиком

float pidLeft();//Вычесление рулевого воздействия по показаниям левого датчика

float pidRight();//Вычесление рулевого воздействия по показаниям правого датчика

boolean getCrossLeft();//Левые датчики видят перекрёсток?

boolean getCrossRight();//Правые датчики видят перекрёсток?

boolean getCubeLeft();//Есть ли куб перед левым датчиком растояния

boolean getCubeRight();//Есть ли куб перед правым датчиком растояния

void goToCrossLeft();//Ехать до перекрёстка левыми датчиками линии

void goToCrossRight();//Ехать до перекрёстка правыми датчиками линии

void goToCubeLeft();//Ехать до куба перед левым датчком растояния

void goToCubeRight();//Ехать до куба перед правым датчком растояния

void goToCrossCubeLeft();//Ехать налево пока не куб или не перекрёсток

void stopLeft(mode m = SLOW);//Остановка после движения на лево

void stopRight(mode m = SLOW);//Остановка после движения на право

void kalibrovka();//Калибровка датчиков линий

void motorTest();//Проверка моторов

void ledTurn(byte pin, boolean value);//Подать value на пин pin

void method1(TypeCube type);//1ый метод сбора кубиков

void method2(TypeCube type);//2ой метод сбора кубиков

void method3(TypeCube type);//3ий метод сбора кубиков

void method4(TypeCube type); //4ий метод сбора кубиков Gleb

int searchFirstLeftCube(TypeCube type, TypeCube *massiv, int k);//Вернёт индекс первого куба с заданными параметрами, начиная поиск слева

int searchFirstRightCube(TypeCube type, TypeCube *massiv, int k);//Вернёт индекс первого куба с заданными параметрами, начиная поиск справа

void moveMassiv(int number, TypeCube *massiv, int &k);//Сдвиг массива с заданного элемента

boolean stopCross = false;
boolean stopCube = false;
void setup() {

  preSetup();
  balkaMove(OUT);
  while (!digitalRead(END_IN)) {
    ;
  }
  delay(1000);
  //handClose();
  //kalibrovka();
  //testStart();
  //test();
  //motorTest();

  //goOutStart();

  //method1(BIG_BLACK);
  // method2(BIG_WHITE); //возит по два цвета
  // method2(BIG_BLACK);
}


void loop() {
  //getTypeCube();
  //lineDetectLeft();

}

void goOutStart() {
  handClose();

  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);

  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  for (int v = 0; v < 50; v++) { //150 - было много
    motorRight.setSpeed(v);
    motorLeft.setSpeed(v);
    delay(1);
  }

  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  blink(GREEN, 300);
  delay(4000);

  delay(400);
  lineDetectLeft();
  while (!getCrossLeft()) {
    lineDetectLeft();
  }

  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  blink(RED, 300);
  delay(4000);

  for (int i = 0; i < 30; i++) {//30
    lineDetectLeft();
  }


  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  blink(BLUE, 300);
  delay(4000);

  stopLeft();
  delay(500);
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);

  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  //  for (int v = 0; v < 150; v++) {
  //    motorRight.setSpeed(v);
  //    motorLeft.setSpeed(v);
  //  }
  //  delay(700);
  //
  //  motorRight.run(BACKWARD);
  //  motorLeft.run(BACKWARD);
  //
  //  delay(700);
  // motorRight.run(RELEASE);
  // motorLeft.run(RELEASE);


  turn(110);//100 //110 //-*

  goLineTimeRight(80);  //80 //Left
}




void testStart() {

  test();
  //kalibrovka();
  //testPidLeft();
  kalibrovka();//  while (1) {
  //      lineDetectLeft();
  //    }
  //testColorSensor();
  // test();
  ;
}
void preSetup() {
  pinMode(END_IN, INPUT);
  pinMode(END_OUT, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

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
  hand.attach(10);
  delay(5);
  hand.write(CLOSE + 2);
  delay(50);
  hand.detach();
}

void goLineTimeLeft(int t) {
  lineDetectLeft();
  lineDetectLeft();
  for (int i = 0; i < t; i++) {
    lineDetectLeft();
    getCubeLeft();
    getCubeRight();
    //здесь разве не нужен delay
  }
}
void goLineTimeRight(int t) {
  lineDetectRight();
  lineDetectRight();
  for (int i = 0; i < t; i++) {
    lineDetectRight();
    getCubeRight();
    getCubeLeft();
  }
}
void pop() {
  balkaMove(IN);
  handOpen();
  balkaMove(OUT);
}

void afterCrossLeft() {
  for (int i = 0; i < 100; i++) {
    lineDetectLeft();
    getCubeLeft();
  }
  hand.write(CLOSE);
  delay(10);
  for (int i = 0; i < 120; i++) {
    lineDetectLeft();
    getCubeLeft();
  }
  hand.detach();
  stopCross = false;
  stopCube = false;
}

void afterCrossRight() {
  for (int i = 0; i < 100; i++) {
    lineDetectRight();
    getCubeRight();
  }
  hand.write(CLOSE);
  delay(10);
  for (int i = 0; i < 120; i++) {
    lineDetectRight();
    getCubeRight();
  }
  hand.detach();
  stopCross = false;
  stopCube = false;
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
  alfa = abs(alfa);
  //  double k =  atan((130.0 - 60.0) / (alfa * 5.1 * 0.5));
  while ((leftCount < alfa * 5.1) && (rightCount < alfa * 5.1)) {
    //    if ((rightCount + leftCount) / 2.0 < alfa * 5.1 / 2.0) {
    //      v = 60 + ((rightCount + leftCount) / 2) * k;
    //    } else {
    //      v = 200 - ((rightCount + leftCount) / 2) * k;
    //    }
    //    if (v < 70)v = 70;
    //    if (v > 160)v = 160;

    motorRight.setSpeed(90);
    motorLeft.setSpeed(90);
    Serial2.print(leftCount);
    Serial2.print('\t'); Serial2.println(rightCount);
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

void handClose() {
  for (int i = OPEN; i > CLOSE; i--) {
    hand.write(i);
    delay(2);
  }
  delay(80);
  hand.detach();
}

void handOpen() {
  hand.attach(10);
  for (int i = CLOSE; i < OPEN; i++) {
    hand.write(i);
    delay(5);
  }
  // delay(50);
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


  if (clear < 150) {
    return SMALL_BLACK;
  }
  if (clear < 800) {
    blink(GREEN, 100);
    return BIG_BLACK;
  }
  if (clear < 1200) {
    blink(RED, 100);
    return SMALL_WHITE;
  }
  blink(BLUE, 100);
  return BIG_WHITE;

}

void testColorSensor() {
  while (1) {
    uint16_t clear, red, green, blue;
    tcs.getRawData(&red, &green, &blue, &clear);
    Serial.print("C:\t"); Serial.print(clear);
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.println(blue);
  }
}


void blink(byte pin,  int t) {
  ledTurn(pin, 1);
  delay(t);
  ledTurn(pin, 0);
  delay(t);
}
void testBalka() {
  while (1) {
    balkaMove(IN);
    delay(2000);
    balkaMove(OUT);
    delay(2000);
  }
}
void testLed() {
  while (1) {
    ledTurn(RED, HIGH);
    delay(1000);
    ledTurn(RED, LOW);
    delay(1000);

    ledTurn(GREEN, HIGH);
    delay(3000);
    ledTurn(GREEN, LOW);
    delay(1000);

    ledTurn(BLUE, HIGH);
    delay(5000);
    ledTurn(BLUE, LOW);
    delay(2000);
  }
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

void lineDetectRight() {
  float du = pidRight();
  speedDC = speedDC - 0.01 * abs(du);
  if (speedDC < 90) speedDC = 90;
  if (speedDC < maxSpeed) speedDC = speedDC + 1.2;
  double v1 = speedDC  - du;
  double v2 = speedDC  + du;
  if (v1 < 0) v1 = 0;
  if (v2 < 0) v2 = 0;
  if (v1 > 255) v1 = 255;
  if (v2 > 255) v2 = 255;
  motorRight.run(BACKWARD);
  motorLeft.run(BACKWARD);
  motorRight.setSpeed(v1);
  motorLeft.setSpeed(v2);
}

float pidLeft() {
  float Pt = 0, It = 0, Dt = 0, error = 0;
  boolean flag = true;
  error = qtrrcLeft->error(sensorValues);
  Serial.println(error);
  Pt = Kp * error;
  //It = It_old + Ki * error;
  //It_old = It;
  Dt = Kd * (error - error_old);
  error_old = error;
  return Pt + It + Dt;
}

float pidRight() {
  float Pt = 0, It = 0, Dt = 0, error = 0;
  boolean flag = true;
  error = qtrrcRight->error(sensorValues);
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
    qtrrcRight->error(sensorValues);

    It_old = 0;
    flag = false;
  }
  if ( !flag) {
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    error_old = error;//добавил вечером
    delay(50);
    flag = true;
  }
  motorRight.run(BACKWARD);
  motorLeft.run(BACKWARD);
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



// put your setup code here, to run once:
boolean getCrossLeft() {
  qtrrcLeft->error(sensorValues);
  int s = 0;
  for (int i = 0; i < 8; i++) {
    s += sensorValues[i];
  }
  if (s > 6500) return true;
  else return false;
}

boolean getCrossRight() {
  qtrrcRight->error(sensorValues);
  int s = 0;
  for (int i = 0; i < 8; i++) {
    s += sensorValues[i];
  }
  if (s > 6500) return true;
  else return false;
}
boolean getCubeLeft() {
  x = 0.5 * x + 0.5 * analogRead(A15);
  return  x > 80;
}

boolean getCubeRight() {
  y = 0.5 * y + 0.5 * analogRead(A14);
  return  y > 120;
}
void goToCrossLeft() {
  lineDetectLeft();
  lineDetectLeft();
  stopCross = false;
  while (!stopCross) {
    lineDetectLeft();
    stopCross = getCrossLeft();
    stopCube = getCubeLeft();
  }
  goLineTimeLeft(40);
  stopLeft();
}

void goToCrossRight() {
  lineDetectRight();
  lineDetectRight();
  stopCross = false;
  while (!stopCross) {
    lineDetectRight();
    stopCross = getCrossRight();
    // stopCube = getCubeLeft();
  }
  goLineTimeRight(40);
  stopRight();
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
void goToCubeRight() {
  lineDetectRight();
  lineDetectRight();
  stopCube = false;
  while (!stopCube) {
    lineDetectRight();
    stopCross = getCrossRight();
    stopCube = getCubeRight();
  }
}
void goToCrossCubeLeft() {
  stopCube = false;
  stopCross = false;
  while (!stopCube && !stopCross) {
    lineDetectLeft();
    stopCross = getCrossLeft();
    stopCube = getCubeLeft();
  }
  stopLeft();
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
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(10);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
  }
}

void stopRight(mode m) {
  if (m == SLOW) {
    motorRight.setSpeed(60);
    motorLeft.setSpeed(60);
    for (int i = 20; i > 0; i--) {
      motorRight.setSpeed(i);
      motorLeft.setSpeed(i);
      delay(2);
    }
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(10);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
  } else {
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(150);
    delay(10);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
  }
}

void kalibrovka() {
  blink(RED, 2000);
  qtrrcRight->calibrateEEPROM();
  blink(BLUE, 2000);
  qtrrcLeft->calibrateEEPROM();
  blink(GREEN, 2000);

}
void testPidLeft() {

  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  motorRight.setSpeed(255);
  motorLeft.setSpeed(255);
  while (1) {
    qtrrcLeft->printCalibrated(sensorValues);
    delay(400);
    Serial.println(qtrrcLeft->error(sensorValues));
    delay(400);
    //    qtrrcLeft->printCalibrated(sensorValues2);
    //    delay(400);
  }
}
void test() {
  qtrrcLeft->printMinMax();
  Serial.println('\t');
  qtrrcRight->printMinMax();
  while (1) {
    Serial.print(digitalRead(END_IN));
    Serial.print('\t');
    Serial.println(digitalRead(END_OUT));
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

    Serial.println();
    Serial.print("RightCalibrated     ");      Serial.print('\t');
    qtrrcRight->readCalibrated(sensorValues);
    for (int i = 0; i < 8; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }
    Serial.print("Right ");      Serial.print('\t');
    qtrrcRight->read(sensorValues);
    for (int i = 0; i < 8; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }

    Serial.println();

    Serial.println();
    Serial.print("Right=");
    Serial.print(rightCount);
    Serial.print('\t');
    Serial.print("Left=");
    Serial.print(leftCount);
    Serial.println();
    delay(1000);
  }
}
void motorTest() {
  motorRight.setSpeed(255);
  motorLeft.setSpeed(255);
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  while (1) {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    delay(2000);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    delay(500);

    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
    delay(2000);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    delay(500);
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
void ledTurn(byte pin, boolean value) {
  digitalWrite(pin, value);
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

      if (getTypeCube() == type) {
        count++;
        if (count == 1) {
          takeFirst();
          goLineTimeLeft(70);
          stopCube = false;
        } else {
          takeFirst();
          maxSpeed = 255;
          goToCrossLeft();
          pop();
          maxSpeed = 120;
          afterCrossLeft();
          stopCross = false;
          stopCube = false;
          count = 0;
        }
      } else {
        goLineTimeLeft(80);
      }
    } else {
      if (count > 0) {
        goLineTimeLeft(80); //если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();
        afterCrossLeft();
      }
      stopCross = true;
      stopCube = true;
    }

  }


  stopCross = false;
  stopCube = false;
  count = 0;
  while (!stopCross) {
    speedDC = 150;
    lineDetectLeft();
    stopCross = false;
    stopCube = false;
    goToCrossCubeLeft();
    if (stopCube) {
      count++;
      delay(200);
      if (count == 1) {
        takeFirst();
        goLineTimeLeft(70);
        stopCube = false;
      } else {
        takeFirst();
        maxSpeed = 255;
        goToCrossLeft();
        pop();
        maxSpeed = 120;
        afterCrossLeft();
        stopCross = false;
        stopCube = false;
        count = 0;
      }
    } else {
      if (count > 0) {
        goLineTimeLeft(80);//если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();
      }
      motorRight.setSpeed(0);
      motorLeft.setSpeed(0);
      motorRight.run(RELEASE);
      motorLeft.run(RELEASE);
      while (1) {
        ;
      }
    }
  }

}


void method2(TypeCube type) {
  int count = 0;
  stopCross = false;
  stopCube = false;
  zeroMotor();
  int k = 0;
  while (!stopCross) {
    stopCross = false;
    stopCube = false;
    speedDC = 150;
    lineDetectLeft();
    goToCrossCubeLeft();
    if (stopCube) {
      TypeCube typeCube = getTypeCube();
      if (typeCube == type) {
        if (++count <= 2) {
          takeFirst();
        } else {
          cubes[k++] = typeCube;
        }
      } else {
        cubes[k++] = typeCube;
      }
      stopCube = 0;
      goLineTimeLeft(80);
    } else {
      if (count > 0) {
        goLineTimeLeft(40); //если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();

        stopCross = true;
        stopCube = true;
      }
    }
  }

  zeroMotor();
  afterCrossLeft();
  maxSpeed = 200;
  count = 0;
  stopCross = false;
  stopCube = false;
  int number1 = 0;
  while (searchFirstLeftCube(type, cubes, k) >= 0) {
    lineDetectLeft();
    int number = searchFirstLeftCube(type, cubes, k) - number1;
    number1 = number;
    moveMassiv(searchFirstLeftCube(type, cubes, k), cubes, k);
    Serial2.print("number");
    Serial2.println(number);
    for (int i = 0; i < number; i++) {
      goToCubeLeft();
      goLineTimeLeft(80);
    }
    goToCubeLeft();
    stopLeft();
    if (++count == 1) {
      takeFirst();
      goLineTimeLeft(70);
      speedDC = 150;
      maxSpeed = 150;
    } else {
      takeFirst();
      maxSpeed = 200;
      speedDC = 200;
      if ((leftCount + rightCount) / 2 > 13000) {
        goToCrossLeft();
      } else {
        goToCrossRight();
      }
      pop();
      zeroMotor();
      // maxSpeed = 120;
      afterCrossLeft();
      count = 0;
      number1 = 0;
    }

  }
  if (count == 1) {
    maxSpeed = 200;
    speedDC = 200;
    if ((leftCount + rightCount) / 2 > 13000) {
      goToCrossLeft();
    } else {
      goToCrossRight();
    }
    pop();
    zeroMotor();
    afterCrossLeft();
    count = 0;
  }




  zeroMotor();
  //второй цвет
  stopCross = false;
  stopCube = false;
  count = 0;
  maxSpeed = 200;
  speedDC = 200;
  while (!stopCross) {
    lineDetectLeft();
    stopCross = false;
    stopCube = false;
    goToCrossCubeLeft();
    if (stopCube) {
      count++;
      delay(200);
      if (count == 1) {
        takeFirst();
        maxSpeed = 150;
        speedDC = 150;
        goLineTimeLeft(70);
        stopCube = false;
      } else {
        takeFirst();
        maxSpeed = 200;
        speedDC = 200;
        if ((leftCount + rightCount) / 2 > 13000) {
          goToCrossLeft();
        } else {
          goToCrossRight();
        }
        pop();
        zeroMotor();
        if ((--(--k)) > 0) {
          afterCrossLeft();
          stopCross = false;
          stopCube = false;
          count = 0;
        } else {
          stopCross = true;
          stopCube = true;
        }

      }
    } else {
      if (count > 0) {
        goLineTimeLeft(40);//если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();
      }
    }

  }
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
  while (1) {
    ;
  }

  // afterCrossLeft();
}


void method3(TypeCube type) {
  int count = 0;
  stopCross = false;
  stopCube = false;
  zeroMotor();
  int k = 0;
  //забираем первые два кубика цвета type и все остальное записываем в массив
  while (!stopCross) {
    stopCross = false;
    stopCube = false;
    speedDC = 150;
    maxSpeed = 150;
    lineDetectLeft();
    goToCrossCubeLeft();
    if (stopCube) {
      TypeCube typeCube = getTypeCube();
      if (typeCube == type) {
        if (++count <= 2) {
          takeFirst();
        } else {
          cubes[k++] = typeCube;
        }
      } else {
        cubes[k++] = typeCube;
      }
      stopCube = 0;
      goLineTimeLeft(80);
    } else {
      if (count > 0) {
        goLineTimeLeft(80); //если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();

        stopCross = true;
        stopCube = true;
      }
    }
  }


  //собираем кубики первого цвета
  zeroMotor();
  afterCrossRight();
  speedDC = 150;
  maxSpeed = 150;
  count = 0;
  stopCross = false;
  stopCube = false;
  int number1 = 0;
  int number = 0;
  while (searchFirstRightCube(BIG_WHITE, cubes, k) >= 0) {
    lineDetectRight();
    if (count == 0) {
      number = k - searchFirstRightCube(BIG_WHITE, cubes, k) - 1;
      Serial2.print("number");
      Serial2.println(number);
      number1 = searchFirstRightCube(BIG_WHITE, cubes, k);
    } else {
      number = number1 - searchFirstRightCube(BIG_WHITE, cubes, k) - 1;
    }
    moveMassiv(searchFirstRightCube(BIG_WHITE, cubes, k), cubes, k);
    Serial2.print("number");
    Serial2.println(number);
    for (int i = 0; i < number; i++) {
      goToCubeRight();
      goLineTimeRight(80);
    }
    goToCubeRight();
    stopRight();
    if (++count == 1) {
      takeFirst();
      goLineTimeRight(70);
      speedDC = 150;
      maxSpeed = 150;
    } else {
      takeFirst();
      speedDC = 150;
      maxSpeed = 150;
      if ((leftCount + rightCount) / 2 > 13000) {
        goToCrossRight();
      } else {
        goToCrossLeft();
      }
      pop();
      zeroMotor();
      // maxSpeed = 120;
      if (searchFirstRightCube(BIG_WHITE, cubes, k) > 0) {
        afterCrossRight();
      }
      number1 = 0;
      count = 0;
    }

  }
  if (count == 1) {
    speedDC = 150;
    maxSpeed = 150;
    if ((leftCount + rightCount) / 2 > 13000) {
      goToCrossRight();
    } else {
      goToCrossLeft();
    }
    pop();
    zeroMotor();

    count = 0;
  }



  afterCrossLeft();
  zeroMotor();
  //второй цвет
  stopCross = false;
  stopCube = false;
  count = 0;
  speedDC = 150;
  maxSpeed = 150;
  while (!stopCross) {
    lineDetectLeft();
    stopCross = false;
    stopCube = false;
    goToCrossCubeLeft();
    if (stopCube) {
      count++;
      delay(200);
      if (count == 1) {
        takeFirst();
        speedDC = 150;
        maxSpeed = 150;
        goLineTimeLeft(70);
        stopCube = false;
      } else {
        takeFirst();
        speedDC = 150;
        maxSpeed = 150;
        if ((leftCount + rightCount) / 2 > 13000) {
          goToCrossLeft();
        } else {
          goToCrossRight();
        }
        pop();
        zeroMotor();
        if ((--(--k)) > 0) {
          afterCrossLeft();
          stopCross = false;
          stopCube = false;
          count = 0;
        } else {
          stopCross = true;
          stopCube = true;
        }

      }
    } else {
      if (count > 0) {
        goLineTimeLeft(80);//если с одним кубиком перезжает то уменьшить
        stopLeft();
        pop();
      }
    }

  }
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
  while (1) {
    ;
  }

  // afterCrossLeft();
}

int searchFirstLeftCube(TypeCube type, TypeCube *massiv, int k) {
  for (int i = 0; i < k; i++) if (type == massiv[i])return i;
  return -1;
}

int searchFirstRightCube(TypeCube type, TypeCube *massiv, int k) {
  for (int i = k - 1; i > -1; i--) if (type == massiv[i])return i;
  return -1;
}

void moveMassiv(int number, TypeCube *massiv, int &k) {
  for (int i = number; i < k - 1; i++) {
    massiv[i] = massiv[i + 1];
  }
  k--;
}

void method4(TypeCube type) {
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
