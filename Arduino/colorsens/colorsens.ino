#include <QTRSensors.h>
#include <AFMotor.h>
int Speed = 80;
int sensorval = 600;
int k = 40;
AF_DCMotor motorL(2);
AF_DCMotor motorR(1);
QTRSensors qtrL;
const uint8_t SensorCount = 8; //кол -во датчиков
uint16_t sensorValues[SensorCount]; //массив с информацией

float err(uint16_t sensorValues[SensorCount]);
void sms(int v, int v1, int moveR, int moveL);




void setup() {
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  qtrL.setTypeRC(); //установка типа датчиков
  qtrL.setSensorPins((const uint8_t[]) {
    50, 48, 46, 44, 42, 40, 38, 36
  }, 8); //    устаовка пинов датчиков
  qtrL.setEmitterPin(52); //установка emittera
  /* for (uint8_t i = 0; i < 250; i++) {
     qtrL.calibrate();
     delay(20);*/

}

void loop()
{
  qtrL.read(sensorValues);
  float error = err(sensorValues);
  int speedR, speedL;
  // int Left =  sensorValues[0] + sensorValues[1] + sensorValues[2] + sensorValues[3];
  // int Right = sensorValues[4] + sensorValues[5] + sensorValues[6] + sensorValues[7];
  //

  if (abs(error) > 0) {
    if (error < -1) {
      sms (Speed, Speed, RELEASE , RELEASE );
      delay(50);
      sms(Speed, Speed, BACKWARD , FORWARD);
      delay(600);
    }
    else if (error > 1) {
      sms (Speed, Speed, RELEASE , RELEASE );
      delay(50);
      sms(Speed, Speed, FORWARD , BACKWARD);
      delay(600);
    }
    speedR = Speed - k * error;
    speedL = Speed + k * error;

  }
  /* else if (Left < Right) {
     speedR = Speed - error;
     speedL = Speed + error;
    }*/
  else {
    speedR = Speed;
    speedL = Speed;
  }
  //
  if (sensorValues[0] < sensorval && sensorValues[1] < sensorval && sensorValues[2] < sensorval && sensorValues[3] < sensorval && sensorValues[4] < sensorval && sensorValues[5] < sensorval && sensorValues[6] < sensorval && sensorValues[7] < sensorval) {
    sms (speedR, speedL, RELEASE , RELEASE ); //NACOS
  }
  else {
    sms(speedR, speedL, FORWARD, FORWARD);
  }
}

float err(uint16_t sensorValues[SensorCount]) {
  float cm = 0;
  float del = 0;
  for (int8_t i = 0; i < 8; i++) {
    cm += i * sensorValues[i];
    del += sensorValues[i];
  }
  float centre = cm / del;
  float error = centre - 3.5;
  return error;
}
//
void sms(int v, int v1, int moveR, int moveL)
{
  motorR.setSpeed(v);
  motorL.setSpeed(v1);
  motorR.run(moveR);
  motorL.run(moveL);
}
