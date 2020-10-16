#include <Wire.h>
#include <ZumoShield.h>
#include <Servo.h>
Servo handr;
ZumoMotors motors;
void setup() {
  motors.setSpeeds(20, 20);
    handr.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay (1000);
  motors.setSpeeds(250, 250);
  delay(1000);
  motors.setSpeeds(0, 0);

 /* handr.write (90);
  delay(1000);
  handr.write(30);
  delay(1000);
  handr.write (90);
  delay(1000);
  handr.detach();
*/S}
