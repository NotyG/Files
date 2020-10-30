#ifndef QTRRobo_H
#define QTRRobo_H
#include "Arduino.h"
#include "QTRSensors.h"
#include "EEPROM.h"
class QTRRobo : public QTRSensorsRC {
  public:
    QTRRobo(
      unsigned char* pins,
      unsigned char numSensors = 8,
      int timeout = 2500,
      char emitterPin = 15,
      int adress = 10
    ): QTRSensorsRC(
        pins,
        numSensors,
        timeout,
        emitterPin
      ) {
      this->adress = adress;
      getMinMax();
    }
    void calibrateEEPROM();//Калибровка датчика с записью в энергонезависимую память
    void read(unsigned int *sensor_values);//Прочитать и записать в массив сырые показания датчиков
    void readCalibrated(unsigned int *sensor_values);//Прочитать и записать в массив калиброванные показания датчиков
    void getMinMax();//Получить минимальные и максимальные показания для каждого датчика(из энергонезависимой памяти)
    void printMinMax();//Вывести их
    void print(unsigned int *sensor_values);//Вывести сырые значения датчиков
    void printCalibrated(unsigned int *sensor_values);//Вывести калиброванные значения датчиков
    float error(unsigned int *sensor_values);//Вывести калиброванные значения датчиков

  private:
    int min[8];//Массив с минимальными показаниями датчиков
    int max[8];//Массив с максимальными показаниями датчиков
    int adress;//Адрес, с которого начинается запись в энергонезависимую память

};
#endif
