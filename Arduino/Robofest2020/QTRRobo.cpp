#include "Arduino.h"
#include "QTRRobo.h"
void QTRRobo::calibrateEEPROM() {
  unsigned int values[8];
  for (int i = 0; i < 8; i++) {
    min[i] = 5000;
    max[i] = 0;
  }
  delay(1000);
  for (int i = 0; i < 500; i++) {
    QTRSensorsRC::read(values);
    delay(20);
    Serial.println(i);
    for (int i = 0; i < 8; i++) {
      if  (values[i] < min[i])min[i] = values[i];
      if  (values[i] > max[i])max[i] = values[i];
    }
  }
  Serial.println("stop");
  for (int i = 0; i < 8; i++) {
    EEPROM.put(adress + 8 * i, min[i]);
    EEPROM.put(adress + 4 + 8 * i, max[i]);
  }
  Serial.println();
  getMinMax();
  printMinMax();
}
void QTRRobo::getMinMax() {
  for (int i = 0; i < 8; i++) {
    EEPROM.get(adress + 8 * i, min[i]);
    EEPROM.get(adress + 4 + 8 * i, max[i]);
  }
}
void QTRRobo::printMinMax() {
  for (int i = 0; i < 8; i++) {
    Serial2.print(min[i]);
    Serial2.print("  ");
    Serial2.print(max[i]);
    Serial2.println("   ");
  }
}
void QTRRobo::read(unsigned int *sensor_values) {
  QTRSensorsRC::read(sensor_values);
}
void QTRRobo::readCalibrated(unsigned int *sensor_values) {
  QTRSensorsRC::read(sensor_values);
  for (int i = 0; i < 8; i++) {
    if (abs(max[i] - min[i]) < 2) {
      sensor_values[i] = 1000;
    } else {
      sensor_values[i] = 1000 - (max[i] - sensor_values[i]) / ((max[i] - min[i]) * 1.0) * 1000.0;
      //      if (sensor_values[i] <0)sensor_values[i] = 0;
      if (sensor_values[i] > 900)sensor_values[i] = 1000;
      if (sensor_values[i] < 200)sensor_values[i] = 0; //было 100
    }
  }
}
void QTRRobo::printCalibrated(unsigned int *sensor_values) {
  readCalibrated(sensor_values);
  for (int i = 0; i < 8; i++) {
    Serial.print(sensor_values[i]);
    Serial.print("\t");
  }
  Serial.println();

}
void QTRRobo::print(unsigned int *sensor_values) {
  QTRSensorsRC::read(sensor_values);
  for (int i = 0; i < 8; i++) {
    Serial.print(sensor_values[i]);
    Serial.print("\t");
  }
  Serial.println();

}
float QTRRobo::error(unsigned int *sensor_values) {
  readCalibrated(sensor_values);
  float s = 0, s2 = 0;
  for (int i = 0; i < 8; i++) {
    s += sensor_values[i];
    s2 += i * sensor_values[i];
  }
  if (s < 5) s = 5;
  if (s2 == 0) return 0;
  return s2 / s - 3.5;
}
