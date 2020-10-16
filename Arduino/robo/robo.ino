#include <Servo.h> //включаем библиотеку
#include <Ultrasonic.h>
Servo handl; //обзначаем сервоприводы
Servo handr;
Servo head;
Ultrasonic ultrasonic(A1, 13);

void setup() {
  head.attach(12);
  Serial.begin(9600);
}

void loop() {

  head.write(0);
  delay(1000);

}
