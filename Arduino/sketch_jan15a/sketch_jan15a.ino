#include <QTRSensors.h>
unsigned int sensor_values[8];
int color;
#define NUM_SENSORS   8  
#define TIMEOUT       2500  
#define EMITTER_PIN   33
QTRSensors sensors((unsigned char[]){37,39,41,43,45,47,49,51}, NUM_SENSORS, TIMEOUT , EMITTER_PIN );





void setup() {
  Serial.begin(9600);


}
void loop() {
  
  color = sensors.read(sensor_values);
    for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
   Serial.print('\t');}
   Serial.println(color);
  delay(300);

}
