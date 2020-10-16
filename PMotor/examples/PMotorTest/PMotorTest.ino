//PMotor - library for pololu motor driver TB6612FNG and similar drivers.
//PMotor - библиотека, предназначенная для управления моторами с помощью драйвера pololu TB6612FNG и аналогичных ему.  
//library PMotor similar to AFMotor / библиотека PMotor похожа на AFMotor

#include <PMotor.h>

PMotor motorL(11, 12, 13); //1st position - IN1, 2nd position - IN2, 3rd position - PWM
PMotor motorR(8, 9, 10);   //на 1 месте IN1, на 2 месте IN2, на 3 месте PWM
void setup() {
  motorL.run(RELEASE); //функция run отвечает за направление вращения мотора FORWARD - вперёд, BACKWARD - назад, RELEASE - стоп
  motorL.setSpeed(150); //функция setSpeed отвечает за скорость мотора
  motorR.run(RELEASE); //run function is responsible for the direction of rotation of the motor
  motorR.setSpeed(150); //setSpeed function is responsible for motor speed
  delay(100);
}

void loop() {
  motorL.run(FORWARD);
  motorR.run(FORWARD);
  delay(2000);
  motorL.run(BACKWARD);
  motorR.run(BACKWARD)
  delay(2000)
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  delay(1000);
}
