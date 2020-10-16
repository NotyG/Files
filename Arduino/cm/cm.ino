#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 8; //кол -во датчиков
uint16_t sensorValues[SensorCount]; //массив с информацией
void setup() {
  qtr.setTypeRC(); //установка типа датчиков
  qtr.setSensorPins((const uint8_t[]) {50, 48, 46, 44, 42, 40, 38, 36}, 8); //    устаовка пинов датчиков
  qtr.setEmitterPin(52);
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  qtr.read(sensorValues);
  float cm=0;
  float del=0;
  for (int8_t i = 0; i < 8; i++){
    cm+=i*sensorValues[i]; 
    del+=sensorValues[i];
  }
  float centre=cm/del;
  Serial.println(centre);
}
